typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef union FacingPosition {
    struct {
    u32 x : 8;
    u32 height : 8;
    u32 y : 8;
    u32 unused : 8;
    } fields;
    struct { unsigned short low; unsigned short high; } halves;
} FacingPosition;
typedef char facing_word_size[sizeof(FacingPosition)==4 ? 1:-1];
extern u8 ReadPositionHeight(u8 x, u8 y);

/* These packed local words retain the original X/height/Y subfields.
   Height is looked up and stored even though only X/Y select the result. */
u32 DetermineSceneFacing_08124ACC(u8 source_x, u8 source_y, u8 target_x, u8 target_y)
{
    FacingPosition source;
    FacingPosition target;
    source.fields.x = source_x;
    source.fields.y = source_y;
    target.fields.x = target_x;
    target.fields.y = target_y;
    source.fields.height = ReadPositionHeight(source.fields.x, source.halves.high);
    target.fields.height = ReadPositionHeight(target.fields.x, target.halves.high);
    if (source.fields.x == target.fields.x) {
        if (source.fields.y < target.fields.y)
            goto facing_zero;
        goto facing_two;
    }
    if (source.fields.y == target.fields.y) {
        if (source.fields.x < target.fields.x)
            goto facing_three;
        goto facing_one;
    }
    if (source.fields.x > target.fields.x) {
        if (source.fields.y > target.fields.y) {
            if ((s32)source.fields.y - (s32)target.fields.y >
                (s32)source.fields.x - (s32)target.fields.x)
                goto facing_two;
        } else {
            if ((s32)target.fields.y - (s32)source.fields.y >
                (s32)source.fields.x - (s32)target.fields.x)
                goto facing_zero;
        }
    facing_one:
        return 1;
    }
    if (source.fields.y > target.fields.y) {
        if ((s32)source.fields.y - (s32)target.fields.y <=
            (s32)target.fields.x - (s32)source.fields.x)
            goto facing_three;
    facing_two:
        return 2;
    }
    if ((s32)target.fields.y - (s32)source.fields.y >
        (s32)target.fields.x - (s32)source.fields.x)
        goto facing_zero;
 facing_three:
    return 3;
 facing_zero:
    return 0;
}
asm(".global ReadPositionHeight\n.thumb_set ReadPositionHeight,0x0801cc19");
