typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u32 *ReadPathSample(u32 *,u32,u32,u32);
extern u32 BiosPathArcTan2(s32,s32);
__asm__(".global ReadPathSample\n.thumb_set ReadPathSample,0x0804bd4d\n"
        ".global BiosPathArcTan2\n.thumb_set BiosPathArcTan2,0x08141861");
u32 GetPathSegmentOrientation(u32 incoming_reverse,u32 incoming_table,u32 incoming_start) __asm__("CoreRegion_00044D90");
u32 GetPathSegmentOrientation(u32 incoming_reverse,u32 incoming_table,u32 incoming_start)
{
    u32 current_point;
    u32 next_point;
    u32 reverse = (u8)incoming_reverse;
    u32 table = (u8)incoming_table;
    u32 start = (u8)incoming_start;
    /* Original full-word packed accumulator survives both retained calls in R4. */
    register u32 accumulated __asm__("r4") = 0;
    u32 index = 0;
    __asm__("" : "+r"(accumulated));
    while (index <= 4) {
        u32 position = start+index;
        u32 current_snapshot;
        s32 delta_x;
        s32 delta_y;
        s32 accumulated_y;
        u32 projected_x;
        u32 projected_y;
        ReadPathSample(&current_point,reverse,table,(u8)position);
        current_snapshot = current_point;
        if (current_snapshot == 0)
            break;
        ReadPathSample(&next_point,reverse,table,(u8)(position+1));
        if (next_point == 0)
            goto orientation_ready;
        delta_x = (s8)next_point-(s8)current_snapshot;
        projected_x = (u16)(accumulated+delta_x);
        accumulated &= 0xffff0000u;
        accumulated |= projected_x;
        accumulated_y = (s32)accumulated >> 16;
        delta_y = (s8)(next_point>>16)-(s8)(current_snapshot>>16);
        projected_y = (u32)(accumulated_y+delta_y)<<16;
        accumulated &= 0xffffu;
        accumulated |= projected_y;
        index = (u8)(index+1);
    }
orientation_ready:
    return (((u32)(u16)BiosPathArcTan2((s16)accumulated,(s32)accumulated>>16)>>13)-2)&7;
}
