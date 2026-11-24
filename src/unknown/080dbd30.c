typedef unsigned char u8;
struct DefinitionActor;
extern struct DefinitionActor *DefinitionRecordIdentity(struct DefinitionActor *);
extern void *ReadActorResourceFlags(struct DefinitionActor *, u8 *, u8 *);
/* The retained helper leaves both outputs untouched when its flag is clear. */
void *ReadDefinitionActorResource(struct DefinitionActor *actor,
                                  u8 *horizontal_flag, u8 *vertical_flag)
{
    return ReadActorResourceFlags(DefinitionRecordIdentity(actor),
                                  horizontal_flag, vertical_flag);
}
asm(".global DefinitionRecordIdentity\n.thumb_set DefinitionRecordIdentity,0x080dd351\n"
    ".global ReadActorResourceFlags\n.thumb_set ReadActorResourceFlags,0x08099c05\n");
