typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u8 *PairTextTable[];
__asm__(".global PairTextTable\n.set PairTextTable,0x08526680");
u8 *CoreConsumer_000CB4E0(u32 input_id)
{
 u16 id=input_id;
 u16 index;
 if(id==0) return PairTextTable[0];
 if(id>85) index=id+540;
 else index=id+625;
 return PairTextTable[(s16)index];
}
