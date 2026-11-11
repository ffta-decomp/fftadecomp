typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { u8 category; u8 opaque[3]; } NeighborCategoryRule;
typedef char RuleStride[(sizeof(NeighborCategoryRule)==4)?1:-1];
extern const NeighborCategoryRule gFourMatchRules[];
extern const NeighborCategoryRule gThreeMatchRules[];
extern const NeighborCategoryRule gTwoMatchRules[];
extern u32 CountNeighborCategory(u8 category,const u8 *values,int length);
/* Actual four-neighbor game rule: preserve table priority and first row match.
 * The output ordinal is written only on success; no default initialization. */
u32 CoreRegion_0003A838(u8 *out_index,const u8 *values)
{
 int i;
 for(i=0;i<5;++i) {
  if((u8)CountNeighborCategory(gFourMatchRules[i].category,values,4)==4) {
   *out_index=i;
   return 1;
  }
 }
 for(i=0;i<6;++i) {
  if((u8)CountNeighborCategory(gThreeMatchRules[i].category,values,4)==3) {
   *out_index=i;
   return 2;
  }
 }
 for(i=0;i<8;++i) {
  if((u8)CountNeighborCategory(gTwoMatchRules[i].category,values,4)==2) {
   *out_index=i;
   return 3;
  }
 }
 return 0;
}
asm(".global gFourMatchRules\n.set gFourMatchRules,0x08391BBC");
asm(".global gThreeMatchRules\n.set gThreeMatchRules,0x08391BD0");
asm(".global gTwoMatchRules\n.set gTwoMatchRules,0x08391BE8");
asm(".global CountNeighborCategory\n.thumb_set CountNeighborCategory,0x0803A7C1");
