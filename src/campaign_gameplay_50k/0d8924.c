typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct GridRecord {u8 unknown0[10];s8 x,y;};
struct PositionEffectEvent {u32 unknown0;s16 *point;u32 unknown8,unknown12,unknown16;u16 delay,mask;u32 unknown24;};
extern unsigned TriggerImmediateRecordEffect(void *,u16);
extern unsigned RecordHasEffectFlag(void *,u16);
extern struct GridRecord *GetEffectRecordIdentity(void *);
extern unsigned ReadGridHeight(u8,u8);
extern void ConvertEffectGridToWorld(s16,u8,s16,s16 *,s16 *,s16 *);
extern void *CreateDelayedEffectTask(void *,u16,const struct PositionEffectEvent *,void *);
extern unsigned ReadEffectTargetRowCount(void *);
static inline void ReadEffectGridPosition(void *record,s16 *x,s16 *y) {
 struct GridRecord *identity=GetEffectRecordIdentity(record);
 *x=identity->x;
 *y=identity->y;
}
unsigned TriggerRecordPositionEffect(void *record,u16 mask,u16 delay,void *parent) {
 struct PositionEffectEvent event;
 s16 grid_x, grid_y;
 unsigned height;
 unsigned effect_result;
 if(delay==0) {
  effect_result=TriggerImmediateRecordEffect(record,mask);
  goto narrow_result;
 }
 if((u8)RecordHasEffectFlag(record,32)==0) goto fallback;
 {
  ReadEffectGridPosition(record,&grid_x,&grid_y);
  {
   /* Original R1 first captures the full result, then normalizes it
    * before either signed grid reload for the conversion call. */
   register u32 height_working __asm__("r1") =
       ReadGridHeight((u8)grid_x,(u8)grid_y);
   __asm__("" : "+r" (height_working));
   height_working=(u8)height_working;
   /* This is input-only: retain the proven LOW8 range at the use. */
   __asm__ __volatile__("" : : "r" (height_working));
   height=height_working;
  }
  {
   /* The world point starts only after the independent grid OUT phase.
    * The delayed task copies this real contiguous point synchronously. */
   s16 world[3];
   ConvertEffectGridToWorld(grid_x,height,grid_y,&world[0],&world[1],&world[2]);
   event.point=world;
   event.delay=delay;
   event.mask=mask;
   CreateDelayedEffectTask((void *)0x080d82e1,12,&event,parent);
   return 0;
  }
 }
fallback:
 effect_result=ReadEffectTargetRowCount(record);
narrow_result:
 return (u8)effect_result;
}
__asm__(".global TriggerImmediateRecordEffect\n.thumb_set TriggerImmediateRecordEffect,0x080d8859\n.global RecordHasEffectFlag\n.thumb_set RecordHasEffectFlag,0x080dd699\n.global GetEffectRecordIdentity\n.thumb_set GetEffectRecordIdentity,0x080a880d\n.global ReadGridHeight\n.thumb_set ReadGridHeight,0x0801cc19\n.global ConvertEffectGridToWorld\n.thumb_set ConvertEffectGridToWorld,0x0801ca79\n.global CreateDelayedEffectTask\n.thumb_set CreateDelayedEffectTask,0x08005b6d\n.global ReadEffectTargetRowCount\n.thumb_set ReadEffectTargetRowCount,0x080dd495");
