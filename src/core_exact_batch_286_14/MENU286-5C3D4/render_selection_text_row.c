typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SelectionTextData { u8 unknown00[21]; u8 width_units; };
struct SelectionTextWorkspace { u8 unknown00[16]; u8 *tile_base; };
extern struct SelectionTextWorkspace gSelectionTextWorkspace;
extern u8 *gSceneStateRoot;
extern u32 QuerySelectionTileOffset(struct SelectionTextData *,u32);
extern void ClearTextCells(void *,u16);
extern u32 ProcessText(void *,u32,const u8 *,u32,u32);
asm(".global gSelectionTextWorkspace\n.set gSelectionTextWorkspace,0x03000990\n"
    ".global gSceneStateRoot\n.set gSceneStateRoot,0x0200f428\n"
    ".global QuerySelectionTileOffset\n.thumb_set QuerySelectionTileOffset,0x08017b9d\n"
    ".global ClearTextCells\n.thumb_set ClearTextCells,0x08013a89\n"
    ".global ProcessText\n.thumb_set ProcessText,0x08015111\n");
void RenderSelectionText(const u8 *text,struct SelectionTextData *data,
                            s8 row,u8 glyph)
    asm("SceneTaskDependency_0005C3D4");
void RenderSelectionText(const u8 *text,struct SelectionTextData *data,
                            s8 row,u8 glyph)
{
    u32 tile_offset=QuerySelectionTileOffset(data,row);
    u8 *destination=gSelectionTextWorkspace.tile_base+((u32)(u16)tile_offset<<5);
    ClearTextCells(destination,data->width_units*2);
    /* This is an embedded context, not a word loaded from offset0x1184. */
    ProcessText(gSceneStateRoot+0x1184,(u32)destination,text,glyph,1);
}
