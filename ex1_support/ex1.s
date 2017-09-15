        .syntax unified
	
	      .include "efm32gg.s"

	/////////////////////////////////////////////////////////////////////////////
	//
  // Exception vector table
  // This table contains addresses for all exception handlers
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .section .vectors
	
	      .long   stack_top               /* Top of Stack                 */
	      .long   _reset                  /* Reset Handler                */
	      .long   dummy_handler           /* NMI Handler                  */
	      .long   dummy_handler           /* Hard Fault Handler           */
	      .long   dummy_handler           /* MPU Fault Handler            */
	      .long   dummy_handler           /* Bus Fault Handler            */
	      .long   dummy_handler           /* Usage Fault Handler          */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* SVCall Handler               */
	      .long   dummy_handler           /* Debug Monitor Handler        */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* PendSV Handler               */
	      .long   dummy_handler           /* SysTick Handler              */

	      /* External Interrupts */
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO even handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO odd handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler

	      .section .text

	/////////////////////////////////////////////////////////////////////////////
	//
	// Reset handler
  // The CPU will start executing here after a reset
	//
	/////////////////////////////////////////////////////////////////////////////

	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset:

	/***************** Energy saving setup *****************/

	// EM2 on sleep & sleep on interrupt return
	ldr r0, =#SCR
	ldr r1, =#0x6
	str r1, [r0]


	/**************** I/O & interrupt setup ****************/

	// Turn on GPIO clock
	ldr r0, =#(CMU_BASE + CMU_HFPERCLKEN0)
	ldr r1, =#(1 << CMU_HFPERCLKEN0_GPIO)
	str r1, [r0]

	// Keep GPIO base addresses in these registers
	ldr r0, =#GPIO_PA_BASE
	ldr r1, =#GPIO_PC_BASE
	ldr r2, =#GPIO_BASE

	// Port A setup (LED)
	ldr r3, =#0x2
	str r3, [r0, #GPIO_CTRL]
	ldr r3, =#0x55555555
	str r3, [r0, #GPIO_MODEH]
	ldr r3, =#0xff00
	str r3, [r0, #GPIO_DOUT]

	// Port C setup (buttons)
	ldr r3, =#0x33333333
	str r3, [r1, #GPIO_MODEL]
	ldr r3, =#0xff
	str r3, [r1, #GPIO_DOUT]

	// GPIO interrupt setup
	ldr r3, =#0x22222222
	str r3, [r2, #GPIO_EXTIPSELL]
	ldr r3, =#0xff
	str r3, [r2, #GPIO_EXTIFALL]
	str r3, [r2, #GPIO_EXTIRISE]
	str r3, [r2, #GPIO_IEN]

	// Enable interrupts
	ldr r4, =#ISER0
	ldr r3, =#0x802
	str r3, [r4]


	wfi // Sleep


	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:

	// Clear interrupt
	ldr r3, [r2, #GPIO_IF]
	str r3, [r2, #GPIO_IFC]

	// Test
	ldr r3, [r1, #GPIO_DIN]
	ldr r4, =#0xff
	and r3, r3, r4
	lsl r3, r3, #8
	str r3, [r0, #GPIO_DOUT]

	bx lr // Return

	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

