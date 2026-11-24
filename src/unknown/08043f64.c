typedef unsigned char u8;
typedef unsigned int u32;
extern u8 gLocationSave[];
union CurrentLocationValue { u32 raw; struct { u32 location:5; u32 preserved:27; } bits; };
/* The observed initial selector is18; its content name remains unknown. */
void SetInitialCurrentLocation(void)
{
 u32 previous=gLocationSave[0x2e54];
 register u32 current asm("r0");
 union CurrentLocationValue extracted;
 current=~31u;
 current &= previous;
 asm("" : "+r" (current));
 current |= 18;
 gLocationSave[0x2e54]=current;
 extracted.raw=current;
 gLocationSave[0x1f69]=extracted.bits.location;
}
asm(".global gLocationSave\n.set gLocationSave,0x02000000");
