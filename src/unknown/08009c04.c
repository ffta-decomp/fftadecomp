typedef unsigned char u8;
typedef unsigned short u16;
struct MissionDispatchContextPrefix {
    u8 unknown00[160];
    u16 first;
    u16 second;
};
/* 09C18 supplies a definition/record pair before mission operation dispatch.
 * Only this prefix and the two halfword writes are known, not full object size.
 * Ordinary callback-free RAM; no fabricated flags, guard or return value. */
void CoreFrontier_00009C04(u16 first, u16 second)
{
    struct MissionDispatchContextPrefix *context =
        (struct MissionDispatchContextPrefix *)0x020020d0;
    context->first = first;
    context->second = second;
}
