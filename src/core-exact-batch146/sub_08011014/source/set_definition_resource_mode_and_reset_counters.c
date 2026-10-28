typedef unsigned char u8;typedef unsigned short u16;
struct DefinitionResource {u8 state;u8 unknown1[11];u16 mode,counter14,counter16;};
void SetDefinitionResourceModeAndResetCounters(struct DefinitionResource*,u16) __asm__("sub_08011014");
void SetDefinitionResourceModeAndResetCounters(struct DefinitionResource *resource,u16 mode)
{
    resource->mode=mode;
    resource->counter14=0;
    resource->counter16=0;
    if(resource->state==2)resource->state=1;
}
