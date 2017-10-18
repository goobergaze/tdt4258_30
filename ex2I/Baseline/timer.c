#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"

void timerStart()
{
	*TIMER1_CMD = 1;
}

void timerStop()
{
	*TIMER1_CMD = 2;
}

void setupTimer(uint16_t period)
{
	
	*CMU_HFPERCLKEN0 |= 1<<6;
	*TIMER1_TOP = period;
	*TIMER1_IEN = 1;


	timerStart();
}
