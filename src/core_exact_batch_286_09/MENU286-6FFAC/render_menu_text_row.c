typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MenuTextPanel { u8 unknown00[124]; void *text_context; };
struct TextWorkspace { u8 unknown00[16]; u8 *row_base; };
extern struct TextWorkspace gTextWorkspace;
extern void ClearTextCells(void *,u16);
extern u32 ProcessText(void *,u32,const u8 *,u32,u32);
asm(".global gTextWorkspace\n.set gTextWorkspace,0x030008b0\n"
    ".global ClearTextCells\n.thumb_set ClearTextCells,0x08013a89\n"
    ".global ProcessText\n.thumb_set ProcessText,0x08015111\n");
void RenderMenuTextRow(struct MenuTextPanel *panel,const u8 *text,u16 row)
    asm("CoreRegion_0006FFAC");
void RenderMenuTextRow(struct MenuTextPanel *panel,const u8 *text,u16 row)
{
    u8 *destination = gTextWorkspace.row_base + ((u32)row << 5);
    ClearTextCells(destination,24);
    /* The clear is opaque here: reload the live context pointer afterwards. */
    ProcessText(panel->text_context,(u32)destination,text,5,1);
}
