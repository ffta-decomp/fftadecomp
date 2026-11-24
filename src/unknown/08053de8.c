typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
extern void CopyTiles(const void *,void *,unsigned);
extern void DrawRecordIndicators(void *,unsigned,unsigned);
void RefreshPendingRecordIndicators(u8 *panel,const u16 *records)
{
 u16 zero;
 u16 ordinal;
 u16 index;
 register unsigned clear_value asm("r1")=0;
 asm("" : "+r" (clear_value));
 panel[23]=5;
 zero=clear_value;
 CopyTiles(&zero,*(void **)(panel+12),0x01000000|2*((unsigned)panel[21]*panel[22]));
 ordinal=0;
 index=*(u16 *)(panel+26);
 while(ordinal<(*(s16 *)(panel+24)<4 ? *(s16 *)(panel+24):4)){
  DrawRecordIndicators(panel,(u8)ordinal,records[index]);
  ordinal++;
  index++;
 }
}
asm(".global CopyTiles\n.thumb_set CopyTiles,0x0814186d\n.global DrawRecordIndicators\n.thumb_set DrawRecordIndicators,0x08053f09");
