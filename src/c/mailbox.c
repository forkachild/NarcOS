#include <mailbox.h>

int32_t mbox_call(uint32_t *mbox, uint8_t ch)
{
    uint32_t r;
    /* wait until we can write to the mailbox */
    do
    {
        asm volatile("nop");
    } while (MBOX_STATUS(GFX_MBOX) & MBOX_FULL);
    /* write the address of our message to the mailbox with channel identifier */
    MBOX_WRITE(GFX_MBOX) = (((uint32_t)mbox) & ~0xF) | (ch & 0xF);
    /* now wait for the response */
    while (1)
    {
        /* is there a response? */
        do
        {
            asm volatile("nop");
        } while (MBOX_STATUS(GFX_MBOX) & MBOX_EMPTY);
        r = MBOX_READ(GFX_MBOX);
        /* is it a response to our message? */
        if ((uint8_t)(r & 0xF) == ch && (r & ~0xF) == ((uint32_t)mbox))
            /* is it a valid successful response? */
            return mbox[1] == MBOX_RESPONSE;
    }
    return 0;
}