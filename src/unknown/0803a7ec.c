typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { u8 first_category; u8 second_category; u8 opaque[2]; } NeighborPairRule;
typedef char PairRuleStride[(sizeof(NeighborPairRule)==4)?1:-1];
typedef struct { NeighborPairRule rows[28]; } NeighborPairTable;
extern const NeighborPairTable gNeighborPairTable;
extern u32 CountNeighborCategory(u8 category,const u8 *values,int length);
/* B1 is deliberately read only after the first category count succeeds. */
u32 CoreRegion_0003A7EC(u8 *out_index,const u8 *values)
{
 int i;
 for(i=0;i<28;++i) {
  if((u8)CountNeighborCategory(gNeighborPairTable.rows[i].first_category,values,4)==2 &&
     (u8)CountNeighborCategory(gNeighborPairTable.rows[i].second_category,values,4)==2) {
   *out_index=i;
   return 1;
  }
 }
 return 0;
}
asm(".global gNeighborPairTable\n.set gNeighborPairTable,0x08391C08");
asm(".global CountNeighborCategory\n.thumb_set CountNeighborCategory,0x0803A7C1");
