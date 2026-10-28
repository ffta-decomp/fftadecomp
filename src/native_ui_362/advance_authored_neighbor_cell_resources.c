typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct ActionCell {s8 x,height,y;u8 untouched;};
struct CellEvent {u16 phase,unknown02;struct ActionCell *cell;u8 unknown08[12];u16 ordinal;u8 unknown16[6];};
struct CellWork {u8 ordinal,unknown01;u16 delay;u8 tile_x,tile_y;s16 x,height,y;u8 unknown12[4];void *resources[2];};
typedef char EventSize[sizeof(struct CellEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct CellWork)==24?1:-1];
extern const s8 gKindsA[],gKindsB[],gSortA[];
extern const u8 gOptions[],gResource[];
extern void *CopyBytes(void *,const void *,u32);
extern void *CreateDefinitionResource(const void *,u32,s32,s32,s32,u32,u32);
extern void SetDefinitionObjectOption(void *,u8);
extern void SetDefinitionResourceDetached(void *,u8);
extern void SetDefinitionObjectSortKey(void *,s16);
extern u32 PollDefinitionResources(void **,u16);
__asm__(
 ".global gKindsA\n.set gKindsA,0x08149d14\n"
 ".global gKindsB\n.set gKindsB,0x08149d18\n"
 ".global gOptions\n.set gOptions,0x08149d1c\n"
 ".global gSortA\n.set gSortA,0x08149d20\n"
 ".global gResource\n.set gResource,0x085000d8\n"
 ".global CopyBytes\n.thumb_set CopyBytes,0x81443fd\n"
 ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x80d5e81\n"
 ".global SetDefinitionObjectOption\n.thumb_set SetDefinitionObjectOption,0x8011119\n"
 ".global SetDefinitionResourceDetached\n.thumb_set SetDefinitionResourceDetached,0x8010885\n"
 ".global SetDefinitionObjectSortKey\n.thumb_set SetDefinitionObjectSortKey,0x8011059\n"
 ".global PollDefinitionResources\n.thumb_set PollDefinitionResources,0x80d5f25\n"
);
s32 AdvanceAuthoredNeighborCellResources(TaskNode *,struct CellEvent *,struct CellWork *) __asm__("RemainingBand43_000F4C6C");
s32 AdvanceAuthoredNeighborCellResources(TaskNode *parent,struct CellEvent *event,struct CellWork *work)
{
 switch(event->phase) {
 case 0: {
  struct ActionCell *cell=event->cell;
  work->ordinal=(u8)event->ordinal;
  work->x=cell->x*32+16;
  work->height=cell->height*16;
  work->y=cell->y*32+16;
  work->tile_x=(u8)cell->x;work->tile_y=(u8)cell->y;
  work->delay=work->ordinal+1;
  break;
 }
 case 1:break;
 case 256: {
  s8 kinds_a[4],kinds_b[4];u8 options[4];s8 sort_a[4],sort_b[4];
  s8 *kinds[2],*sort_keys[2];u8 index;s32 missing;
  CopyBytes(kinds_a,gKindsA,4);
  CopyBytes(kinds_b,gKindsB,4);
  kinds[0]=kinds_a;kinds[1]=kinds_b;
  CopyBytes(options,gOptions,4);
  CopyBytes(sort_a,gSortA,4);
  CopyBytes(sort_b,gKindsA,4);
  sort_keys[0]=sort_a;sort_keys[1]=sort_b;
  if(--work->delay!=0)break;
  index=0;missing=-1;
  do {
   register s8 **kind_slot __asm__("r0")=&kinds[index];
   register u32 ordinal_word __asm__("r1");
   register const s8 *kind_address __asm__("r1");
   register s32 kind __asm__("r0");
   const s8 *table_base;u32 address;
   /* The actual table-cell address precedes the ordinal read. Each R0/R1
    * epoch ends before the same register receives its next real value. */
   __asm__("" : : "r"(kind_slot));
   ordinal_word=work->ordinal;
   __asm__("" : "+r"(ordinal_word));
   table_base=*kind_slot;
   /* Use a fresh ordinary sum before its fixed-register consumer: directly
    * updating hard R1 can commute the original base-first ADD operands. */
   address=(u32)table_base+ordinal_word;
   kind_address=(const s8 *)address;
   __asm__("" : : "r"(kind_address));
   kind=*kind_address;
   /* Native kind is initialized in R0 for the sentinel comparison, then
    * copied to R1 for its LOW16 constructor argument. It is dead before
    * the call writes R0. This input carries that actual value only. */
   __asm__("" : : "r"(kind));
   if(kind!=missing) {
    void *created;void **slot;void **resource_base;s8 *key;
    register s32 constructor_kind __asm__("r1")=kind;
    /* The full signed value reaches its real R1 argument-working epoch
     * before destructive LOW16 conversion. The earlier R1 address is dead;
     * this initialized read/write value is consumed before the call. */
    __asm__("" : "+r"(constructor_kind));
    created=CreateDefinitionResource(gResource,(u16)constructor_kind,work->x,work->height,work->y,0x392,6);
    resource_base=work->resources;slot=resource_base+index;*slot=created;
    SetDefinitionObjectOption(created,options[work->ordinal]);
    key=&sort_keys[index][work->ordinal];
    if(*key==0)SetDefinitionResourceDetached(*slot,1);
    else SetDefinitionObjectSortKey(*slot,*key);
   }
   ++index;
  }while(index<=1);
  ++event->phase;break;
 }
 case 257:
  if((u8)PollDefinitionResources(work->resources,2)!=0)event->phase=2;
  break;
 }
 return 0;
}
