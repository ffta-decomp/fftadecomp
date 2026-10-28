typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct NativeIntroDrawRow {
    const u8 *sprite_list;
    u8 state, affine_enabled;
    u16 tick;
    s16 x,y,start_x,start_y,target_x,target_y;
    s16 scale_x,scale_y;
    u8 draw_flag;
} NativeIntroDrawRow;
extern void DrawNativeAffineRow(const u8*,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_080018a0");
extern void DrawNativePlainRow(const u8*,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_08001f34");
void DrawNativeIntroRow(NativeIntroDrawRow *row) asm("Registered39_00136944");
void DrawNativeIntroRow(NativeIntroDrawRow *row)
{
    if(row->draw_flag) {
        if(row->affine_enabled) {
            DrawNativeAffineRow(row->sprite_list,row->x,row->y,0,
                0,0,0,2,0,row->scale_x,row->scale_y,0,1);
        } else {
            DrawNativePlainRow(row->sprite_list,row->x,row->y,0,
                0,0,0,0,0,2,0);
        }
    }
}
__asm__(".global RetailCall_080018a0\n.thumb_set RetailCall_080018a0,0x080018a1\n"
        ".global RetailCall_08001f34\n.thumb_set RetailCall_08001f34,0x08001f35\n");
