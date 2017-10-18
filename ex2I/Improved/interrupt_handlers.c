#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"

void soundTick();
void buttonRoutine();


void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	*TIMER1_IFC = 1; /* Clear pending interrupt flag */
	soundTick();
}

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	*GPIO_IFC = *GPIO_IF; /* Clear pending interrupt flag */
	buttonRoutine();
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	*GPIO_IFC = *GPIO_IF; /* Clear pending interrupt flag */
	buttonRoutine();
}
