typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { u8 category; u8 opaque[3]; } NeighborCategoryRule;
typedef char RuleStride[(sizeof(NeighborCategoryRule)==4)?1:-1];
extern const NeighborCategoryRule gTwoMatchRules[];
extern u32 CountNeighborCategory(u8 category,const u8 *values,int length);
/* Choose the first table category shared by both world neighbors.
 * Preserve the output ordinal when neither neighbor pair matches. */
u32 CoreRegion_0003A920(u8 *out_index,const u8 *values)
{
 int i;
 for(i=0;i<8;++i) {
  if((u8)CountNeighborCategory(gTwoMatchRules[i].category,values,2)==2) {
   *out_index=i;
   return 3;
  }
 }
 return 0;
}
asm(".global gTwoMatchRules\n.set gTwoMatchRules,0x08391BE8");
asm(".global CountNeighborCategory\n.thumb_set CountNeighborCategory,0x0803A7C1");
