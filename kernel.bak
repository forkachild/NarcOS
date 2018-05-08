#include <stddef.h>
#include <stdint.h>
#include "raspireg.h"

#define DISPLAY_WIDTH	1920
#define DISPLAY_HEIGHT	1080

extern void PUT32(uint32_t, uint32_t);
extern uint32_t GET32(uint32_t);
extern void dummy(void);

volatile uint32_t counter, gpu_p, x, y;

static inline void gpio_init()
{
	PUT32(GPFSEL1, (1 << 24));
}

static inline void led_on()
{
	PUT32(GPSET0, (1 << 18));
}

static inline void led_off()
{
	PUT32(GPCLR0, (1 << 18));
}

void mailbox_init()
{
	PUT32(0x40040000, DISPLAY_WIDTH); /* #0 Physical Width */
    PUT32(0x40040004, DISPLAY_HEIGHT); /* #4 Physical Height */
    PUT32(0x40040008, DISPLAY_WIDTH); /* #8 Virtual Width */
    PUT32(0x4004000C, DISPLAY_HEIGHT); /* #12 Virtual Height */
    PUT32(0x40040010, 0); /* #16 GPU - Pitch */
    PUT32(0x40040014, 32); /* #20 Bit Depth */
    PUT32(0x40040018, 0); /* #24 X */
    PUT32(0x4004001C, 0); /* #28 Y */
    PUT32(0x40040020, 0); /* #32 GPU - Pointer */
    PUT32(0x40040024, 0); /* #36 GPU - Size */
}

uint32_t mailbox_write(uint32_t fbinfo_addr, uint32_t channel)
{
    while(1)
    {
        if((GET32(MAIL_BASE+0x18)&0x80000000)==0) break;
    }
    PUT32(MAIL_BASE+0x20,fbinfo_addr+channel);
    return(0);
}

uint32_t mailbox_read(uint32_t channel)
{
    uint32_t ra;

    while(1)
    {
        while(1)
        {
            ra=GET32(MAIL_BASE+0x18);
            if((ra&0x40000000)==0) break;
        }
        ra=GET32(MAIL_BASE+0x00);
        if((ra&0xF)==channel) break;
    }
    return(ra>>4);
}

static inline void delay()
{
	for(counter = 0; counter < 0x10000; counter++)
		dummy();
}

void color_screen(uint32_t color)
{
	for(y=0;y<DISPLAY_HEIGHT;y++)
	{
		for(x=0;x<DISPLAY_WIDTH;x++)
		{
			PUT32(gpu_p, color);
			gpu_p += 4;
		}
	}
	PUT32(gpu_p, 0xFFFFFFFF);
}

void kernel_main()
{
	gpio_init();
	mailbox_init();
	mailbox_write(0x40040000, 1);
	mailbox_read(1);

	color_screen(0xFFFF0000);

	led_on();

    while(1)
    {
    	led_off();
    	delay();
    	led_on();
    	delay();
    }
}













