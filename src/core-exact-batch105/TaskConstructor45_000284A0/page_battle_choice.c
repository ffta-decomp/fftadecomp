typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 *ContextCell;
extern u32 Call_08017BE8(u8 *);
extern u32 Call_08017B68(u8 *,int);
extern void Call_08141540(u32);
extern void Call_08025DC8(u8 *,u32);
__asm__(".global ContextCell\n.set ContextCell,0x0200F438\n.global Call_08017BE8\n.thumb_set Call_08017BE8,0x08017BE9\n.global Call_08017B68\n.thumb_set Call_08017B68,0x08017B69\n.global Call_08141540\n.thumb_set Call_08141540,0x08141541\n.global Call_08025DC8\n.thumb_set Call_08025DC8,0x08025DC9");
void TaskConstructor45_000284A0(u8 *request,u32 input_direction)
{
 u8 direction=input_direction;
 u8 *widget=request+56;
 u8 *control=request+88;
 u16 *cell=(u16 *)(ContextCell+0x444+request[8]*4);
 s32 old_base=*(s16 *)(widget+26);
 u32 base=old_base;
 s32 total=(s16)Call_08017BE8(widget)+1;
 u32 row=control[17];
 u32 remaining=*(s8 *)(request+9);
 while(remaining!=0) {
   remaining--;
   if(direction==128) {
     s32 count=*(s8 *)(request+9);
     if((s32)(base+count)<total) base++;
     else {
       remaining=0;
       if(old_base==total-count) row=count-1;
     }
   } else {
     if((s32)base>0) base--;
     else {
       remaining=0;
       if(old_base==0) row=0;
     }
   }
 }
 if((u32)old_base!=base || control[17]!=row) {
   cell[0]=base;
   cell[1]=row;
   Call_08141540(109);
   Call_08025DC8(request,0);
   if(ContextCell[4]==2) {
     register u32 index __asm__("r0")=Call_08017B68(widget,(s8)row);
     register u8 *context __asm__("r2")=ContextCell;
     register u32 *entries __asm__("r1");
     index <<= 16;
     __asm__("" : "+r"(index), "+r"(context));
     entries=*(u32 **)(request+148);
     __asm__("" : "+r"(entries), "+r"(index), "+r"(context));
     index >>= 14;
     index += (u32)entries;
     *(u32 *)(context+24)=*(u32 *)index;
   }
 }
}
