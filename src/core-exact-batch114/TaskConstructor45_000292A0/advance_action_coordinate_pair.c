typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
union ActionPoint { struct { u16 x, y; } coordinate; u32 packed; };
struct ActionTransition { union ActionPoint current, target; };
u32 TaskConstructor45_000292A0(u8 *object)
{
    struct ActionTransition *transition = (struct ActionTransition *)(object + 136);
    int target = (s16)transition->target.coordinate.x;
    u16 previous = transition->current.coordinate.x;
    if (target > (s16)transition->current.coordinate.x)
        transition->current.coordinate.x = previous + 2;
    target = (s16)transition->target.coordinate.y;
    previous = transition->current.coordinate.y;
    if (target > (s16)transition->current.coordinate.y)
        transition->current.coordinate.y = previous + 4;
    if (transition->target.packed == transition->current.packed)
        return 1;
    return 0;
}
