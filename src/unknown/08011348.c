typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
struct DefinitionObject;
extern struct DefinitionObject *CreateDefinitionObject(u8 kind,const void *data,const void *relative,u16 id,u8 mode,s16 x,s16 y,s16 z,s16 group,s16 palette,u16 flags) __asm__("RetailCreateDefinitionObject");
__asm__(".global RetailCreateDefinitionObject\n.thumb_set RetailCreateDefinitionObject,0x0801093d");
struct DefinitionObject *CreateKindTwoDefinition(const void *data,const void *relative,u16 id,u8 mode,s16 x,s16 y,s16 z,s16 group,s16 palette,u16 flags) __asm__("CoreDependency29_00011348");
struct DefinitionObject *CreateKindTwoDefinition(const void *data,const void *relative,u16 id,u8 mode,s16 x,s16 y,s16 z,s16 group,s16 palette,u16 flags)
{
    return CreateDefinitionObject(2,data,relative,id,mode,x,y,z,group,palette,flags);
}
