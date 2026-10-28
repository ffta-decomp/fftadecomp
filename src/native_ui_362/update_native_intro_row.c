typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct NativeIntroRow {
    u32 text;
    u8 state, enabled;
    u16 tick;
    s16 x, y, start_x, start_y, target_x, target_y;
    u16 scale_x, scale_y;
    u8 draw_flag;
} NativeIntroRow;
extern s32 InterpolateNativeIntro(s32,s32,u32,u32) asm("RetailCall_081369b0");
extern s32 EaseNativeIntro(u32,u32,s32,s32) asm("RetailCall_08137194");
void UpdateNativeIntroRow(NativeIntroRow *row) asm("Registered39_00136868");
void UpdateNativeIntroRow(NativeIntroRow *row)
{
    int state=row->state;
    switch(state) {
    case 0:
        row->draw_flag=state;
        break;
    case 1:
        row->draw_flag=state;
        row->enabled=state;
        row->tick++;
        row->scale_y=InterpolateNativeIntro(80,768,10,row->tick);
        row->scale_x=row->scale_y;
        row->x=InterpolateNativeIntro(row->start_x,row->target_x,10,row->tick);
        row->y=InterpolateNativeIntro(row->start_y,row->target_y,10,row->tick);
        if(row->tick>9) {
            row->state=2;
            row->tick=0;
        }
        break;
    case 2:
        row->enabled=1;
        row->draw_flag=1;
        row->tick++;
        row->scale_y=InterpolateNativeIntro(768,256,10,row->tick);
        row->scale_x=row->scale_y;
        if(row->tick>10) {
            row->state=100;
            row->tick=0;
        }
        break;
    case 3:
        row->tick++;
        row->y=(s16)EaseNativeIntro(row->tick,50,
            (s32)((u32)(u16)row->start_y<<24)>>16,
            (s32)((u32)(u16)row->target_y<<24)>>16)>>8;
        if(row->tick>50) {
            row->state=100;
            row->tick=0;
        }
        break;
    case 10:
        break;
    case 100:
        row->enabled=0;
        row->draw_flag=1;
        break;
    }
}
__asm__(".global RetailCall_081369b0\n.thumb_set RetailCall_081369b0,0x081369b1\n"
        ".global RetailCall_08137194\n.thumb_set RetailCall_08137194,0x08137195\n");
