#include "aliens.h"

// array of the 3 types of aliens (elite, infantry, and grunt)
static const alien_t alien_symbols[ALIEN_ROW_COUNT] = {
		/** Elite Aliens **/

		{
				.in = alien_top_in_12x8,
				.out = alien_top_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_ELITE_VALUE
		},

		/** Infantry Aliens **/

		{
				.in = alien_middle_in_12x8,
				.out = alien_middle_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_INFANTRY_VALUE
		},
		{
				.in = alien_middle_in_12x8,
				.out = alien_middle_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_INFANTRY_VALUE
		},

		/** Grunt Aliens **/

		{
				.in = alien_bottom_in_12x8,
				.out = alien_bottom_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_GRUNT_VALUE
		},
		{
				.in = alien_bottom_in_12x8,
				.out = alien_bottom_out_12x8,
				.bitmapSize = &alienBitmapSize,
				.scoreValue = ALIEN_SCORE_GRUNT_VALUE
		}
};

static bool alien_lives_matter[ALIEN_COUNT] = { false };
static point_t alienOrigins[ALIEN_COUNT];

// Holds the lowest 11 living aliens (used for shooting)
static uint16_t lowestAlien_Xs[ALIEN_COL_COUNT];
static uint16_t lowestAlien_Ys[ALIEN_COL_COUNT];

// Keep track of the living
static uint32_t alienAliveCount = 0;

// global var indicates which position the aliens
// are in (flapping up vs flapping in)
static bool flapIn = false;

// implementation of the struct above, nicknamed "the kill log"
static kill_t kill_log = { .kill = false };

// keeps track of whether the aliens should be marching right or left
static bool _aliensMarchingRight = true;

// how many living aliens are there in this column?
static uint8_t aliensInColumn[ALIEN_COL_COUNT] = { 0 };

// function definitions
void initAlienOrigins();
void initLivesArray();
void drawAliens();
void shiftAlienOrigin(uint16_t x, uint16_t y, int16_t xShift, int16_t yShift);
void updateLowestLivingAliens(uint16_t x, uint16_t y);
point_t get_rightPoint();
point_t get_leftPoint();

//-----------------------------------------------------------------------------

void aliens_init() {
	// set all lives to true
	initLivesArray();

	// set all alien origins, relative to top-left
	initAlienOrigins();

	// draw the aliens!
	drawAliens();

	// set how many aliens are alive
	alienAliveCount = ALIEN_COUNT;
	kill_log.kill = false;

	// direction info
	flapIn = false;
	_aliensMarchingRight = true;
	uint8_t i;
	for(i=0; i<ALIEN_COL_COUNT; i++){
		aliensInColumn[i] = ALIEN_ROW_COUNT;
	}
}

//-----------------------------------------------------------------------------

// shift aliens in any direction
void aliens_march_dir(uint16_t dir){
	uint16_t x, y;
	int16_t x_shift = 0, y_shift = 0;

	aliens_cleanupKills();  // erase any explosions (kills) before moving on
							// this causes no explosion when a alien is killed
							// right before it's about to march
							// The reason this needs to be here is because an
							// artifact is left if killed and then aliens move.

	// Set the (x,y) shifts according to dir input
	if (dir == ALIEN_MARCH_DOWN) {
		x_shift = 0;
		y_shift = ALIEN_SHIFT_Y;
	} else if (dir == ALIEN_MARCH_UP) {
		x_shift = 0;
		y_shift = -ALIEN_SHIFT_Y;
	} else if (dir == ALIEN_MARCH_RIGHT) {
		x_shift = ALIEN_SHIFT_X;
		y_shift = 0;
	} else if (dir == ALIEN_MARCH_LEFT) {
		x_shift = -ALIEN_SHIFT_X;
		y_shift = 0;
	}


	for (y = 0; y < ALIEN_ROW_COUNT; y++) {

		// If we are marching down, we need to start drawing from
		// the downmost column, otherwise the aliens will stack on top
		// of each other and the bottom y_shift rows will be blank
		if (dir == ALIEN_MARCH_DOWN) y = (ALIEN_ROW_COUNT-1) - y;

		// ================== possibly backward y ================

		alien_t alien = alien_symbols[y];	// select alien type
		const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
		for (x = 0; x < ALIEN_COL_COUNT; x++) {

			// If we are marching to the right, we need to start drawing from
			// the rightmost column, otherwise the aliens will stack on top
			// of each other and the right x_shift columns will be blank
			if (dir == ALIEN_MARCH_RIGHT) x = (ALIEN_COL_COUNT-1) - x;

			// -------------- possibly backward x ----------------

			// Grab the alien origin for this given alien (col,row)
			point_t alienOrigin = aliens_getAlienOrigin(x, y);

			// Tell the screen to shift this element by x_shift, y_shift
			if(ALIEN_ALIVE(x,y)){
				screen_shiftElement(symbol, alienOrigin, *alien.bitmapSize,
									x_shift, y_shift, ALIEN_SCALE, ALIEN_COLOR);
			}


			// update internal alien origin
			shiftAlienOrigin(x, y, x_shift*ALIEN_SCALE, y_shift*ALIEN_SCALE);

			// ---------------------------------------------------

			// Switch back to the original x so that the for loop is happy
			if (dir == ALIEN_MARCH_RIGHT) x = (ALIEN_COL_COUNT-1) - x;
		}

		// =======================================================

		// Switch back to the original y so that the for loop is happy
		if (dir == ALIEN_MARCH_DOWN) y = (ALIEN_ROW_COUNT-1) - y;
	}
}

//-----------------------------------------------------------------------------

void aliens_march(){
	// origin of leftmost alien
	point_t left_origin = get_leftPoint();
	// origin of rightmost alien
	point_t right_origin = get_rightPoint();

	// if i'm marching right and my rightmost part of me will be in the
	// margin, drop down onto the next row, change marching direction to left
	if(_aliensMarchingRight && ((right_origin.x + ALIEN_WIDTH) >= SCREEN_WIDTH - SCREEN_EDGE_BUFFER)){
		aliens_march_dir(ALIEN_MARCH_DOWN);
		_aliensMarchingRight = false;

	// if I'm about to be in the left margin, drop down, change marching direction
	} else if(!_aliensMarchingRight && ((left_origin.x) <= SCREEN_EDGE_BUFFER)){
		aliens_march_dir(ALIEN_MARCH_DOWN);
		_aliensMarchingRight = true;

	// If I'm marching right, then march right, dang it!
	} else if(_aliensMarchingRight) {
		aliens_march_dir(ALIEN_MARCH_RIGHT);

	// If I'm marching left, then march left
	} else if(!_aliensMarchingRight) {
		aliens_march_dir(ALIEN_MARCH_LEFT);
	}

	// change the direction of the alien flapping
	flapIn = !flapIn;
}

//-----------------------------------------------------------------------------

void aliens_kill(uint16_t index) {
	// If there are any exploded aliens, clean up the mess
	aliens_cleanupKills();

	// play a sound!
	audio_play_track(SOUND_ALIEN_KILLED);

	// Make sure we should be here: if already dead, bail
	if (!alien_lives_matter[index]) return;

	// kill the alien in memory
	alien_lives_matter[index] = false;

	// Convert index to (x,y) coordinates
	uint16_t y = index / (ALIEN_COL_COUNT);
	uint16_t x = index % (ALIEN_COL_COUNT);

	// Get the origin of the alien we want to kill
	point_t origin = aliens_getAlienOrigin(x, y);

	// draw the explosion in place of that particular alien
	screen_drawSymbol(alien_explosion_12x10, origin, explosionBitmapSize,
						ALIEN_SCALE, SCREEN_COLOR_WHITE);

	// Increase score!
	gameScreen_increaseScore(alien_symbols[y].scoreValue);

	// Keep track of how many aliens are alive
	alienAliveCount--;

	// set up the global kill log to know which area needs to be
	// cleaned up on next kill. Updates on the next march happen
	// automatically because we killed that alien in memory, so
	// the explosion will be removed.
	kill_log.kill = true;
	kill_log.x = x;
	kill_log.y = y;

	// Also, update which are the lowest living aliens

	aliensInColumn[x]--;

	updateLowestLivingAliens(x, y);
//	if(aliens_areLiving()==0){
//		aliens_cleanupKills();
//	}
}

//-----------------------------------------------------------------------------

void aliens_left() {
	_aliensMarchingRight = false;
	aliens_march();
}

//-----------------------------------------------------------------------------

void aliens_right() {
	_aliensMarchingRight = true;
	aliens_march();
}

//-----------------------------------------------------------------------------

void aliens_up() {
	aliens_march_dir(ALIEN_MARCH_UP);
}

//-----------------------------------------------------------------------------

void aliens_down() {
	aliens_march_dir(ALIEN_MARCH_DOWN);
}

//-----------------------------------------------------------------------------


bool alien_isAlive(uint16_t x, uint16_t y) {
	return ALIEN_ALIVE(x,y);
}

//-----------------------------------------------------------------------------

uint16_t alien_xy_to_index(uint16_t x, uint16_t y){
	return ALIEN_XY_TO_INDEX(x,y);
}

//-----------------------------------------------------------------------------

point_t aliens_getAlienOrigin(uint16_t x, uint16_t y) {
	point_t origin = alienOrigins[ALIEN_XY_TO_INDEX(x,y)];
	return origin;
}

//-----------------------------------------------------------------------------

void aliens_getLowestAliens(uint16_t *xArray, uint16_t *yArray) {
	uint8_t i = 0;
	for (i=0; i<ALIEN_COL_COUNT; i++) {
		// deep copy the lowest living alien coordinates
		xArray[i] = lowestAlien_Xs[i];
		yArray[i] = lowestAlien_Ys[i];
	}
}

//-----------------------------------------------------------------------------

uint32_t aliens_areLiving() {
	return alienAliveCount;
}

//-----------------------------------------------------------------------------

void aliens_cleanupKills() {
	if(kill_log.kill){
		// Get the origin of the already exploded alien to clean up.
		point_t origin = aliens_getAlienOrigin(kill_log.x, kill_log.y);

		// Blank the rectangle that the exploded alien was
		screen_drawSymbol(alien_explosion_12x10, origin, explosionBitmapSize,
								ALIEN_SCALE, SCREEN_BG_COLOR);

		// reset kill log
		kill_log.kill = false;
	}
}

//-----------------------------------------------------------------------------

bool aliens_belowBunkers() {
	// Get the lowest living aliens
	uint16_t Xs[ALIEN_COL_COUNT];
	uint16_t Ys[ALIEN_COL_COUNT];
	aliens_getLowestAliens(Xs, Ys);

	bool aliensBelowBunkers = false;

	uint8_t i = 0;
	for (i=0; i<ALIEN_COL_COUNT; i++) {
		// so, grab each lowest living alien per column and see if its
		// (origin.y+its height) is lower than BUNKER_END_Y
		point_t alienOrigin = aliens_getAlienOrigin(Xs[i], Ys[i]);
		if (alienOrigin.y+ALIEN_HEIGHT > BUNKER_END_Y) {
			// this living alien is below the bunkers
			aliensBelowBunkers = true;
			break;
		}
	}

	return aliensBelowBunkers;
}

//-----------------------------------------------------------------------------
// Private Helper Methods
//-----------------------------------------------------------------------------

// draw all the aliens as they currently appear (only living aliens)
void drawAliens() {
	uint16_t row = 0, col = 0;

	// For every alien out of the all the aliens in the whole wide world...
	for (row = 0; row < ALIEN_ROW_COUNT; row++) {
		alien_t alien = alien_symbols[row];	// select alien type
		for (col = 0; col < ALIEN_COL_COUNT; col++) {

			// Convert Alien Coordinates (col,row) into an absolute point (x,y)
			point_t alienOrigin = aliens_getAlienOrigin(col, row);

			// If the alien is dead, color it the screen, else alien color
			uint32_t color = (ALIEN_ALIVE(col,row)) ? ALIEN_COLOR : SCREEN_BG_COLOR;
			const uint32_t* symbol = flapIn ? alien.in : alien.out;	// set direction (up/down)
			// Tell the screen to draw my symbol
			screen_drawSymbol(symbol, alienOrigin, *alien.bitmapSize,
					ALIEN_SCALE, color);
		}
	}
}

//-----------------------------------------------------------------------------

// initializes the alien lives array
void initLivesArray() {
	uint16_t i;
	for(i=0; i < ALIEN_COUNT; i++){
		alien_lives_matter[i] = true;
	}
}

//-----------------------------------------------------------------------------

// initialize the array containing all the origin point of every alien
void initAlienOrigins() {
	uint16_t y, x;
	for(y=0; y<ALIEN_ROW_COUNT; y++){
		alien_t alien = alien_symbols[y];	// select alien type
		for(x=0; x<ALIEN_COL_COUNT; x++){
			point_t origin = {
					.x = (x * alien.bitmapSize->w * ALIEN_SCALE) + x*ALIEN_PADDING_X + SCREEN_EDGE_BUFFER, // account for the screen buffer
					.y = (y * alien.bitmapSize->h * ALIEN_SCALE) + y*ALIEN_PADDING_Y + SCREEN_EDGE_BUFFER + 3*ALIEN_HEIGHT
			};
			alienOrigins[ALIEN_XY_TO_INDEX(x, y)] = origin;

			// set the lowest alien coordinate arrays
			if (y == (ALIEN_ROW_COUNT-1)) {
				// I'm on the last row
				lowestAlien_Xs[x] = x;
				lowestAlien_Ys[x] = y;
			}
		}
	}
}

// ----------------------------------------------------------------------------

void shiftAlienOrigin(uint16_t x, uint16_t y, int16_t xShift, int16_t yShift) {
	point_t *origin = &alienOrigins[ALIEN_XY_TO_INDEX(x,y)];

	// Change the x and y in place (the actual value in the array)
	origin->x += xShift;
	origin->y += yShift;
}

// ----------------------------------------------------------------------------

void updateLowestLivingAliens(uint16_t x, uint16_t y) {
	// If no alien exists in column, setting the y to 0 is fine because
	// the missiles_alienFire function will check if that spot is living
	uint8_t i = 0;

	if (y == lowestAlien_Ys[x]) { // If I'm the lowest living alien
		i = 1; // start looking directly above me

		// while the alien above me is dead, but I'm still looking within range
		while(!ALIEN_ALIVE(x, (y-i)) && (y-i) > 0) i++;

		// Because of the starting condition of i, we need to subtract
		// one from i so that we don't underflow lowestAlien_Ys when
		// we kill the alien at position '0'. (We want it to stay 0)
		//
		// uint16_t is promoted to an int for this subtraction.
		// i.e, (unsigned)0 - (unsigned)1 == -1
		if ((y-i) < 0) i--;

		// here, I either found an alien above me, or I got out of range
		// Due to the previous check, this expression is always safe.
		lowestAlien_Ys[x] = (y-i);
	}

	// If I'm not the lowest alien, that means you just
	// killed an alien above a living alien. Thus,
	// the lowest alien is still lowestAlien_Ys[x].
}

// ----------------------------------------------------------------------------

uint16_t aliens_getFiringCount(){
	uint8_t i, count=0;
	for(i=0; i<ALIEN_COL_COUNT; i++){
		if(ALIEN_ALIVE(lowestAlien_Xs[i], lowestAlien_Ys[i])){
			count++;
		}
	}
	return count;
}

// ----------------------------------------------------------------------------

uint16_t aliens_get_lowest_y(){
	uint8_t i, la;
	uint16_t y=0;
	for(i=0; i<11; i++){
		la = lowestAlien_Ys[i];
		if(la>y){
			y = la;
		}
	}
	return y;
}

// ----------------------------------------------------------------------------

point_t get_leftPoint(){
	uint8_t i;
	point_t alien;

	// starting from the left, if this column exists, get that alien.
	for(i=0; i<ALIEN_COL_COUNT; i++){
		if (aliensInColumn[i]) {
			alien = aliens_getAlienOrigin(i, 0);
			break;
		}
	}

	return alien;
}

// ----------------------------------------------------------------------------

point_t get_rightPoint(){
	uint8_t i;
	point_t alien;

	// starting from the right, if this colum exists, get that alien.
	for(i=ALIEN_COL_COUNT-1; i>0; i--){
		if (aliensInColumn[i]) {
			alien = aliens_getAlienOrigin(i, 0);
			break;
		}
	}

	return alien;
}
