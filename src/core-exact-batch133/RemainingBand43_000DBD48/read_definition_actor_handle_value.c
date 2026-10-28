typedef unsigned short u16;
typedef unsigned int u32;
struct DefinitionActor;
extern struct DefinitionActor *DefinitionRecordIdentity(struct DefinitionActor *);
/* The original caller consumes the returned register through LOW16. */
extern u32 ReadActorHandleRegister(const struct DefinitionActor *);
u16 ReadDefinitionActorHandleValue(struct DefinitionActor *actor)
{
    return (u16)ReadActorHandleRegister(DefinitionRecordIdentity(actor));
}
asm(".global DefinitionRecordIdentity\n.thumb_set DefinitionRecordIdentity,0x080dd351\n"
    ".global ReadActorHandleRegister\n.thumb_set ReadActorHandleRegister,0x08099bf5\n");
