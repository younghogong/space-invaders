#include <stdio.h>          // xil_printf and so forth.
#include <stdint.h>			// uint32_t and so forth.

#include "xgpio.h"          // Provides access to PB GPIO driver.
#include "platform.h"       // Enables caching and other system stuff.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.

#include "clock/clock.h"
#include "debouncer/debouncer.h"

XGpio gpLED;  // This is a handle for the LED GPIO block.
XGpio gpPB;   // This is a handle for the push-button GPIO block.
u8 counter; // tens of milliseconds
u8 manual_counter;
u8 bouncing = 0;
char time[5] = "";

// This is invoked in response to a timer interrupt.
// It does 2 things: 1) debounce switches, and 2) advances the time.
void timer_interrupt_handler() {
	// for testing only
	uint32_t seconds = 0;
	uint32_t minutes = 0;
	uint32_t hours = 0;
	uint8_t manual_mode;

	manual_mode = in_manual();

	if (++counter == 100 && !manual_mode){

		// clear the counter, it's been a second
		counter = 0;

		// increment the clock
		incrementClock();
	}
	else if(++manual_counter==20){
		getClock(&seconds, &minutes, &hours);
		xil_printf("\b\b\b\b\b\b\b\b%02d:%02d:%02d", hours, minutes, seconds);
		manual_counter = 0;
	}
	if(bouncing){
		tick_bouncer();
	}

}

// This is invoked each time there is a change in the button state (result of a push or a bounce).
void pb_interrupt_handler() {
	// Clear the GPIO interrupt.
	XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now.
	u32 currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.

	bouncing = bouncer(currentButtonState) ? 1 : 0;
//	xil_printf("%d\n\r", currentButtonState);

	XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);            // Ack the PB interrupt.
	XGpio_InterruptGlobalEnable(&gpPB);                 // Re-enable PB interrupts.
}

// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
	// Check the FIT interrupt first.
	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
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
    int success;
    success = XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
    // Set the push button peripheral to be inputs.
    XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
    // Enable the global GPIO interrupt for push buttons.
    XGpio_InterruptGlobalEnable(&gpPB);
    // Enable all interrupts in the push button peripheral.
    XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

    microblaze_register_handler(interrupt_handler_dispatcher, NULL);
    XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
    		(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
    XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
    microblaze_enable_interrupts();

    while(1);  // Program never ends.

    cleanup_platform();

    return 0;
}
