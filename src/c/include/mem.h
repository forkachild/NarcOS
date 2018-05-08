#ifndef _MEM_H_
#define _MEM_H_

#include <stddef.h>
#include <stdint.h>

#define REG(r)			*((volatile uint32_t *) r)

extern void PUT32(uint32_t, uint32_t);

#endif