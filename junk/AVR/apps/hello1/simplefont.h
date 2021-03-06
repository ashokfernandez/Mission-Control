#ifndef SIMPLEFONT_H_
#define SIMPLEFONT_H_

#include <stdint.h>

static uint8_t font[] = {
		/*   */		0x00, 0x00, 0x00, 0x00, 0x00,
		/* ! */		0x00, 0x00, 0x5F, 0x00, 0x00,
		/* " */		0x00, 0x03, 0x00, 0x03, 0x00,
		/* # */		0x12, 0x7F, 0x12, 0x7F, 0x12,
		/* $ */		0x26, 0x49, 0x7F, 0x49, 0x32,
		/* % */		0x43, 0x33, 0x08, 0x66, 0x61,
		/* & */		0x36, 0x49, 0x55, 0x23, 0x50,
		/* ' */		0x00, 0x00, 0x03, 0x00, 0x00,
		/* ( */		0x00, 0x1C, 0x63, 0x41, 0x00,
		/* ) */		0x00, 0x41, 0x63, 0x1C, 0x00,
		/* * */		0x49, 0x2A, 0x7F, 0x2A, 0x49,
		/* + */		0x08, 0x08, 0x7F, 0x08, 0x08,
		/* , */		0x00, 0x40, 0x70, 0x00, 0x00,
		/* - */		0x08, 0x08, 0x08, 0x08, 0x08,
		/* . */		0x00, 0x00, 0x40, 0x00, 0x00,
		/* / */		0x40, 0x30, 0x08, 0x06, 0x01,
		/* 0 */		0x3E, 0x51, 0x49, 0x45, 0x3E,
		/* 1 */		0x00, 0x42, 0x7F, 0x40, 0x00,
		/* 2 */		0x42, 0x61, 0x51, 0x49, 0x46,
		/* 3 */		0x21, 0x41, 0x45, 0x4B, 0x31,
		/* 4 */		0x18, 0x14, 0x12, 0x7F, 0x10,
		/* 5 */		0x27, 0x45, 0x45, 0x45, 0x39,
		/* 6 */		0x3C, 0x4A, 0x49, 0x49, 0x30,
		/* 7 */		0x01, 0x01, 0x79, 0x05, 0x03,
		/* 8 */		0x37, 0x49, 0x49, 0x49, 0x36,
		/* 9 */		0x06, 0x49, 0x49, 0x29, 0x1E,
		/* : */		0x00, 0x00, 0x14, 0x00, 0x00,
		/* ; */		0x00, 0x40, 0x74, 0x00, 0x00,
		/* < */		0x00, 0x08, 0x14, 0x22, 0x41,
		/* = */		0x14, 0x14, 0x14, 0x14, 0x14,
		/* > */		0x41, 0x22, 0x14, 0x08, 0x00,
		/* ? */		0x00, 0x06, 0x59, 0x05, 0x02,
		/* @ */		0x3E, 0x41, 0x4D, 0x51, 0x4E,
		/* A */		0x7E, 0x11, 0x11, 0x11, 0x7E,
		/* B */		0x41, 0x7F, 0x49, 0x49, 0x36,
		/* C */		0x3E, 0x41, 0x41, 0x41, 0x22,
		/* D */		0x41, 0x7F, 0x41, 0x41, 0x3E,
		/* E */		0x7F, 0x49, 0x49, 0x49, 0x49,
		/* F */		0x7F, 0x09, 0x09, 0x09, 0x01,
		/* G */		0x3E, 0x41, 0x41, 0x49, 0x7A,
		/* H */		0x7F, 0x08, 0x08, 0x08, 0x7F,
		/* I */		0x00, 0x41, 0x7F, 0x41, 0x00,
		/* J */		0x20, 0x40, 0x41, 0x3F, 0x01,
		/* K */		0x7F, 0x08, 0x14, 0x22, 0x41,
		/* L */		0x7F, 0x40, 0x40, 0x40, 0x40,
		/* M */		0x7F, 0x02, 0x0C, 0x02, 0x7F,
		/* N */		0x7F, 0x06, 0x08, 0x30, 0x7F,
		/* O */		0x3E, 0x41, 0x41, 0x41, 0x3E,
		/* P */		0x7F, 0x09, 0x09, 0x09, 0x06,
		/* Q */		0x7E, 0x41, 0x51, 0x21, 0x5E,
		/* R */		0x7F, 0x09, 0x19, 0x29, 0x46,
		/* S */		0x26, 0x49, 0x49, 0x49, 0x32,
		/* T */		0x01, 0x01, 0x7F, 0x01, 0x01,
		/* U */		0x3F, 0x40, 0x40, 0x40, 0x3F,
		/* V */		0x1F, 0x20, 0x40, 0x20, 0x1F,
		/* W */		0x7F, 0x20, 0x18, 0x20, 0x7F,
		/* X */		0x63, 0x14, 0x08, 0x14, 0x63,
		/* Y */		0x07, 0x08, 0x70, 0x08, 0x07,
		/* Z */		0x61, 0x51, 0x49, 0x45, 0x43,
		/* [ */		0x00, 0x7F, 0x41, 0x41, 0x00,
		/* \ */		0x01, 0x06, 0x08, 0x30, 0x40,
		/* ] */		0x00, 0x41, 0x41, 0x7F, 0x00,
		/* ^ */		0x00, 0x06, 0x01, 0x06, 0x00,
		/* _ */		0x40, 0x40, 0x40, 0x40, 0x40,
		/* ` */		0x00, 0x01, 0x02, 0x00, 0x00
};

#define FONT_WIDTH             5
#define FONT_ASCII_OFFSET      ' '
#define FONT_TABLE_SIZE        (sizeof(font)/FONT_WIDTH)

#endif

