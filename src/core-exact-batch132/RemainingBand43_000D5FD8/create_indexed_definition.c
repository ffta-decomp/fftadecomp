typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct DefinitionObject;
struct Task;
struct InitEvent {u16 state;u8 unknown2[2];void *destination;u8 unknown8[12];u16 id;u8 unknown22[6];};
typedef char InitEventSize[sizeof(struct InitEvent)==28?1:-1];
extern u32 QueryPaletteIndex(u16) __asm__("RetailQueryPaletteIndex");
extern void CopyHalfwords(const void*,void*,u32) __asm__("RetailCopyHalfwords");
extern u32 TransferIndexedDefinition(struct Task*,struct InitEvent*,void*) __asm__("RetailTransferIndexedDefinition");
extern struct Task *CreateTask(u32(*)(struct Task*,struct InitEvent*,void*),u16,struct InitEvent*,struct Task*) __asm__("RetailCreateTask");
extern struct DefinitionObject *CreateKindTwoDefinition(const void*,const void*,u16,u8,s16,s16,s16,s16,s16,u16) __asm__("RetailCreateKindTwoDefinition");
extern u8 gPaletteData[];
extern const u8 gIndexedDefinition[];
__asm__(".global RetailQueryPaletteIndex\n.thumb_set RetailQueryPaletteIndex,0x080cb99d\n.global RetailCopyHalfwords\n.thumb_set RetailCopyHalfwords,0x0814186d\n.global RetailTransferIndexedDefinition\n.thumb_set RetailTransferIndexedDefinition,0x080d65d5\n.global RetailCreateTask\n.thumb_set RetailCreateTask,0x08005b6d\n.global RetailCreateKindTwoDefinition\n.thumb_set RetailCreateKindTwoDefinition,0x08011349\n.global gPaletteData\n.set gPaletteData,0x03003a60\n.global gIndexedDefinition\n.set gIndexedDefinition,0x083954b8");
struct DefinitionObject *CreateIndexedDefinition(u16 id,u8 mode,u16 x,u16 y,u16 z,void *destination,u8 palette,struct Task *parent) __asm__("RemainingBand43_000D5FD8");
struct DefinitionObject *CreateIndexedDefinition(u16 id,u8 mode,u16 x,u16 y,u16 z,void *destination,u8 palette,struct Task *parent)
{
    struct InitEvent init;
    u8 source_palette=QueryPaletteIndex(id);
    CopyHalfwords(gPaletteData+source_palette*32,gPaletteData+palette*32,16);
    init.id=id;
    init.destination=destination;
    CreateTask(TransferIndexedDefinition,136,&init,parent);
    return CreateKindTwoDefinition(gIndexedDefinition,0,0,mode,(s16)x,(s16)y,(s16)z,(s32)(((u32)destination+0xf9ff0000u)<<11)>>16,palette,6);
}
