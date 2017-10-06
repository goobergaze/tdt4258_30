#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define   SAMPLE_PERIOD   0

void setupTimer(uint32_t period);
void setupDAC();
void setupNVIC();
void setupEnergyOptimizations();

int main(void)
{
	setupEnergyOptimizations();

	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupDAC();
	setupTimer(SAMPLE_PERIOD);

	/*
	 * Enable interrupt handling 
	 */
	setupNVIC();

	/*
	 * TODO for higher energy efficiency, sleep while waiting for
	 * interrupts instead of infinite loop for busy-waiting 
	 */

	__WFI(); // we'll see if that works

	//while (1) ;

	return 0;
}

void setupNVIC()
{
	/*
	 * Enable TIMER1, GPIO odd and GPIO even interrupt handling
	 */
	*ISER0 = 0b1100000000010;
}

void setupEnergyOptimizations()
{
	*MSC_READCTRL = 0b1101010; /* Set zero wait-state access with SCBTP, disable instruction cache */
	*CMU_LFCLKSEL = 0; /* Disable low frequency clocks or something */
	*SCR = 0b110; /* Configure EM3 on sleep mode & sleep on exit */
}

/*
 * if other interrupt handlers are needed, use the following names:
 * NMI_Handler HardFault_Handler MemManage_Handler BusFault_Handler
 * UsageFault_Handler Reserved7_Handler Reserved8_Handler
 * Reserved9_Handler Reserved10_Handler SVC_Handler DebugMon_Handler
 * Reserved13_Handler PendSV_Handler SysTick_Handler DMA_IRQHandler
 * GPIO_EVEN_IRQHandler TIMER0_IRQHandler USART0_RX_IRQHandler
 * USART0_TX_IRQHandler USB_IRQHandler ACMP0_IRQHandler ADC0_IRQHandler
 * DAC0_IRQHandler I2C0_IRQHandler I2C1_IRQHandler GPIO_ODD_IRQHandler
 * TIMER1_IRQHandler TIMER2_IRQHandler TIMER3_IRQHandler
 * USART1_RX_IRQHandler USART1_TX_IRQHandler LESENSE_IRQHandler
 * USART2_RX_IRQHandler USART2_TX_IRQHandler UART0_RX_IRQHandler
 * UART0_TX_IRQHandler UART1_RX_IRQHandler UART1_TX_IRQHandler
 * LEUART0_IRQHandler LEUART1_IRQHandler LETIMER0_IRQHandler
 * PCNT0_IRQHandler PCNT1_IRQHandler PCNT2_IRQHandler RTC_IRQHandler
 * BURTC_IRQHandler CMU_IRQHandler VCMP_IRQHandler LCD_IRQHandler
 * MSC_IRQHandler AES_IRQHandler EBI_IRQHandler EMU_IRQHandler 
 */
