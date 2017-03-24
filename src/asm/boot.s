.section ".text.boot"

.globl _start
_start:

    mov sp, #0x8000
    bl kernel_main
hang: b hang
		
.globl PUT32
PUT32:
	str r1, [r0]
	bx lr

.globl GET32
GET32:
	ldr r0, [r0]
	bx lr

.globl PUT16
PUT16:
	strh r1, [r0]
	bx lr

.globl PUT8
PUT8:
	strb r1, [r0]
	bx lr

.globl GETPC
GETPC:
	mov r0, lr
	bx lr

.globl dummy
dummy:
	bx lr
