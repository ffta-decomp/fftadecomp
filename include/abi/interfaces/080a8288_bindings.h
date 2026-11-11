#ifndef FFTA_BATTLE_SCENE_DIRECTION_16_H
#define FFTA_BATTLE_SCENE_DIRECTION_16_H

typedef unsigned char direction_u8;
typedef signed char direction_s8;
typedef unsigned short direction_u16;
typedef signed short direction_s16;
typedef unsigned int direction_u32;
typedef signed int direction_s32;

typedef struct DirectionChoiceObject {
    void *node;
    direction_u8 direction;
    direction_u8 initial_direction;
    direction_u8 animation_offset;
    direction_u8 countdown;
    direction_u8 animation_step;
    direction_u8 reserved_9;
    direction_u16 x;
    direction_u16 height;
    direction_u16 y;
    direction_u8 draw_enabled;
    direction_u8 reserved_17[3];
} DirectionChoiceObject;
typedef char DirectionChoiceObjectMustBe20Bytes[
    sizeof(DirectionChoiceObject) == 20 ? 1 : -1];

#define DirectionNodeHalf(node, offset) \
    (*(volatile direction_u16 *)((direction_u8 *)(node) + (offset)))
#define DirectionNodeWord(node, offset) \
    (*(volatile direction_u32 *)((direction_u8 *)(node) + (offset)))

typedef void (*DirectionClearFunction)(void *destination, direction_u32 length);
typedef void (*DirectionObjectEffect)(direction_u32 object, direction_u32 enabled);

extern void InitializeDirectionChoiceObject(volatile DirectionChoiceObject *choice,
    void *node, direction_s32 x, direction_s32 height, direction_s32 y,
    direction_s32 direction);
extern direction_s32 AdvanceDirectionChoiceObject(
    volatile DirectionChoiceObject *choice, direction_u32 input);
extern void InitializeDirectionChoiceObjectBody(volatile DirectionChoiceObject *choice,
    void *node, direction_s32 x, direction_s32 height, direction_s32 y,
    direction_s32 direction);
extern direction_s32 AdvanceDirectionChoiceObjectBody(
    volatile DirectionChoiceObject *choice, direction_u32 input);
extern void DirectionProjectCoordinates(direction_s32 x, direction_s32 height,
    direction_s32 y, direction_s16 *screen_x, direction_s16 *screen_y);
extern void IP03_DrawIndicator(const void *list, direction_s32 x,
    direction_s32 y, direction_u32 attributes, direction_u32 attribute_12,
    direction_u32 attribute_13, direction_u32 mirror_x, direction_u32 mirror_y,
    direction_u32 tile_offset, direction_u32 priority, direction_u32 palette);
extern void RetailCall_0809836c(void *node, direction_u32 code,
    direction_s32 direction, direction_u32 value);
extern void DirectionPlaySound(direction_u32 sound);

#endif
