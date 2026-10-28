typedef unsigned char u8;
typedef unsigned int u32;
struct DefinitionActorOptionView { u8 reserved[31]; u8 option_byte31; };
/* This byte is forwarded by the actor task; its broader policy meaning is unknown. */
void SetDefinitionActorByte31(struct DefinitionActorOptionView *actor, u32 value)
{
    actor->option_byte31 = value;
}
