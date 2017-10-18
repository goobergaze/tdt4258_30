#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"

/* Counter used for generating waveforms */
uint32_t ticks = 0;

/* Addresses pointing to sound data for each channel */
uint32_t *mainAddress[4] = {0};
uint32_t *loopAddress[4] = {0};

/* Current state of each channel */
uint16_t freq[4] = {0};
int8_t sample[4] = {0};
uint8_t volume[4] = {0};
uint8_t waveform[4] = {0};
uint16_t duration[4] = {0};
uint8_t lastPhase[4] = {0};
int32_t tickOffset[4] = {0};

/* External helper functions */
void timerStart();
void timerStop();

int8_t noiseLCG();
int8_t adjustVolume(int8_t sample, uint8_t volume);
uint16_t getFrequency(uint32_t frame);

/***---------------------------------------------------------------***/

void soundPlay(uint32_t *ch0, uint32_t *ch1, uint32_t *ch2, uint32_t *ch3)
{
	/*
	 * Use parameters to specify which channels to play sounds on,
	 * and leave the rest set to null - these will be ignored here.
	 * This routine shouldn't be interrupted, so we pause the timer.
	 */

	timerStop();

	/* Write new addresses */
	mainAddress[0] = ch0 ? ch0 : mainAddress[0];
	mainAddress[1] = ch1 ? ch1 : mainAddress[1];
	mainAddress[2] = ch2 ? ch2 : mainAddress[2];
	mainAddress[3] = ch3 ? ch3 : mainAddress[3];
	
	/* Re-initialize loop addresses */
	loopAddress[0] = loopAddress[1] = loopAddress[2] = loopAddress[3] = 0;

	/* Interrupt pending frames */
	duration[0] = ch0 ? 0 : duration[0];
	duration[1] = ch1 ? 0 : duration[1];
	duration[2] = ch2 ? 0 : duration[2];
	duration[3] = ch3 ? 0 : duration[3];

	timerStart();
}

void soundStop()
{
	/* Stop the timer */
	*TIMER1_CMD = 2;

	/* Clear all addresses to prevent sound from playing */
	mainAddress[0] = mainAddress[1] = mainAddress[2] = mainAddress[3] = 0;
	loopAddress[0] = loopAddress[1] = loopAddress[2] = loopAddress[3] = 0;
};

bool soundIsPlaying()
{
	return mainAddress[0] || mainAddress[1] || mainAddress[2] || mainAddress[3];
}

void soundRequestFrame()
{
	for(uint8_t i = 0; i < 4; i++)
	{
		/* Don't fetch a new frame if the current one is not over yet */
		if(duration[i] > 0)
		{
			duration[i]--;
			continue;
		}
		
		/*
		 * Fetch the current frame and read its duration.
		 * If it's zero, then this is the last sound frame.
		 * If a loop frame is specified, jump back to it.
		 * Otherwise, stop the sound.
		 */
		uint32_t frame = mainAddress[i] ? *mainAddress[i] : 0;
		duration[i] = frame & 0x3FF;

		if(duration[i] == 0)
		{
			if(loopAddress[i])
			{
				mainAddress[i] = loopAddress[i];

				/* Crude restart */
				i--;
				continue;
			}
			mainAddress[i] = 0;
			frame = 0;
		}

		/***---------------------------------------------------------------***/

		/* Read the remaining frame data */
		waveform[i] = (frame & 0x1E0000) >> 17;
		volume[i]   = (frame & 0x00FC00) >> 10;
		
		if(frame & LOOP)
		{
			/* Specify a starting frame for a looping sound */
			loopAddress[i] = mainAddress[i];
		}

		/*
		 * Obtain the new frequency from an 11-bit logarithmic value.
		 * Compare it to the old frequency and adjust the tick offset/phase
		 * for a smoother transition between the two frequencies.
		 */
		uint16_t newFreq = getFrequency(frame);

		tickOffset[i] = ((ticks + tickOffset[i]) * freq[i] - ticks * newFreq) / newFreq;

		freq[i] = newFreq;

		/* Advance address to the upcoming frame (ignore if null) */
		mainAddress[i] += mainAddress[i] ? 1 : 0;
		duration[i]--;
	}
}

void soundTick()
{
	if(!soundIsPlaying())
	{
		soundStop();
	}

	/* Request a new frame at regular intervals */
	bool newFrame = ticks % TICKS_PER_FRAME == 0;

	if(newFrame)
	{
		soundRequestFrame();
	}

	/* Generate new samples on each channel */
	for(uint8_t i = 0; i < 4; i++)
	{
		/*
		 * Calculate the phase of the wave currently playing.
		 * If it's the same as it was last time on the same frame,
		 * then skip sample generation.
		 */
		uint8_t phase = ((ticks + tickOffset[i]) * freq[i] * PERIOD / SAMPLE_RATE) % PERIOD;

		if(phase == lastPhase[i] && !newFrame)
		{
			continue;
		}

		/***---------------------------------------------------------------***/

		/* Create pulse-width modulation if PWM bit is set */
		if(waveform[i] & 0b1000)
		{
			uint8_t dutyCycle = (waveform[i] & 0b0111) + 1;

			sample[i] = phase < dutyCycle * PERIOD / 16 ? AMPLITUDE : -AMPLITUDE;
		}
		else /* Create a different waveform */
		{
			switch(waveform[i])
			{
				case 0: /* White noise */

					sample[i] = noiseLCG();
					break;

				case 1: /* Sawtooth */

					sample[i] = phase * SAW_NOTCH - AMPLITUDE;
					break;

				case 2: /* Triangle */

					sample[i] = AMPLITUDE - (phase % PERIOD / 2) * TRI_NOTCH;

					if(phase < PERIOD / 2)
					{
						sample[i] = -sample[i];
					}
					break;
			}
		}

		/* Final adjustments */
		sample[i] = adjustVolume(sample[i], volume[i]);
		lastPhase[i] = phase;
	}

	/* Mix the channel samples and feed them to DAC (mono) */
	*DAC0_CH0DATA = *DAC0_CH1DATA = 0x7FF + sample[0] + sample[1] + sample[2] + sample[3];

	ticks++;
}
