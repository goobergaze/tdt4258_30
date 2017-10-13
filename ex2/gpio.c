#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"

void soundPlay();
void soundStop();

const uint32_t heli[3][5] =
{
	{
		( 14 << 21) | VOLUME_42 | WAVE_NOISE | 2 | LOOP,
		( 56 << 21) | VOLUME_04 | WAVE_NOISE | 2,
		(  7 << 21) | VOLUME_38 | WAVE_NOISE | 2,
		(784 << 21) | VOLUME_04 | WAVE_NOISE | 2,
		STOP
	},
	{
		NOTE_AS2 | VOLUME_31 | WAVE_PWM3 | 2 | LOOP,
		NOTE_A_2 | VOLUME_15 | WAVE_PWM3 | 2,
		NOTE_F_8 | VOLUME_07 | WAVE_PWM3 | 2,
		NOTE_E_8 | VOLUME_03 | WAVE_PWM3 | 2,
		STOP
	},
	{
		NOTE_E_3 | VOLUME_63 | WAVE_TRIANGLE | 1 | LOOP,
		NOTE_F_2 | VOLUME_63 | WAVE_TRIANGLE | 1,
		STOP, STOP, STOP
	},
};


void setupGPIO()
{
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;
	*GPIO_PC_MODEL  = 0x33333333;
	*GPIO_PC_DOUT   = 0xFF;
	*GPIO_EXTIPSELL = 0x22222222;
	*GPIO_EXTIFALL  = 0xFF;
	*GPIO_EXTIRISE  = 0xFF;
	*GPIO_IEN       = 0xFF;
}

void buttonRoutine()
{
	switch(*GPIO_PC_DIN & 0xFF)
	{
		case 0b11111110:

			soundPlay(heli[0], heli[1], heli[2], 0);
			break;

		case 0b10111111:
			soundStop();
			break;
	}
}