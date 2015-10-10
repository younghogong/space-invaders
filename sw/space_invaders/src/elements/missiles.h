#ifndef MISSILES_H_
#define MISSILES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../globals.h"
#include "../screen/screen.h"
#include "aliens.h"
#include "tank.h"

// missile size info
#define MISSILE_HEIGHT 		6
#define MISSILE_WIDTH 		3
#define MISSILE_COUNT		4
#define MISSILE_SCALE		1 // how much should we scale?
#define MISSILE_SHIFT 		6 // how many pixels shold we move by every time?


// color def
#define MISSILE_COLOR 		SCREEN_COLOR_WHITE

// index of tank missile in missile array
#define TANK_MISSILE		0


// missile struct definition
typedef struct{
	point_t origin;				// current location of missile
	const uint32_t* symbol_r;	// alternating missile bitmap
	const uint32_t* symbol_l;	// alternating missile bitmap
	const bool up; 				// missile direction
	bool active;				// missle in flight?
	const symbolsize_t size;	// size of missile bitmap
} missile_t;

// function delcarations
void missiles_tank_fire();
void missiles_move();
void missiles_alien_fire();


// array of all missile types
static missile_t missile_array[MISSILE_COUNT] = {
		{
				.symbol_r = missile0_6x6,			// missile type 1 (tank)
				.symbol_l = missile0_6x6,
				.up = true,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
		{
				.symbol_r = missile1_6x6,			// missile type 2 (alien)
 				.symbol_l = missile1_6x6,
				.up = false,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
		{
				.symbol_r = missile2_6x6,			// missile type 3 (alien)
				.symbol_l = missile2_6x6,
				.up = false,
				.active = false,
				.size = {.w = MISSILE_WIDTH, .h = MISSILE_HEIGHT}
		},
		{
				.symbol_r = missile3r_6x6,			// missile type 4 (alien)
				.symbol_l = missile3l_6x6,			// only missile with "wiggle" movement
				.up = false,
				.active = false,
				.size = {.w = 6, .h = 6}
		},
};

//-----------------------------------------------------------------------------

void missiles_init();

#endif /* MISSILES_H_ */