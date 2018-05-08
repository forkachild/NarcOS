#ifndef _GFX_H_
#define _GFX_H_

#include <stddef.h>
#include <stdint.h>
#include <mailbox.h>

#define COLOR_RED   0xFFFF0000
#define COLOR_GREEN   0xFF00FF00
#define COLOR_BLUE   0xFF0000FF
#define COLOR_YELLOW   0xFFFFFF00
#define COLOR_CYAN   0xFF00FFFF
#define COLOR_MAGENTA   0xFFFF00FF

volatile uint32_t __attribute__((aligned(16))) mbox[36];

uint32_t width, height, depth, pitch;
uint8_t *pointer;

int32_t gfx_init(uint32_t, uint32_t, uint32_t);
void gfx_clear_screen(uint32_t);

#endif