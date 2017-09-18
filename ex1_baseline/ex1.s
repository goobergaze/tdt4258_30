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

	// Set zero wait-state access with SCBTP
	ldr r0, =#(MSC_BASE + MSC_READCTRL)
	ldr r1, =#0b10
	str r1, [r0]

	// Disable if-then folding
	ldr r0, =#ACTLR
	ldr r1, =#0b100
	str r1, [r0]

	// Power off RAM blocks
	ldr r0, =#(EMU_BASE + EMU_MEMCTRL)
	ldr r1, =#0b111
	str r1, [r0]


	/****************** Init values setup ******************/

	// Dedicated button state register
	ldr r3, =#0xff

	// Dedicated LED state registers
	ldr r6, =#0xfffffeff // Leftmost
	ldr r9, =#0xffff7fff // Rightmost


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
	ldr r4, =#0x2
	str r4, [r0, #GPIO_CTRL]
	ldr r4, =#0x55555555
	str r4, [r0, #GPIO_MODEH]
	ldr r4, =#0x7e00
	str r4, [r0, #GPIO_DOUT]

	// Port C setup (buttons)
	ldr r4, =#0x33333333
	str r4, [r1, #GPIO_MODEL]
	ldr r4, =#0xff
	str r4, [r1, #GPIO_DOUT]

	// GPIO interrupt setup
	ldr r4, =#0x22222222
	str r4, [r2, #GPIO_EXTIPSELL]
	ldr r4, =#0xff
	str r4, [r2, #GPIO_EXTIFALL]
	str r4, [r2, #GPIO_EXTIRISE]
	str r4, [r2, #GPIO_IEN]

	// Enable interrupts
	ldr r5, =#ISER0
	ldr r4, =#0x802
	str r4, [r5]

	// Enter sleep mode
	wfi


gpio_loop:

	// Read button state into r4
	ldr r4, [r1, #GPIO_DIN]
	ldr r5, =#0xff
	and r4, r4, r5

	// Mask current LED states onto r5 and r10
	ldr r10, =#0xff00
	and r5, r10, r6
	and r10, r10, r9

	// Use r7 to check which button has been pressed
	mvn r7, r3
	orr r7, r7, r4
	mvn r7, r7

	// Move leftmost LED
sw1_press:
	cmp r7, #0b1
	bne sw3_press
	cmp r5, #0xfe00
	beq rest
	lsr r6, r6, #1
sw3_press:
	cmp r7, #0b100
	bne sw5_press
	cmp r5, #0x7f00
	beq rest
	lsl r6, r6, #1

	// Move rightmost LED
sw5_press:
	cmp r7, #0b10000
	bne sw7_press
	cmp r10, #0xfe00
	beq rest
	lsr r9, r9, #1
sw7_press:
	cmp r7, #0b1000000
	bne rest
	cmp r10, #0x7f00
	beq rest
	lsl r9, r9, #1

rest:
	// Copy button state
	mov r3, r4

	// Display both LEDs
	and r5, r6, r9
	ldr r7, =#0xff00
	and r5, r5, r7
	str r5, [r0, #GPIO_DOUT]

	b gpio_loop

	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

