#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"

void setupTimer(uint32_t period);
void setupDAC();
void setupGPIO();
void setupNVIC();
void setupEnergyOptimizations();

void soundPlay();


int main()
{
	setupEnergyOptimizations();

	/* Call the peripheral setup functions */
	setupGPIO();
	setupDAC();
	setupTimer(SAMPLE_PERIOD);

	/* Play the startup jingle */
	extern const uint32_t *jingle[3];
	soundPlay(jingle[0], jingle[1], jingle[2], 0);

	/* Enable interrupt handling */
	setupNVIC();

	/* Enter sleep mode */
	__asm("wfi");

	return 0;
}

void setupNVIC()
{
	/* Enable TIMER1, GPIO odd and GPIO even interrupt handling */
	*ISER0 = 0b1100000000010;
}

void setupEnergyOptimizations()
{
	/* Set zero wait-state access with SCBTP, disable instruction cache */
	*MSC_READCTRL = 0b1101010;

	/* Disable low frequency clocks or something */
	*CMU_LFCLKSEL = 0;

	/* Configure EM1 on sleep mode & sleep on exit */
	*SCR = 0b10;
}


