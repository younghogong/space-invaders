#include "gameScreen.h"

// We need these to know what to erase the next time
static uint32_t currentScore = 0;
static uint8_t currentScoreArray[SCORE_VAL_MAX_LEN] = { 0 };
static uint8_t currentScoreLength = 0;

static uint8_t currentLives = 0;

void drawFloor();
void drawScore();
void drawLives();
uint32_t setScore(uint32_t score);
uint8_t setLives(uint8_t lives);
point_t getCenterStartPoint(uint16_t width, uint16_t height, uint8_t scale);

// ----------------------------------------------------------------------------

void gameScreen_init() {
	drawFloor();
	drawScore();
	drawLives();

	// draw a '0' next to "SCORE"
	setScore(0);

	// draw 3 tanks next to "LIVES"
	setLives(LIVES_MAX);
}

// ----------------------------------------------------------------------------

uint32_t gameScreen_increaseScore(int32_t score) {
	uint32_t newScore = currentScore;

	if ((currentScore + score) < 0) newScore = 0;
	else if ((currentScore + score) > SCORE_VAL_MAX) newScore = SCORE_VAL_MAX;
	else newScore = currentScore + score;

	return setScore(newScore);
}

// ----------------------------------------------------------------------------

uint8_t gameScreen_increaseLives(int8_t lives) {
	uint8_t newLives = currentLives;

	if ((currentLives + lives) < 0) newLives = 0;
	else if ((currentLives + lives) > LIVES_MAX) newLives = LIVES_MAX;
	else newLives = currentLives + lives;

	return setLives(newLives);
}

// ----------------------------------------------------------------------------

uint8_t gameScreen_getTankLives() {
	return currentLives;
}

// ----------------------------------------------------------------------------

void gameScreen_printGameOver() {
	// get the location the text needs to start to be centered
	point_t start_point = text_getCenterStartPoint(wordGameBitmapSize.w+GAME_OVER_SPACE,
			wordGameBitmapSize.h, GAME_OVER_SCALE);

	// draw "GAME"
	screen_drawSymbol(word_game_24x5, start_point, wordGameBitmapSize,
			GAME_OVER_SCALE, SCREEN_COLOR_WHITE);

	// shift over for a space
	start_point.x += wordGameBitmapSize.w*GAME_OVER_SCALE + GAME_OVER_SPACE;

	// draw "OVER"
	screen_drawSymbol(word_over_24x5, start_point, wordOverBitmapSize, GAME_OVER_SCALE, SCREEN_COLOR_WHITE);
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

void drawFloor() {
	point_t origin = { .x = FLOOR_ORIGIN_X, .y = FLOOR_ORIGIN_Y };

	uint8_t i = 0;
	for (i=0; i<(SCREEN_WIDTH/FLOOR_WIDTH); i++) {
		screen_drawSymbol(floor_32x2, origin, floorBitmapSize, FLOOR_SCALE, FLOOR_COLOR);

		// shift the origin over a bit
		origin.x += FLOOR_WIDTH;
	}

}

// ----------------------------------------------------------------------------

void drawScore() {
	point_t origin = { .x = SCORE_TXT_ORIGIN_X, .y = SCORE_TXT_ORIGIN_Y };

	// Draw the text "SCORE"
	screen_drawSymbol(word_score_30x5, origin, wordScoreBitmapSize, SCORE_TXT_SCALE, SCORE_TXT_COLOR);
}

// ----------------------------------------------------------------------------

void drawLives() {
	point_t origin = { .x = LIVES_TXT_ORIGIN_X, .y = LIVES_TXT_ORIGIN_Y };

	// Draw the text "SCORE"
	screen_drawSymbol(word_lives_24x5, origin, wordLivesBitmapSize, LIVES_TXT_SCALE, LIVES_TXT_COLOR);
}

// ----------------------------------------------------------------------------

uint8_t setLives(uint8_t lives) {
	point_t origin = { .x = LIVES_TANK_ORIGIN_X, .y = LIVES_TANK_ORIGIN_Y };
	uint8_t i = 0;

	for (i=0; i<LIVES_MAX; i++) {
		// Find out if this tank live should be drawn or not
		uint32_t color = (i<lives) ? LIVES_TANK_COLOR : SCREEN_BG_COLOR;

		// Draw a tank at the given origin
		screen_drawSymbol(tank_15x8, origin, tankBitmapSize, LIVES_TANK_SCALE, color);

		// Shift the origin over to the next tank
		origin.x += (LIVES_TANK_WIDTH + LIVES_TANK_PADDING);
	}

	// save lives for next time
	currentLives = lives;

	return currentLives;
}

// ----------------------------------------------------------------------------

uint32_t setScore(uint32_t score) {
	point_t origin = { .x = SCORE_VAL_ORIGIN_X, .y = SCORE_VAL_ORIGIN_Y };

	// Get score info as an array so we can loop through each digit
	text_explodeNumber(score, SCORE_VAL_MAX_LEN, currentScoreArray, &currentScoreLength);

	// actually draw the exploded array to the screen
	text_drawNumberString(currentScoreArray, currentScoreLength, SCORE_VAL_MAX_LEN,
					origin, SCORE_VAL_SCALE, SCORE_VAL_COLOR);

	// save score for next time
	currentScore = score;

	return currentScore;
}

// ----------------------------------------------------------------------------
