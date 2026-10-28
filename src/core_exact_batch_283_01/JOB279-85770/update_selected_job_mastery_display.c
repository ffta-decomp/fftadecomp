typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct JobSelectionContext {
    u8 before_render[0x68c];
    u8 render_context[0x95e - 0x68c];
    u8 other_bit0 : 1;
    u8 mastered : 1;
    u8 other_bits2_7 : 6;
    u8 before_unit[0x1d0c - 0x95f];
    const u8 *unit;
};
extern struct JobSelectionContext *gJobSelectionContext;
extern const u8 *const gJobNames[];
extern u32 GetJobProperty(u8,u8,u8);
extern void BiosCpuSet(const void *,void *,u32);
extern u16 RenderEncodedTextCenteredInWidth(void *,const void *,const u8 *,u32,u32);
extern u8 HasMasteredJobAbilities(const u8 *,u8);
asm(".global gJobSelectionContext\n.set gJobSelectionContext,0x03002818\n.global gJobNames\n.set gJobNames,0x08526680\n.global GetJobProperty\n.thumb_set GetJobProperty,0x080c8571\n.global BiosCpuSet\n.thumb_set BiosCpuSet,0x0814186d\n.global RenderEncodedTextCenteredInWidth\n.thumb_set RenderEncodedTextCenteredInWidth,0x0801539d\n.global HasMasteredJobAbilities\n.thumb_set HasMasteredJobAbilities,0x080cd2c5");
void UpdateSelectedJobMasteryDisplay(u32 incoming_job,u32 row_flags)
{
    u32 job = (u8)incoming_job;
    u32 text_index = GetJobProperty(job,job,0);
    {
        const u8 *const *names = gJobNames;
        const u8 *text = names[text_index];
        u16 zero;
        u16 *fill_source = &zero;
        *fill_source = 0;
        {
            void *tiles = (void *)0x0600b4e0;
            BiosCpuSet(fill_source,tiles,0x01000160);
            RenderEncodedTextCenteredInWidth(gJobSelectionContext->render_context,tiles,text,row_flags == 0,12);
        }
    }
    if (HasMasteredJobAbilities(gJobSelectionContext->unit,job))
        gJobSelectionContext->mastered = 1;
    else
        gJobSelectionContext->mastered = 0;
}
