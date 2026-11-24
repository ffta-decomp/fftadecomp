typedef unsigned char u8;
typedef unsigned short u16;
extern u8 gSavedImage[];
__asm__(".global gSavedImage\n.set gSavedImage,0x02000000");
void SetMissionItemOccupancy(unsigned occupied,unsigned index_word)
{
    register unsigned value __asm__("r2")=occupied;
    u8 *address;
    u8 *saved_image_base;
    unsigned shifted_index;
    u8 previous;
    /* Retain both real incoming words at the actual initialized R2 entry-copy
     * boundary, then consume only LOW16 of the index as retail does. */
    __asm__("" : "+r"(value), "+r"(index_word));
    shifted_index=index_word<<16;
    saved_image_base=gSavedImage;
    /* The real displaced word is still live when the actual saved-image base
     * is materialized; its lower shift is consumed by the following address. */
    __asm__("" : "+r"(saved_image_base), "+r"(shifted_index));
    /* Native evolves the byte displacement into a working address word before
     * its actual byte-pointer consumption. Keep this destructive association. */
    shifted_index>>=14;
    shifted_index+=(unsigned)saved_image_base;
    address=(u8 *)shifted_index;
    __asm__("" : "+r"(address));
    address+=0x2b08;
    previous=*address;
    __asm__ volatile("" : : "r"(previous));
    *address=value;
}
