#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "efm32gg.h"

/*
 * Global variables
 */
unsigned int timeElapsed = 0;


void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	*TIMER1_IFC = 1; /* Clear pending interrupt flag */
	timeElapsed++; /* Increment counter used for generating waveforms */

	/*
	 * TODO feed new samples to the DAC
	 */
	unsigned short sample = (1 + sin(0.02 * timeElapsed)) * 0x7FF; /* some 12-bit sine wave */
	*DAC0_CH0DATA = *DAC0_CH1DATA = sample /* feed sample to DAC (mono) */

}

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
}
