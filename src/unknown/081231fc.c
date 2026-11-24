typedef unsigned char u8;
typedef unsigned short u16;
struct SceneActor {void *unit;u8 unknown4[26];u8 unit_slot;};
extern struct SceneActor *ResolveCommandActor(unsigned);
extern u16 ReadUnitPropertyAndSlot(const void *,u8 *);
unsigned RefreshSelectedActorUnitSlot(void *ignored,const u8 *command) {
 u8 slot;
 struct SceneActor *actor=ResolveCommandActor(command[1]);
 ReadUnitPropertyAndSlot(actor->unit,&slot);
 actor->unit_slot=slot;
 return 272;
}
__asm__(".global ResolveCommandActor\n.thumb_set ResolveCommandActor,0x081255c9\n.global ReadUnitPropertyAndSlot\n.thumb_set ReadUnitPropertyAndSlot,0x08022239");
