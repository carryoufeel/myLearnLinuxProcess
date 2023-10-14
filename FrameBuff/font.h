/*
 *  Created 1995 by Geert Uytterhoeven
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the main directory of this archive
 *  for more details.
 */

#ifndef _VIDEO_FONT_H
#define _VIDEO_FONT_H

#include <linux/types.h>

struct fbcon_font_desc {
    int idx;
    char *name;
    int width, height;
    char *data;
    int pref;
};

typedef struct hanzi {
	unsigned char str[4];
	unsigned char zimo[32];
}Hanzi_t;

extern Hanzi_t gHanziList[100];

#define VGA8x8_IDX	0
#define VGA8x16_IDX	1
#define PEARL8x8_IDX	2
#define VGA6x11_IDX	3
#define SUN8x16_IDX	4
#define SUN12x22_IDX	5
#define ACORN8x8_IDX	6

#define FONTDATAMAX 4096
extern unsigned char fontdata_8x16[FONTDATAMAX];

/* Max. length for the name of a predefined font */
#define MAX_FONT_NAME	32

#endif /* _VIDEO_FONT_H */
