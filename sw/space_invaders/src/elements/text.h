/*
 * text.h
 *
 *  Created on: Sep 29, 2015
 *      Author: superman
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "bitmapDB.h"
#include "../globals.h"
#include "../screen/screen.h"
#define TEXT_SCALE 3

void text_print_game_over();
void text_print_init();



//////////////////////////////////////////////////////


// Font data for Gill Sans MT 9pt
extern const uint32_t bitmaps[];
extern const FONT_INFO fontInfo;
extern const FONT_CHAR_INFO descriptors[];


////////////////////////////////////////////////////

//static const symbolsize_t charsize = {
//		.w = 8,
//		.h = 9
//};


static const uint32_t COLON[] = { // @100 ':' (1 pixels wide)
		0x00, //
		0x00, //
		0x00, //
		0x80, // #
		0x00, //
		0x00, //
		0x00, //
		0x00, //
		0x80, // #
		0x00, //
};


static const uint32_t ZERO[] = { // @0 '0' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const uint32_t ONE[] = {	// @10 '1' (3 pixels wide)
	0x20, //   #
	0xE0, // ###
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x00, //
};


static const uint32_t TWO[] = {	// @20 '2' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x08, //     #
	0x08, //     #
	0x10, //    #
	0x20, //   #
	0x40, //  #
	0x80, // #
	0xF8, // #####
	0x00, //
};


static const uint32_t THREE[] = {	// @30 '3' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x08, //     #
	0x08, //     #
	0x30, //   ##
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const uint32_t FOUR[] = {	// @40 '4' (5 pixels wide)
	0x10, //    #
	0x30, //   ##
	0x30, //   ##
	0x50, //  # #
	0x50, //  # #
	0x90, // #  #
	0xF8, // #####
	0x10, //    #
	0x10, //    #
	0x00, //
};


static const uint32_t FIVE[] = {	// @50 '5' (5 pixels wide)
	0xF8, // #####
	0x80, // #
	0x80, // #
	0xF0, // ####
	0x88, // #   #
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const int SIX[] = {	// @60 '6' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x80, // #
	0x80, // #
	0xF0, // ####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const int SEVEN[] = {	// @70 '7' (5 pixels wide)
	0xF8, // #####
	0x08, //     #
	0x10, //    #
	0x10, //    #
	0x20, //   #
	0x20, //   #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x00, //
};


static const int EIGHT[] = {	// @80 '8' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ###
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const uint32_t NINE[] = {	// @90 '9' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x78, //  ####
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const uint32_t A[] = {	// @100 'A' (7 pixels wide)
	0x10, //    #
	0x10, //    #
	0x28, //   # #
	0x28, //   # #
	0x44, //  #   #
	0x44, //  #   #
	0x7C, //  #####
	0x82, // #     #
	0x82, // #     #
	0x00, //
};


static const uint32_t B[] = {	// @110 'B' (5 pixels wide)
	0xF0, // ####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF0, // ####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF0, // ####
	0x00, //
};


static const uint32_t C[] = {	// @120 'C' (6 pixels wide)
	0x78, //  ####
	0x84, // #    #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x84, // #    #
	0x78, //  ####
	0x00, //
};


static const uint32_t D[] = {	// @130 'D' (6 pixels wide)
	0xF0, // ####
	0x88, // #   #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x88, // #   #
	0xF0, // ####
	0x00, //
};


static const uint32_t E[] = {	// @140 'E' (5 pixels wide)
	0xF8, // #####
	0x80, // #
	0x80, // #
	0x80, // #
	0xF0, // ####
	0x80, // #
	0x80, // #
	0x80, // #
	0xF8, // #####
	0x00, //
};


static const uint32_t F[] = {	// @150 'F' (5 pixels wide)
	0xF8, // #####
	0x80, // #
	0x80, // #
	0x80, // #
	0xF0, // ####
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //
};


static const uint32_t G[] = {	// @160 'G' (6 pixels wide)
	0x78, //  ####
	0x84, // #    #
	0x80, // #
	0x80, // #
	0x9C, // #  ###
	0x84, // #    #
	0x84, // #    #
	0x8C, // #   ##
	0x74, //  ### #
	0x00, //
};


static const uint32_t H[] = {	// @170 'H' (6 pixels wide)
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0xFC, // ######
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x00, //
};


static const uint32_t I[] = {	// @180 'I' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //
};


static const uint32_t J[] = {	// @190 'J' (4 pixels wide)
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x90, // #  #
	0x90, // #  #
	0x60, //  ##
	0x00, //
};


static const uint32_t K[] = {	// @200 'K' (6 pixels wide)
	0x88, // #   #
	0x90, // #  #
	0xA0, // # #
	0xC0, // ##
	0xC0, // ##
	0xA0, // # #
	0x90, // #  #
	0x88, // #   #
	0x84, // #    #
	0x00, //
};


static const uint32_t L[] = {	// @210 'L' (5 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0xF8, // #####
	0x00, //
};


static const uint32_t M[] = {	// @220 'M' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0xC6, // ##   ##
	0xC6, // ##   ##
	0xAA, // # # # #
	0xAA, // # # # #
	0x92, // #  #  #
	0x92, // #  #  #
	0x82, // #     #
	0x00, //
};


static const uint32_t N[] = {	// @230 'N' (6 pixels wide)
	0x84, // #    #
	0xC4, // ##   #
	0xC4, // ##   #
	0xA4, // # #  #
	0xA4, // # #  #
	0x94, // #  # #
	0x8C, // #   ##
	0x8C, // #   ##
	0x84, // #    #
	0x00, //
};


static const uint32_t O[] = {	// @240 'O' (6 pixels wide)
	0x78, //  ####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  ####
	0x00, //
};


static const uint32_t P[] = {	// @250 'P' (6 pixels wide)
	0xF8, // #####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0xF8, // #####
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //
};


static const uint32_t Q[] = {	// @260 'Q' (6 pixels wide)
	0x78, //  ####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x94, // #  # #
	0x8C, // #   ##
	0x78, //  ####
	0x04, //      #
};


static const uint32_t R[] = {	// @270 'R' (6 pixels wide)
	0xF8, // #####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0xF8, // #####
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x00, //
};


static const uint32_t S[] = {	// @280 'S' (5 pixels wide)
	0x70, //  ###
	0x88, // #   #
	0x80, // #
	0x80, // #
	0x70, //  ###
	0x08, //     #
	0x08, //     #
	0x88, // #   #
	0x70, //  ###
	0x00, //
};


static const uint32_t T[] = {	// @290 'T' (5 pixels wide)
	0xF8, // #####
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x20, //   #
	0x00, //
};


static const uint32_t U[] = {	// @300 'U' (6 pixels wide)
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x84, // #    #
	0x78, //  ####
	0x00, //
};


static const uint32_t V[] = {	// @310 'V' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   #
	0x44, //  #   #
	0x44, //  #   #
	0x28, //   # #
	0x28, //   # #
	0x10, //    #
	0x10, //    #
	0x00, //
};


static const uint32_t W[] = {	// @320 'W' (11 pixels wide)
	0x80, 	0x20, // #         #
	0x80, 	0x20, // #         #
	0x44, 	0x40, //  #   #   #
	0x44, 	0x40, //  #   #   #
	0x44, 	0x40, //  #   #   #
	0x2A, 	0x80, //   # # # #
	0x2A, 	0x80, //   # # # #
	0x11, 	0x00, //    #   #
	0x11, 	0x00, //    #   #
	0x00, 	0x00, //
};


static const uint32_t X[] = {	// @340 'X' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   #
	0x28, //   # #
	0x10, //    #
	0x28, //   # #
	0x44, //  #   #
	0x82, // #     #
	0x82, // #     #
	0x00, //
};


static const uint32_t Y[] = {	// @350 'Y' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   #
	0x28, //   # #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x00, //
};


static const uint32_t Z[] = {	// @360 'Z' (7 pixels wide)
	0xFE, // #######
	0x02, //       #
	0x04, //      #
	0x08, //     #
	0x10, //    #
	0x20, //   #
	0x40, //  #
	0x80, // #
	0xFE, // #######
	0x00, //
};

static const uint32_t SPACE[] = { // @0 '0' (5 pixels wide)
	0x00, //  ###
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, // #   #
	0x00, //  ###
	0x00, //
};

//
//  Font data for Tahoma 8pt
//


//typedef struct {
//	uint16_t h; //  Character height
//	.start = '0', //  Start character
//	.end = 'Z', //  End character
//	.sw = 2, //  Width, in pixels, of space character
//	.desc = tahoma_8ptDescriptors, //  Character descriptor array
//	.bitarray = tahoma_8ptBitmaps, //  Character bitmap array
//};
//// Font data for Tahoma 8pt
//extern const uint_8 tahoma_8ptBitmaps[];
//extern const FONT_INFO tahoma_8ptFontInfo;
//extern const FONT_CHAR_INFO tahoma_8ptDescriptors[];
//
//// Character bitmaps for Tahoma 8pt
//const uint_8 tahoma_8ptBitmaps[] =
//{
//	// @0 '0' (6 pixels wide)
//	0x78, //  ####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0x78, //  ####
//	0x00, //
//	0x00, //
//
//	// @10 '1' (4 pixels wide)
//	0x60, //  ##
//	0xE0, // ###
//	0x60, //  ##
//	0x60, //  ##
//	0x60, //  ##
//	0x60, //  ##
//	0x60, //  ##
//	0xF0, // ####
//	0x00, //
//	0x00, //
//
//	// @20 '2' (6 pixels wide)
//	0x78, //  ####
//	0xCC, // ##  ##
//	0x0C, //     ##
//	0x18, //    ##
//	0x30, //   ##
//	0x60, //  ##
//	0xC0, // ##
//	0xFC, // ######
//	0x00, //
//	0x00, //
//
//	// @30 '3' (6 pixels wide)
//	0x78, //  ####
//	0xCC, // ##  ##
//	0x0C, //     ##
//	0x38, //   ###
//	0x0C, //     ##
//	0x0C, //     ##
//	0xCC, // ##  ##
//	0x78, //  ####
//	0x00, //
//	0x00, //
//
//	// @40 '4' (6 pixels wide)
//	0x08, //     #
//	0x18, //    ##
//	0x38, //   ###
//	0x58, //  # ##
//	0x98, // #  ##
//	0xFC, // ######
//	0x18, //    ##
//	0x18, //    ##
//	0x00, //
//	0x00, //
//
//	// @50 '5' (6 pixels wide)
//	0x7C, //  #####
//	0x60, //  ##
//	0x60, //  ##
//	0x78, //  ####
//	0x0C, //     ##
//	0x0C, //     ##
//	0xCC, // ##  ##
//	0x78, //  ####
//	0x00, //
//	0x00, //
//
//	// @60 '6' (6 pixels wide)
//	0x78, //  ####
//	0xC0, // ##
//	0xC0, // ##
//	0xF8, // #####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0x78, //  ####
//	0x00, //
//	0x00, //
//
//	// @70 '7' (6 pixels wide)
//	0xFC, // ######
//	0x0C, //     ##
//	0x18, //    ##
//	0x18, //    ##
//	0x18, //    ##
//	0x30, //   ##
//	0x30, //   ##
//	0x30, //   ##
//	0x00, //
//	0x00, //
//
//	// @80 '8' (6 pixels wide)
//	0x78, //  ####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0x78, //  ####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0x78, //  ####
//	0x00, //
//	0x00, //
//
//	// @90 '9' (6 pixels wide)
//	0x78, //  ####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0x7C, //  #####
//	0x0C, //     ##
//	0x0C, //     ##
//	0x78, //  ####
//	0x00, //
//	0x00, //
//
//	// @100 ':' (2 pixels wide)
//	0x00, //
//	0x00, //
//	0xC0, // ##
//	0xC0, // ##
//	0x00, //
//	0x00, //
//	0xC0, // ##
//	0xC0, // ##
//	0x00, //
//	0x00, //
//
//	// @110 'A' (7 pixels wide)
//	0x38, //   ###
//	0x38, //   ###
//	0x6C, //  ## ##
//	0x6C, //  ## ##
//	0x6C, //  ## ##
//	0xFE, // #######
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0x00, //
//	0x00, //
//
//	// @120 'B' (6 pixels wide)
//	0xF8, // #####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xF8, // #####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xF8, // #####
//	0x00, //
//	0x00, //
//
//	// @130 'C' (6 pixels wide)
//	0x7C, //  #####
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0x7C, //  #####
//	0x00, //
//	0x00, //
//
//	// @140 'D' (7 pixels wide)
//	0xF8, // #####
//	0xCC, // ##  ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xCC, // ##  ##
//	0xF8, // #####
//	0x00, //
//	0x00, //
//
//	// @150 'E' (5 pixels wide)
//	0xF8, // #####
//	0xC0, // ##
//	0xC0, // ##
//	0xF8, // #####
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xF8, // #####
//	0x00, //
//	0x00, //
//
//	// @160 'F' (5 pixels wide)
//	0xF8, // #####
//	0xC0, // ##
//	0xC0, // ##
//	0xF8, // #####
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0x00, //
//	0x00, //
//
//	// @170 'G' (7 pixels wide)
//	0x7E, //  ######
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xCE, // ##  ###
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0x7E, //  ######
//	0x00, //
//	0x00, //
//
//	// @180 'H' (7 pixels wide)
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xFE, // #######
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0x00, //
//	0x00, //
//
//	// @190 'I' (4 pixels wide)
//	0xF0, // ####
//	0x60, //  ##
//	0x60, //  ##
//	0x60, //  ##
//	0x60, //  ##
//	0x60, //  ##
//	0x60, //  ##
//	0xF0, // ####
//	0x00, //
//	0x00, //
//
//	// @200 'J' (5 pixels wide)
//	0x78, //  ####
//	0x18, //    ##
//	0x18, //    ##
//	0x18, //    ##
//	0x18, //    ##
//	0x18, //    ##
//	0x18, //    ##
//	0xF0, // ####
//	0x00, //
//	0x00, //
//
//	// @210 'K' (6 pixels wide)
//	0xCC, // ##  ##
//	0xD8, // ## ##
//	0xF0, // ####
//	0xE0, // ###
//	0xE0, // ###
//	0xF0, // ####
//	0xD8, // ## ##
//	0xCC, // ##  ##
//	0x00, //
//	0x00, //
//
//	// @220 'L' (5 pixels wide)
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0xF8, // #####
//	0x00, //
//	0x00, //
//
//	// @230 'M' (9 pixels wide)
//	0xC1, 0x80, // ##     ##
//	0xE3, 0x80, // ###   ###
//	0xF7, 0x80, // #### ####
//	0xBD, 0x80, // # #### ##
//	0x99, 0x80, // #  ##  ##
//	0x81, 0x80, // #      ##
//	0x81, 0x80, // #      ##
//	0x81, 0x80, // #      ##
//	0x00, 0x00, //
//	0x00, 0x00, //
//
//	// @250 'N' (6 pixels wide)
//	0xC4, // ##   #
//	0xE4, // ###  #
//	0xF4, // #### #
//	0xBC, // # ####
//	0x9C, // #  ###
//	0x8C, // #   ##
//	0x84, // #    #
//	0x84, // #    #
//	0x00, //
//	0x00, //
//
//	// @260 'O' (7 pixels wide)
//	0x7C, //  #####
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0x7C, //  #####
//	0x00, //
//	0x00, //
//
//	// @270 'P' (6 pixels wide)
//	0xF8, // #####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xF8, // #####
//	0xC0, // ##
//	0xC0, // ##
//	0xC0, // ##
//	0x00, //
//	0x00, //
//
//	// @280 'Q' (7 pixels wide)
//	0x7C, //  #####
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0x7C, //  #####
//	0x18, //    ##
//	0x0E, //     ###
//
//	// @290 'R' (7 pixels wide)
//	0xF8, // #####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xF8, // #####
//	0xD8, // ## ##
//	0xCC, // ##  ##
//	0xC6, // ##   ##
//	0x00, //
//	0x00, //
//
//	// @300 'S' (6 pixels wide)
//	0x7C, //  #####
//	0xC0, // ##
//	0xC0, // ##
//	0xF8, // #####
//	0x7C, //  #####
//	0x0C, //     ##
//	0x0C, //     ##
//	0xF8, // #####
//	0x00, //
//	0x00, //
//
//	// @310 'T' (6 pixels wide)
//	0xFC, // ######
//	0x30, //   ##
//	0x30, //   ##
//	0x30, //   ##
//	0x30, //   ##
//	0x30, //   ##
//	0x30, //   ##
//	0x30, //   ##
//	0x00, //
//	0x00, //
//
//	// @320 'U' (7 pixels wide)
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0xC6, // ##   ##
//	0x7C, //  #####
//	0x00, //
//	0x00, //
//
//	// @330 'V' (6 pixels wide)
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0x78, //  ####
//	0x78, //  ####
//	0x78, //  ####
//	0x30, //   ##
//	0x30, //   ##
//	0x00, //
//	0x00, //
//
//	// @340 'W' (10 pixels wide)
//	0xCC, 0xC0, // ##  ##  ##
//	0xCC, 0xC0, // ##  ##  ##
//	0xCC, 0xC0, // ##  ##  ##
//	0x6D, 0x80, //  ## ## ##
//	0x7F, 0x80, //  ########
//	0x73, 0x80, //  ###  ###
//	0x33, 0x00, //   ##  ##
//	0x33, 0x00, //   ##  ##
//	0x00, 0x00, //
//	0x00, 0x00, //
//
//	// @360 'X' (6 pixels wide)
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0x78, //  ####
//	0x30, //   ##
//	0x30, //   ##
//	0x78, //  ####
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0x00, //
//	0x00, //
//
//	// @370 'Y' (6 pixels wide)
//	0xCC, // ##  ##
//	0xCC, // ##  ##
//	0x78, //  ####
//	0x78, //  ####
//	0x30, //   ##
//	0x30, //   ##
//	0x30, //   ##
//	0x30, //   ##
//	0x00, //
//	0x00, //
//
//	// @380 'Z' (6 pixels wide)
//	0xFC, // ######
//	0x0C, //     ##
//	0x1C, //    ###
//	0x38, //   ###
//	0x70, //  ###
//	0xE0, // ###
//	0xC0, // ##
//	0xFC, // ######
//	0x00, //
//	0x00, //
//};
//
//// Character descriptors for Tahoma 8pt
//// { [Char width in bits], [Offset into tahoma_8ptCharBitmaps in bytes] }
//const FONT_CHAR_INFO tahoma_8ptDescriptors[] =
//{
//	{6, 0}, 		// 0
//	{4, 10}, 		// 1
//	{6, 20}, 		// 2
//	{6, 30}, 		// 3
//	{6, 40}, 		// 4
//	{6, 50}, 		// 5
//	{6, 60}, 		// 6
//	{6, 70}, 		// 7
//	{6, 80}, 		// 8
//	{6, 90}, 		// 9
//	{2, 100}, 		// :
//	{0, 0}, 		// ;
//	{0, 0}, 		// <
//	{0, 0}, 		// =
//	{0, 0}, 		// >
//	{0, 0}, 		// ?
//	{0, 0}, 		// @
//	{7, 110}, 		// A
//	{6, 120}, 		// B
//	{6, 130}, 		// C
//	{7, 140}, 		// D
//	{5, 150}, 		// E
//	{5, 160}, 		// F
//	{7, 170}, 		// G
//	{7, 180}, 		// H
//	{4, 190}, 		// I
//	{5, 200}, 		// J
//	{6, 210}, 		// K
//	{5, 220}, 		// L
//	{9, 230}, 		// M
//	{6, 250}, 		// N
//	{7, 260}, 		// O
//	{6, 270}, 		// P
//	{7, 280}, 		// Q
//	{7, 290}, 		// R
//	{6, 300}, 		// S
//	{6, 310}, 		// T
//	{7, 320}, 		// U
//	{6, 330}, 		// V
//	{10, 340}, 		// W
//	{6, 360}, 		// X
//	{6, 370}, 		// Y
//	{6, 380}, 		// Z
//};
//
//// Font information for Tahoma 8pt
//const FONT_INFO tahoma_8ptFontInfo =
//{
//	.h = 10, //  Character height
//	.start = '0', //  Start character
//	.end = 'Z', //  End character
//	.sw = 2, //  Width, in pixels, of space character
//	.desc = tahoma_8ptDescriptors, //  Character descriptor array
//	.bitarray = tahoma_8ptBitmaps, //  Character bitmap array
//};



#endif /* TEXT_H_ */
