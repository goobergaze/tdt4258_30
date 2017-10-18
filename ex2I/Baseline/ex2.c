#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"

void setupTimer(uint32_t period);
void setupDAC();
void setupGPIO();

void soundPlay();
void soundTick();
void buttonRoutine();


int main(){

	// Call the peripheral setup functions 
	setupGPIO();
	setupDAC();
	setupTimer(SAMPLE_PERIOD);

	// Play the startup jingle 
	extern const uint32_t *jingle[3];
	soundPlay(jingle[0], jingle[1], jingle[2], 0);

	uint32_t previousTime = 0;
	while(1)
	{
		buttonRoutine();
		// Check counter overflow 
		if(*TIMER1_CNT < previousTime)
		{
			soundTick();
		}
		previousTime = *TIMER1_CNT;
}
	return 0;
}
