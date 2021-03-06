#include <stdio.h>          // xil_printf and so forth.
#include <stdint.h>			// uint32_t and so forth.

#include "xgpio.h"          // Provides access to PB GPIO driver.
#include "platform.h"       // Enables caching and other system stuff.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.
#include "pit.h"

#include "clock/clock.h"
#include "debouncer/debouncer.h"
#include "uartControl/uartControl.h"

XGpio gpPB;   			// This is a handle for the push-button GPIO block.
u8 counter = 0;			// tens of milliseconds
u8 refresh_counter = 0; // screen refresh counter
u8 bouncing = 0;		// whether or not the button is in debounce mode

// This is invoked in response to a timer interrupt.
// It does 2 things: 1) debounce switches, and 2) advances the time.
void timer_interrupt_handler() {
	uint32_t seconds = 0;
	uint32_t minutes = 0;
	uint32_t hours = 0;

	if (++counter == ONE_SECOND && !in_auto_increment_mode()){
		// clear the counter, it's been a second
		counter = 0;

		// increment the clock
		incrementClock();
	} else if (++refresh_counter == FAST_COUNT_MAX) {
		// clear the counter, it's time to refresh
		refresh_counter = 0;

		// grab the clock values so we can print them out
		getClock(&seconds, &minutes, &hours);

		// make sure to backspace so clock changes in place
		xil_printf("\b\b\b\b\b\b\b\b%02d:%02d:%02d", hours, minutes, seconds);
	}

	// let the bouncer know an interrupt occurred so it can debounce the button
	if (bouncing) tick_bouncer();

}

// This is invoked each time there is a change in the button state (result of a push or a bounce).
void pb_interrupt_handler() {
	// Clear the GPIO interrupt.

	// Turn off all PB interrupts for now.
	XGpio_InterruptGlobalDisable(&gpPB);
	// Get the current state of the buttons.
	u32 currentButtonState = XGpio_DiscreteRead(&gpPB, 1);

	bouncing = bouncer(currentButtonState);

	// Ack the PB interrupt.
	XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);
	// Re-enable PB interrupts.
	XGpio_InterruptGlobalEnable(&gpPB);
}

/******************************************************************************
 * Main interrupt handler, queries interrupt controller to see what peripheral
 * fired the interrupt and then dispatches the corresponding interrupt handler.
 * This routine acks the interrupt at the controller level but the peripheral
 * interrupt must be ack'd by the dispatched interrupt handler.
 *****************************************************************************/
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);

	// Check the FIT interrupt first.
	if (intc_status & XPAR_PIT_0_MYINTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PIT_0_MYINTERRUPT_MASK);
		timer_interrupt_handler();
	}

	// Check the push buttons.
	if (intc_status & XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
		pb_interrupt_handler();
	}
}

int main (void) {
    init_platform();
    // Initialize the GPIO peripherals.
    XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
    // Set the push button peripheral to be inputs.
    XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
    // Enable the global GPIO interrupt for push buttons.
    XGpio_InterruptGlobalEnable(&gpPB);
    // Enable all interrupts in the push button peripheral.
    XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

    pit_init();
    pit_load_value(1000000); // init to 10 ms
    pit_enable_load();
    pit_enable_interrupts();
    pit_enable_count();


    microblaze_register_handler(interrupt_handler_dispatcher, NULL);
    XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
    		(XPAR_PIT_0_MYINTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
    XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);

    microblaze_enable_interrupts();

    // Tell stdin that it gets zero! none! (as far as buffering goes)
    setvbuf(stdin, NULL, _IONBF, 0);

    while(1){
		// blocking call: wait until a character is present
		char input = getchar();

		// Handle the UART control of game
		uartControl_handle(input);
    }

    cleanup_platform();

    return 0;
}
