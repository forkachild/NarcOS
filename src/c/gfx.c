#include <gfx.h>

int32_t gfx_init(uint32_t w, uint32_t h, uint32_t d)
{
    mbox[0] = 35 * 4;
    mbox[1] = MBOX_REQUEST;

    mbox[2] = 0x48003; //set phy wh
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = w; //FrameBufferInfo.width
    mbox[6] = h; //FrameBufferInfo.height

    mbox[7] = 0x48004; //set virt wh
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = w; //FrameBufferInfo.virtual_width
    mbox[11] = h; //FrameBufferInfo.virtual_height

    mbox[12] = 0x48009; //set virt offset
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = 0; //FrameBufferInfo.x_offset
    mbox[16] = 0; //FrameBufferInfo.y.offset

    mbox[17] = 0x48005; //set depth
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = d; //FrameBufferInfo.depth

    mbox[21] = 0x48006; //set pixel order
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = 1; //RGB, not BGR preferably

    mbox[25] = 0x40001; //get framebuffer, gets alignment on request
    mbox[26] = 8;
    mbox[27] = 8;
    mbox[28] = 4096; //FrameBufferInfo.pointer
    mbox[29] = 0;    //FrameBufferInfo.size

    mbox[30] = 0x40008; //get pitch
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0; //FrameBufferInfo.pitch

    mbox[34] = MBOX_TAG_LAST;

    if (mbox_call(mbox, MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0)
    {
        mbox[28] &= 0x3FFFFFFF;
        width = mbox[5];
        height = mbox[6];
        pitch = mbox[33];
        pointer = (void *)((unsigned long)mbox[28]);
        return 1;
    }
    return 0;
}

void gfx_clear_screen(uint32_t color)
{
    uint32_t x, y;
	for(y=0;y<width;y++)
	{
		for(x=0;x<height;x++)
		{
			PUT32(pointer, color);
			pointer += 4;
		}
	}
	// PUT32(pointer, 0xFFFFFFFF);
}
