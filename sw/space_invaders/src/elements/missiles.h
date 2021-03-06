#ifndef MISSILES_H_
#define MISSILES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../globals.h"
#include "../screen/screen.h"
#include "../audio/audio.h"
#include "aliens.h"
#include "tank.h"
#include "bunkers.h"
#include "gameScreen.h"
#include "spaceship.h"

// missile size info (using largest missile)
#define MISSILE_SCALE		1
#define MISSILE_HEIGHT 		(BITMAP_ALIEN_MISSILE_3_HEIGHT*MISSILE_SCALE)
#define MISSILE_WIDTH 		(BITMAP_ALIEN_MISSILE_3_WIDTH*MISSILE_SCALE)
#define MISSILE_SHIFT 		4 // how many pixels should we move by every time?

#define MISSILE_ALIEN_COUNT	3
#define MISSILE_TANK_COUNT	1
#define MISSILE_COUNT		(MISSILE_TANK_COUNT+MISSILE_ALIEN_COUNT)

// missile boundary conditions
#define MISSILE_BOTTOM_BUFFER	(FLOOR_ORIGIN_Y-(2*MISSILE_HEIGHT)-FLOOR_HEIGHT)
#define MISSILE_TOP_BUFFER		(SCREEN_EDGE_BUFFER+2*SCORE_TXT_HEIGHT)

// color def
#define MISSILE_COLOR 		SCREEN_COLOR_WHITE

// index of tank missile in missile array
#define TANK_MISSILE		0


// missile struct definition
typedef struct{
	point_t origin;					// current location of missile
	const uint32_t *symbol_r;		// alternating missile bitmap
	const uint32_t *symbol_l;		// alternating missile bitmap
	const bool up; 					// missile direction
	bool active;					// missile in flight?
	const symbolsize_t *bitmapSize;	// size of missile bitmap
} missile_t;

//-----------------------------------------------------------------------------

// Initialize all the missile objects
void missiles_init();

// Tell the tank to fire a missile
void missiles_tankFire();

// update all alien missile locations
void missiles_moveAlienMissiles();

// update the tank's missile
void missiles_moveTankMissile();

// have the (x,y) alien shoot a missile
bool missiles_alienFire(uint16_t x, uint16_t y);

// erase all the flying missiles
void missiles_deactivateAll();

// how many alien missiles are there in the sky?
uint16_t missiles_getActiveAlienMissiles();

#endif /* MISSILES_H_ */
