/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct ActorVisual { void *unit; u8 unknown4[27]; u8 direction31; u8 alternate32; u8 unknown33[15]; u32 flags48; u16 resource52; u16 requested54; u8 unknown56[8]; void *container64; void *active68; void *auxiliary72; } ActorVisual;
#define OFF(T,F) ((u32)&(((T*)0)->F))
typedef char actor_flags_offset[OFF(ActorVisual,flags48)==48?1:-1];
typedef char actor_container_offset[OFF(ActorVisual,container64)==64?1:-1];
extern u32 ReadResourceVariant(u32);
extern u32 UnitStateEDBit5(const void *);
extern u32 GetUnitProperty(const void *,u8);
extern void *InstallActorVisual(void *,void *,u32,u32,u32,s32,u32);
extern void SetActorVisualFlags(ActorVisual *,u16,u16);
extern void SelectContainerVisual(void *,void *);
extern void *AllocateAuxiliaryVisual(void *);
extern void SetVisualResource(void *,u16,u16);
extern void SetVisualMode(void *,u8);
extern void SetVisualEnabled(void *,u8);
__asm__(".global ReadResourceVariant\n.thumb_set ReadResourceVariant,0x08021055");
__asm__(".global UnitStateEDBit5\n.thumb_set UnitStateEDBit5,0x080cdcd5");
__asm__(".global InstallActorVisual\n.thumb_set InstallActorVisual,0x08021619");
__asm__(".global SetActorVisualFlags\n.thumb_set SetActorVisualFlags,0x0809a571");
__asm__(".global SelectContainerVisual\n.thumb_set SelectContainerVisual,0x08021d99");
__asm__(".global AllocateAuxiliaryVisual\n.thumb_set AllocateAuxiliaryVisual,0x08021b9d");
__asm__(".global SetVisualResource\n.thumb_set SetVisualResource,0x08021c85");
__asm__(".global SetVisualMode\n.thumb_set SetVisualMode,0x08021c39");
__asm__(".global SetVisualEnabled\n.thumb_set SetVisualEnabled,0x08021c09");

static inline u8 UsesAlternateDirection(void *unit)
{
    if(GetUnitProperty(unit,40)&2) return 1;
    return 0;
}
void ApplyActorVisualState(ActorVisual *,u16,u8,u32);
void ApplyActorVisualState(ActorVisual *actor,u16 requested,u8 direction,u32 automatic)
{
    u16 resource_variant=(u16)ReadResourceVariant(actor->resource52);
    actor->requested54=requested;
    if(automatic && requested==0) {
        u32 flags=actor->flags48;
        if(flags&8) requested=12;
        if(flags&16) {
            if((u8)UnitStateEDBit5(actor->unit)) requested=12;
            else requested=20;
        }
        flags=actor->flags48;
        if(flags&0x800) {
            if(flags&32) requested=12;
            else requested=128;
        }
        if(actor->flags48&0x400) requested=140;
    }
    actor->direction31=direction;
    if(UsesAlternateDirection(actor->unit)) direction=actor->alternate32;
    actor->active68=InstallActorVisual(actor->container64,actor->active68,0,resource_variant,
                         actor->resource52,requested+(s8)direction,0);
    if(automatic && requested==0) {
        u32 flags=actor->flags48;
        if(flags&0x100) SetActorVisualFlags(actor,0,0x1000);
        else if(flags&0x200) SetActorVisualFlags(actor,0,0x4000);
    }
    SelectContainerVisual(actor->container64,actor->active68);
    if(!actor->auxiliary72) {
        actor->auxiliary72=AllocateAuxiliaryVisual(actor->container64);
        SetVisualResource(actor->auxiliary72,327,0);
        SetVisualMode(actor->auxiliary72,2);
        SetVisualEnabled(actor->auxiliary72,1);
    }
}
