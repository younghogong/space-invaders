#include "tankSM.h"

// ----------------------------------------------------------------------------

void tankSM_init() {

}

// ----------------------------------------------------------------------------

void tankSM_tick() {
	if (pushButtons_LeftPressed()) {
		tank_left();
	} else if (pushButtons_RightPressed()) {
		tank_right();
	}
}

// ----------------------------------------------------------------------------
