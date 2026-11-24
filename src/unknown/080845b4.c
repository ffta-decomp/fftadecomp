typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef int s32;
struct OwnerSelectionRecord204 {
    u8 unknown00[120];
    u8 selection[32];
    u8 secondary[20];
    u8 scroll[32];
};
typedef char CheckStride[(sizeof(struct OwnerSelectionRecord204)==204)?1:-1];
extern u8 *gOwnerSelectionRoot;
extern void *PreserveMenuScrollObject(void*,u32);
extern u32 QueryClampedSelectionIndex(u8*,u32);
extern void DispatchGuardedRowAttribute(u8*,u32,u32);
extern void SetSelectionRowPosition(u8*,u32);
/* These bindings preserve all caller-established registers. Actual17884
 * consumes only context/key;84A98 consumes ordinal/LOW16delta. */
extern void ApplySceneKeyWithCallerTag(void*,u32,u32);
extern void HandleSelectionByOrdinal(u32,u32,void*);
asm(".global gOwnerSelectionRoot\n.set gOwnerSelectionRoot,0x03002818\n.global PreserveMenuScrollObject\n.thumb_set PreserveMenuScrollObject,0x08017fbd\n.global QueryClampedSelectionIndex\n.thumb_set QueryClampedSelectionIndex,0x08017b69\n.global DispatchGuardedRowAttribute\n.thumb_set DispatchGuardedRowAttribute,0x08017af5\n.global SetSelectionRowPosition\n.thumb_set SetSelectionRowPosition,0x08017fb1\n.global ApplySceneKeyWithCallerTag\n.thumb_set ApplySceneKeyWithCallerTag,0x08017885\n.global HandleSelectionByOrdinal\n.thumb_set HandleSelectionByOrdinal,0x08084a99\n");

void ApplyOwnerSelectionDelta(u32 ordinal,u32 parameter,u32 amount,u32 mode) __asm__("CoreScene34_000845B4");
void ApplyOwnerSelectionDelta(u32 ordinal,u32 parameter,u32 amount,u32 mode)
{
    u32 saved_parameter=(u8)parameter;
    u32 low_amount=(u8)amount;
    u32 narrow_mode=(u8)mode;
    u32 ordinal_bytes;
    u32 common_offset;
    u32 amount_high;
    s32 signed_amount;
    u8 *fresh_root;
    u8 *selection_before_query;
    u8 **root_cell = &gOwnerSelectionRoot;
    /* Retain the defined real symbol address at its original phase only.
     * Input-only keeps its constant identity; no fixed-register lifetime. */
    asm("" : : "r"(root_cell));
    ordinal_bytes=ordinal*204;
    common_offset=ordinal_bytes+0x2c88;
    PreserveMenuScrollObject(((struct OwnerSelectionRecord204*)(gOwnerSelectionRoot+common_offset))->scroll,saved_parameter);
    /* The original constructs this fresh object address before extending the
     * independently retained amount. Keep that actual definition boundary. */
    selection_before_query=((struct OwnerSelectionRecord204*)(gOwnerSelectionRoot+common_offset))->selection;
    asm("" : : "r"(selection_before_query));
    amount_high=low_amount<<24;
    signed_amount=(s32)amount_high>>24;
    QueryClampedSelectionIndex(selection_before_query,signed_amount);
    if(narrow_mode==0) {
        DispatchGuardedRowAttribute(((struct OwnerSelectionRecord204*)(gOwnerSelectionRoot+common_offset))->selection,signed_amount,11);
        SetSelectionRowPosition(((struct OwnerSelectionRecord204*)(gOwnerSelectionRoot+common_offset))->secondary,amount_high>>24);
        {
            register u32 selected asm("r0") = QueryClampedSelectionIndex(gOwnerSelectionRoot+ordinal_bytes+0x2d00,signed_amount);
            /* Original keeps this full helper return in R0 through the fresh
             * root load and byte write; only STRB narrows the value. */
            asm("" : "+r"(selected));
            gOwnerSelectionRoot[ordinal_bytes+0x2cbe]=selected;
        }
    } else {
        HandleSelectionByOrdinal(ordinal,signed_amount,((struct OwnerSelectionRecord204*)(gOwnerSelectionRoot+common_offset))->selection);
        {
            register u32 selected asm("r0") = QueryClampedSelectionIndex(gOwnerSelectionRoot+ordinal_bytes+0x2d00,signed_amount);
            /* Original keeps this full helper return in R0 through the fresh
             * root load and byte write; only STRB narrows the value. */
            asm("" : "+r"(selected));
            gOwnerSelectionRoot[ordinal_bytes+0x2cbe]=selected;
        }
        ApplySceneKeyWithCallerTag(((struct OwnerSelectionRecord204*)(gOwnerSelectionRoot+common_offset))->selection,saved_parameter,1);
        fresh_root=gOwnerSelectionRoot;
        DispatchGuardedRowAttribute(((struct OwnerSelectionRecord204*)(fresh_root+common_offset))->selection,*(s8*)(fresh_root+ordinal_bytes+0x2d31),11);
    }
}
