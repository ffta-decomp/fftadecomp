typedef unsigned char u8;
typedef unsigned short u16;
struct PaletteActor {void *unit;u8 unknown4[26];u8 palette_slot;};
struct ActorPaletteContext {struct PaletteActor *actor;u8 delay,slot,first,condition;u8 unknown8[64];};
struct PaletteSlotEntry {u8 unknown0;u8 slot;u8 unknown2[6];};
extern void *ResolveOverrideUnit(unsigned);
extern void *GetOverrideActorRegistry(void);
extern struct PaletteActor *FindOverrideActor(void *,void *);
extern void *ConfigureActorPaletteOverride(struct ActorPaletteContext *);
extern void MarkActorPaletteHandle(void *);
extern unsigned OverrideUnsignedRemainder(unsigned,unsigned);
extern struct PaletteSlotEntry *GetActorPaletteSlotEntry(unsigned);
extern u16 ReadOverrideUnitPropertyAndSlot(void *,u8 *);
unsigned ProcessActorPaletteOverride(void *ignored,u16 *state,struct ActorPaletteContext *ctx) {
 register unsigned next_state __asm__("r0");
 switch(*state) {
 case 0: {
  void *unit;
  void *registry;
  ctx->first=state[10];
  ctx->condition=state[11];
  ctx->delay=state[12];
  unit=ResolveOverrideUnit(((u8 *)state)[8]);
  registry=GetOverrideActorRegistry();
  ctx->actor=FindOverrideActor(registry,unit);
  break;
 }
 case 256: {
  void *handle=ConfigureActorPaletteOverride(ctx);
  ctx->actor->palette_slot=ctx->slot;
  if(handle) MarkActorPaletteHandle(handle);
  next_state=257;
  __asm__("" : "+r"(next_state));
  *state=next_state;
  break;
 }
 case 257:
  if(ctx->delay) {
   ctx->delay--;
   if(ctx->delay) break;
  }
  if((u8)OverrideUnsignedRemainder(ctx->condition,100)==0) {
   u8 slot=ctx->actor->palette_slot;
   int index=0;
   do {
    struct PaletteSlotEntry *entry=GetActorPaletteSlotEntry((u8)index);
    if(entry->slot && entry->slot==slot) {
     entry->slot=0;
     break;
    }
    index++;
   } while(index<=6);
  }
  if(ctx->condition==100) {
   u8 slot;
   ReadOverrideUnitPropertyAndSlot(ctx->actor->unit,&slot);
   ctx->actor->palette_slot=slot;
  }
  next_state=258;
  __asm__("" : "+r"(next_state));
  *state=next_state;
  break;
 case 258:
  *state=3;
  break;
 }
 return 0;
}
__asm__(".global ResolveOverrideUnit\n.thumb_set ResolveOverrideUnit,0x08125579\n.global GetOverrideActorRegistry\n.thumb_set GetOverrideActorRegistry,0x08096d7d\n.global FindOverrideActor\n.thumb_set FindOverrideActor,0x08099561\n.global ConfigureActorPaletteOverride\n.thumb_set ConfigureActorPaletteOverride,0x081265b9\n.global MarkActorPaletteHandle\n.thumb_set MarkActorPaletteHandle,0x08148601\n.global OverrideUnsignedRemainder\n.thumb_set OverrideUnsignedRemainder,0x08142b29\n.global GetActorPaletteSlotEntry\n.thumb_set GetActorPaletteSlotEntry,0x08121c99\n.global ReadOverrideUnitPropertyAndSlot\n.thumb_set ReadOverrideUnitPropertyAndSlot,0x08022239");
