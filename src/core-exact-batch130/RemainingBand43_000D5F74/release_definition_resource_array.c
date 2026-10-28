typedef unsigned short u16;
typedef unsigned int u32;
extern void ReleaseResource(void *);
void RemainingBand43_000D5F74(void **handles,u16 count)
{
    u16 index;
    for(index=0;index<count;index++) {
        u32 byte_offset=(u32)index*4;
        void **cell;
        /* Original ADD orders the scaled offset before the array base. */
        asm(".syntax unified\n adds %0,%1,%2\n.syntax divided" : "=l"(cell) : "l"(byte_offset), "l"(handles) : "cc");
        if(*cell) {
            ReleaseResource(*cell);
            *cell=0;
        }
    }
}
asm(".global ReleaseResource\n.thumb_set ReleaseResource,0x08011429\n");
