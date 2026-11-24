extern void transition(void*,unsigned,unsigned,unsigned,unsigned,unsigned);
unsigned CoreFrontier_0005D4EC(void){unsigned char **cell=(unsigned char **)0x0200F448;register unsigned char *flags __asm__("r0")=*cell+0x119D;register unsigned zero __asm__("r5")=0;__asm__("" : "+r"(zero), "+r"(flags));*flags=63;transition((void*)0x030008B0,0,0,20,17,1);(*cell)[0x1199]=zero;return 2;}
__asm__(".thumb_set transition,0x08029e49");
