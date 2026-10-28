/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

struct AbilityListLayout {
    u8 origin;
    u8 adjustment;
    u8 width;
    u8 visible;
    u16 count;
    u16 flags;
    u8 unknown08;
    u8 flags09;
};
struct AbilitySelectionContext {
    u8 unknown00[10];
    u8 class_value;
    s8 spacing;
    u8 unknown0c[116];
    struct AbilityListLayout layout;
};
struct AbilitySelectionState {
    u32 unknown00;
    u8 mode;
    u8 unknown05[19];
    u8 *unit;
};
struct AbilityListDescriptor {
    const void *entries;
    u8 first;
    u8 last;
    u8 category;
    u8 base_width;
    u8 item_width;
    u8 count;
    u8 unknown0a[2];
};
typedef char DescriptorSize[(sizeof(struct AbilityListDescriptor)==12)?1:-1];
typedef char LayoutOffset[((unsigned)&((struct AbilitySelectionContext *)0)->layout==128)?1:-1];
extern struct AbilitySelectionState *gAbilitySelection;
extern void (*const gClearSelectionBytes)(void *,u32);
extern u8 UnitStateEAHasBit2(const void *);
extern u32 ReadUnitCounterE6(const void *);
extern void ResolveClassJobCodes(u16,u8 *);
extern u32 ReadMappedClassValue(u16);
extern u32 GetJobProperty(u8,u8,u8);
extern const void *GetJobAbilityList(u8,u8,u8 *,u8 *);
extern const void *SelectUnitAbilityList(const void *,u8,u8 *,u8 *);
extern void BuildMappedAbilityRows(struct AbilitySelectionContext *,struct AbilityListDescriptor *);
extern void BuildInventoryAbilityRows(struct AbilitySelectionContext *,struct AbilityListDescriptor *);
extern void BuildRelatedUnitAbilityRows(struct AbilitySelectionContext *,struct AbilityListDescriptor *);
extern void BuildUnitAbilityRows(struct AbilitySelectionContext *,struct AbilityListDescriptor *);
extern u32 ReadUnitField(const void *,u8);
extern u32 GetContentConsumerContext(void);
extern void *FindLowestEligibleUnitRecord(u32,const void *);
extern u8 AdjustAbilityListWidth(u8,u16);

/* Symbol-only bindings to the original implementations; no instruction body. */
asm(".global gAbilitySelection\n.set gAbilitySelection,0x0200f438\n"
    ".global gClearSelectionBytes\n.set gClearSelectionBytes,0x0836d4b8\n"
    ".global UnitStateEAHasBit2\n.thumb_set UnitStateEAHasBit2,0x080cda7d\n"
    ".global ReadUnitCounterE6\n.thumb_set ReadUnitCounterE6,0x080ce411\n"
    ".global ResolveClassJobCodes\n.thumb_set ResolveClassJobCodes,0x080c9209\n"
    ".global ReadMappedClassValue\n.thumb_set ReadMappedClassValue,0x080c9461\n"
    ".global GetJobProperty\n.thumb_set GetJobProperty,0x080c8571\n"
    ".global GetJobAbilityList\n.thumb_set GetJobAbilityList,0x080cd429\n"
    ".global SelectUnitAbilityList\n.thumb_set SelectUnitAbilityList,0x080cce61\n"
    ".global BuildMappedAbilityRows\n.thumb_set BuildMappedAbilityRows,0x080270cd\n"
    ".global BuildInventoryAbilityRows\n.thumb_set BuildInventoryAbilityRows,0x08026b91\n"
    ".global BuildRelatedUnitAbilityRows\n.thumb_set BuildRelatedUnitAbilityRows,0x08026f9d\n"
    ".global BuildUnitAbilityRows\n.thumb_set BuildUnitAbilityRows,0x08026d45\n"
    ".global ReadUnitField\n.thumb_set ReadUnitField,0x080c7ea5\n"
    ".global GetContentConsumerContext\n.thumb_set GetContentConsumerContext,0x08096d7d\n"
    ".global FindLowestEligibleUnitRecord\n.thumb_set FindLowestEligibleUnitRecord,0x080970e9\n"
    ".global AdjustAbilityListWidth\n.thumb_set AdjustAbilityListWidth,0x08013aad\n");

asm(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");


void PrepareBattleAbilitySelection(struct AbilitySelectionContext *context)
{
    struct AbilityListLayout *layout = &context->layout;
    u32 compact = 0;
    struct AbilityListDescriptor descriptor;
    u8 jobs[3];
    u8 width;
    u16 visible_count;
    u8 selected_job;
    gClearSelectionBytes(&descriptor,12);
    descriptor.base_width = 7;
    if (UnitStateEAHasBit2(gAbilitySelection->unit)) {
        ResolveClassJobCodes((u16)((u8)ReadUnitCounterE6(gAbilitySelection->unit)+202),jobs);
        context->class_value = ReadMappedClassValue((u16)((u8)ReadUnitCounterE6(gAbilitySelection->unit)+202));
        switch (gAbilitySelection->mode) {
        case 6: selected_job = jobs[0]; break;
        case 7: selected_job = jobs[1]; break;
        case 8: selected_job = jobs[2]; break;
        default: goto mapped_category_ready;
        }
        descriptor.category = GetJobProperty(selected_job,selected_job,12);
mapped_category_ready:
        descriptor.entries = GetJobAbilityList(jobs[gAbilitySelection->mode-6],context->class_value,&descriptor.first,&descriptor.last);
        BuildMappedAbilityRows(context,&descriptor);
    } else {
        switch (gAbilitySelection->mode) {
        case 6: descriptor.category = gAbilitySelection->unit[53]; break;
        case 7: descriptor.category = gAbilitySelection->unit[54]; break;
        case 8: descriptor.category = gAbilitySelection->unit[55]; break;
        }
        descriptor.entries = SelectUnitAbilityList(gAbilitySelection->unit,(u8)(gAbilitySelection->mode+251),&descriptor.first,&descriptor.last);
        if (descriptor.category == 1) {
            context->class_value = 0;
            BuildInventoryAbilityRows(context,&descriptor);
        } else {
            u32 consumer;
            context->class_value = ReadUnitField(gAbilitySelection->unit,3);
            consumer = GetContentConsumerContext();
            if (FindLowestEligibleUnitRecord(consumer,gAbilitySelection->unit))
                BuildRelatedUnitAbilityRows(context,&descriptor);
            else
                BuildUnitAbilityRows(context,&descriptor);
        }
    }
    layout->count = descriptor.count;
    layout->width = descriptor.base_width + descriptor.item_width;
    width = AdjustAbilityListWidth(layout->width,layout->flags);
    if (layout->count <= 6) compact = 1;
    layout->origin = 30-width;
    context->spacing = width-(compact+12);
    if (context->spacing < 0) context->spacing = 0;
    visible_count = layout->count;
    if (visible_count <= 5) {
        layout->visible = visible_count;
        layout->adjustment += (6-visible_count)*2;
    }
    if (layout->width <= 10) layout->flags09 &= 0xef;
    layout->origin += compact;
}
