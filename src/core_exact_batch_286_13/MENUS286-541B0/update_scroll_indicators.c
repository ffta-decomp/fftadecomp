typedef unsigned char u8;typedef short s16;
extern unsigned position(void*,unsigned);
void CoreClosure31_000541B0(u8 *flags,u8 *owner){if((u8)position(*(void **)(owner+4),0)){register unsigned old __asm__("r1")=flags[16];__asm__("" : "+r"(old));{register unsigned value __asm__("r0")=4|old;__asm__("" : "+r"(value));flags[16]=value;}}else flags[16]&=251;if((u8)position(*(void **)(owner+4),0)==*(s16 *)(*(u8 **)(owner+4)+24)-4)flags[16]&=247;else {register unsigned old __asm__("r1")=flags[16];__asm__("" : "+r"(old));{register unsigned value __asm__("r0")=8|old;__asm__("" : "+r"(value));flags[16]=value;}}}
__asm__(".thumb_set position,0x080543cd");
