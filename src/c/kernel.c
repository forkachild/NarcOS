#include <gfx.h>
#include <mem.h>

#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 1080
#define DISPLAY_DEPTH 32

static inline void gpio_init()
{
    PUT32(GPFSEL1, (uint32_t)(1 << 24));
}

static inline void led_on()
{
    PUT32(GPSET0, (uint32_t)(1 << 18));
}

static inline void led_off()
{
    PUT32(GPCLR0, (uint32_t)(1 << 18));
}

void kernel_main()
{
    gpio_init();
    if (gfx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_DEPTH))
    {
        led_on();
        gfx_clear_screen(COLOR_RED);
    }
    else
    {
        led_off();
    }

}
