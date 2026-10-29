typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct NeighborOffset { s8 x,y; u8 opaque[2]; };
struct CandidateCell { u8 x,height,y,opaque; };
typedef char OffsetStride[(sizeof(struct NeighborOffset)==4)?1:-1];
typedef char CandidateStride[(sizeof(struct CandidateCell)==4)?1:-1];
extern const struct NeighborOffset *const gNeighborOffsetBanks[];
extern const u8 gNeighborOffsetCounts[];
extern u8 ReadMapCellPrimaryByte(u8 x,u8 y);
extern u32 IsBattleGridCellPopulated(u32 x,u32 y);
extern u32 AreBattleGridCoordinatesWithin16(int x,int y);
/* Reject unavailable or excessive-height-difference neighbors in table order.
 * bit0 preserves ordinal holes; compact mode may overwrite a rejected slot.
 * Only the first three bytes of each four-byte output record are written. */
u32 RemainingBand43_000D8708(u8 x,u8 y,struct CandidateCell *output,
                            u8 shape,u8 height_limit,u16 flags)
{
 u8 base_height=ReadMapCellPrimaryByte(x,y);
 u8 count=0;
 u8 ordinal=0;
 if(ordinal<gNeighborOffsetCounts[shape]) {
  do {
   u32 valid=1;
   register const struct NeighborOffset *const *bank_base asm("r1")=gNeighborOffsetBanks;
   const struct NeighborOffset *bank;
   const struct NeighborOffset *offset;
   u16 column;
   u16 row;
   register u32 height asm("r2");
   register struct CandidateCell *result asm("r0");
   asm("" : "+r"(bank_base));
   bank=bank_base[shape];
   asm("" : "+r"(bank));
   offset=(const struct NeighborOffset *)((u32)(ordinal*4)+(u32)bank);
   column=offset->x+x;
   row=offset->y+y;
   if((u8)AreBattleGridCoordinatesWithin16((s16)column,(s16)row)==0) {
    valid=0;
    goto rejected;
   }
   {
    u8 column8=column;
    u8 row8=row;
    if((u8)IsBattleGridCellPopulated(column8,row8)==0) valid=0;
    if(valid) {
     s16 signed_difference;
     u16 difference;
     height=ReadMapCellPrimaryByte(column8,row8);
     signed_difference=base_height-height;
     difference=signed_difference;
     if(signed_difference<0) difference=-signed_difference;
     if((s16)difference>height_limit) valid=0;
    }
   }
   if(!valid) {
rejected:
    height=0xffff;
    asm("" : : "r"(height));
    column=height;
    row=height;
   }
   if(flags&1) result=&output[ordinal];
   else result=(struct CandidateCell *)((u32)(count*4)+(u32)output);
   asm("" : "+r"(result));
   result->x=column;
   result->height=height;
   result->y=row;
   if(valid) ++count;
   ++ordinal;
  } while(ordinal<gNeighborOffsetCounts[shape]);
 }
 return count;
}
asm(".global gNeighborOffsetBanks\n.set gNeighborOffsetBanks,0x08395544");
asm(".global gNeighborOffsetCounts\n.set gNeighborOffsetCounts,0x08395548");
asm(".global ReadMapCellPrimaryByte\n.thumb_set ReadMapCellPrimaryByte,0x0801CC19");
asm(".global IsBattleGridCellPopulated\n.thumb_set IsBattleGridCellPopulated,0x0801CC7D");
asm(".global AreBattleGridCoordinatesWithin16\n.thumb_set AreBattleGridCoordinatesWithin16,0x0801CD7D");
