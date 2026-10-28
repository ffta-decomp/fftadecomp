typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
struct MovementNode { u8 unknown00[8]; s16 x; u16 height; s16 y; };
struct MovementRecord {
    struct MovementNode *node;
    u8 unknown04[12];
    s16 target_x;
    u8 unknown12[2];
    s16 target_y;
    u8 unknown16[4];
    u16 completed_steps;
    s16 speed;
    u8 unknown1e[9];
    u8 direction;
};
/* All direction arms initialize both original signed-byte outputs. */
static inline void DecodeMovementStep(s32 direction, s8 *x, s8 *y)
{
    switch (direction) {
    case 0: *x = 0; *y = 1; break;
    case 1: *x = -1; *y = 0; break;
    case 2: *x = 0; *y = -1; break;
    case 3: *x = 1; *y = 0; break;
    default: *x = 0; *y = 0; break;
    }
}
static inline s32 SelectMovementCoordinate(s32 current, s32 target,
                                          s32 proposal)
{
    s32 selected;
    if (target < current) {
        selected = proposal;
        if (target < selected)
            goto selected_coordinate;
    }
    selected = target;
    if (selected <= current)
        goto selected_coordinate;
    if (selected <= proposal)
        goto selected_coordinate;
    selected = proposal;
selected_coordinate:
    return selected;
}
static inline s32 SelectFirstMovementCoordinate(s32 current, s32 target,
                                          s32 proposal)
{
    register s32 selected __asm__("r1");
    if (target < current) {
        selected = proposal;
        /* The first-axis CMP consumes the initialized selected r1 alias. */
        __asm__("" : "+r" (selected));
        if (target < selected)
            goto selected_coordinate;
    }
    selected = target;
    __asm__("" : "+r" (selected));
    if (selected <= current)
        goto selected_coordinate;
    if (selected <= proposal)
        goto selected_coordinate;
    selected = proposal;
selected_coordinate:
    return selected;
}
/* Reached coordinates advance the stored halfword once and complete this call. */
u32 AdvanceBattleRecordTowardTarget(struct MovementRecord *record)
{
    s8 dx, dy;
    s32 current, target, speed, proposal;
    s32 direction = (s8)record->direction;
    DecodeMovementStep(direction, &dx, &dy);
    current = record->node->x;
    target = record->target_x;
    speed = record->speed;
    proposal = current + dx * speed;
    record->node->x = SelectFirstMovementCoordinate(current, target, proposal);
    current = record->node->y;
    target = record->target_y;
    speed = record->speed;
    proposal = current + dy * speed;
    record->node->y = SelectMovementCoordinate(current, target, proposal);
    if (record->node->x == record->target_x &&
        record->node->y == record->target_y) {
        ++record->completed_steps;
        return 0;
    }
    return 1;
}
