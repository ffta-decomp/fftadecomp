typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
struct UnitTaskPosition {
    u8 unknown0[4];
    s16 x;
    s16 y;
    u8 unknown8[8];
    u16 flags;
};
/* Each coordinate uses its original independent flag read and common store. */
void InitializeSecondaryTaskPosition(struct UnitTaskPosition *payload)
{
    if (payload->flags & 64)
        payload->x = 248;
    else
        payload->x = -88;
    if (payload->flags & 128)
        payload->y = 120;
    else
        payload->y = 24;
}
