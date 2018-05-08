#ifndef _MAILBOX_H_
#define _MAILBOX_H_

#include<reg.h>
#include<mem.h>

#define MBOX_REQUEST        0
#define MBOX_TAG_LAST       0

#define MBOX_CH_POWER       0
#define MBOX_CH_FB          1
#define MBOX_CH_VUART       2
#define MBOX_CH_VCHIQ       3
#define MBOX_CH_LEDS        4
#define MBOX_CH_BTNS        5
#define MBOX_CH_TOUCH       6
#define MBOX_CH_COUNT       7
#define MBOX_CH_PROP        8

#define MBOX_RESPONSE       0x80000000
#define MBOX_FULL           0x80000000
#define MBOX_EMPTY          0x40000000

#define MBOX_READ(r)        REG(r + 0x0)
#define MBOX_POLL(r)        REG(r + 0x10)
#define MBOX_SENDER(r)      REG(r + 0x14)
#define MBOX_STATUS(r)      REG(r + 0x18)
#define MBOX_CONFIG(r)      REG(r + 0x1C)
#define MBOX_WRITE(r)       REG(r + 0x20)

#define GFX_MBOX            (MMIO_BASE + 0x0000B880)

int32_t mbox_call(uint32_t *, uint8_t);

#endif