#include "bunkers.h"

#define STATUS_MASK 	0x07
#define BUNKER_SYMBOLS	4

static bunker_t bunker_array[BUNKER_COUNT];

// array of three different types of bunker damage patterns
static const uint32_t* bunker_damage_symbols[BUNKER_SYMBOLS] = {
		bunkerDamage0_6x6,
		bunkerDamage1_6x6,
		bunkerDamage2_6x6,
		bunkerDamage3_6x6
};

// function definitions
void bunkers_draw();
void bunkers_init_origins();
void bunkers_init_sub_origins(point_t origin, point_t *sub_points);
uint8_t bunker_point_status(uint8_t bunker_index, uint8_t sub_index);
void bunker_point_damage(uint8_t bunker_index, uint8_t sub_index);

// ----------------------------------------------------------------------------

void bunkers_init() {
	// create the origins of the bunkers
	bunkers_init_origins();
	// draw the bunkers
	bunkers_draw();
}

// ----------------------------------------------------------------------------

bool bunkers_isPointEroded(uint8_t bunker_index, uint8_t sub_index){
	uint8_t status = bunker_point_status(bunker_index, sub_index);

	// is the bunker "sub-block" completely eroded?
	return (status >= BUNKER_ERODED_STATUS);
}

// ----------------------------------------------------------------------------

void bunkers_damage(uint8_t index, uint8_t sub_index){
	bunker_t* bunker = &bunker_array[index];
	point_t point = bunker->sub_points[sub_index];
	uint8_t status = bunker_point_status(index, sub_index);
	const uint32_t* symbol = bunker_damage_symbols[status];
	bunker_point_damage(index, sub_index);
	// update the background frame (used for reference only)
	screen_bgDrawSymbol(symbol, point, bunkerDamageBitmapSize, BUNKER_ERODE_SCALE, SCREEN_COLOR_BLACK);
	// draw the damage to the screen
	screen_drawSymbol(symbol, point, bunkerDamageBitmapSize, BUNKER_ERODE_SCALE, SCREEN_BG_COLOR);
}

// ----------------------------------------------------------------------------

bunker_t bunkers_getBunker(uint8_t index){
	return bunker_array[index];
}

// ----------------------------------------------------------------------------
// Private Helper Methods
// ----------------------------------------------------------------------------

// initialize bunkers
void bunkers_init_origins(){
	uint8_t i;
	bunker_t* bunker;
	for(i=0; i<BUNKER_COUNT; i++){
		point_t origin = {
				.x = i*(SCREEN_WIDTH/BUNKER_COUNT) + BUNKER_START_XOFFSET,
				.y = BUNKER_START_Y
		};
		bunker = &bunker_array[i];
		bunker->origin = origin;
		bunker->status = 0;
		bunker->sub_points = malloc(BUNKER_SUB_ORIGIN_COUNT * sizeof bunker->sub_points);
		// initialize the coordinates of all 10 sub-origins of the bunker
		bunkers_init_sub_origins(origin, bunker->sub_points);

	}
}

// ----------------------------------------------------------------------------

void bunkers_init_sub_origins(point_t origin, point_t *sub_points) {
	uint8_t i, j, k=0, x_offset=0, y_offset=0;
	for(j=0; j<3; j++){
		for(i=0; i<4; i++){
			if(!(j==2 && (i==1 || i==2))){ // ignore blocks 10 and 11 (empty)
				sub_points[k].x = origin.x + x_offset;
				sub_points[k].y = origin.y + y_offset;
				k++;
			}
			x_offset += BUNKER_SUB_ORIGIN_WIDTH;
		}
		x_offset = 0;
		y_offset += BUNKER_SUB_ORIGIN_HEIGHT;
	}
}

// ----------------------------------------------------------------------------

uint8_t bunker_point_status(uint8_t bunker_index, uint8_t sub_index) {
	// get the status of the bunker "sub-block"
	return (bunker_array[bunker_index].status >> sub_index*STATUS_BIT_LENGTH) & STATUS_MASK;
}

// ----------------------------------------------------------------------------

// increment the damage of the bunker "sub-block"
void bunker_point_damage(uint8_t bunker_index, uint8_t sub_index) {
	// get the status of all the points, i.e., the entire bunker
	uint32_t status_all = bunker_array[bunker_index].status;

	// get the current sub-block status
	uint8_t status = bunker_point_status(bunker_index, sub_index);

	// increment the damage of the sub-block of this bunker
	status++;

	// create a mask of the bits you want to set
	uint32_t bit_mask = (STATUS_MASK << (sub_index*STATUS_BIT_LENGTH));
	status_all = (status_all & (~bit_mask)) | (status << (sub_index*STATUS_BIT_LENGTH));

	// write the bits back for next time
	bunker_array[bunker_index].status = status_all;
}

// ----------------------------------------------------------------------------

// draw all bunkers to the screen
void bunkers_draw(){
	uint8_t i;
	for(i=0; i<BUNKER_COUNT; i++){
		point_t origin = bunker_array[i].origin;
		screen_drawSymbol(bunker_24x18, origin, bunkerBitmapSize,
				BUNKER_SCALE, BUNKER_COLOR);
		screen_bgDrawSymbol(bunker_24x18, origin, bunkerBitmapSize,
				BUNKER_SCALE, BUNKER_COLOR);
//		draw_sub_points(bunker_array[i]);
	}

}

// ----------------------------------------------------------------------------

// DEBUG FUNCTION ~ include in bunkers_draw()
void draw_sub_points(bunker_t bunker){
	uint8_t i;
	uint32_t bit = 0x1;
	symbolsize_t size = {.w=1, .h=1};
	for(i=0; i<BUNKER_SUB_ORIGIN_COUNT; i++){
		screen_drawSymbol(&bit, bunker.sub_points[i], size,
						BUNKER_SCALE, SCREEN_COLOR_RED);
	}
}

// ----------------------------------------------------------------------------
