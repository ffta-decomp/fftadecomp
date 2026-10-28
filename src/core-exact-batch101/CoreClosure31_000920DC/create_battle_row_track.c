typedef unsigned char u8;
typedef unsigned int u32;
extern void *AllocateBattleStorage(u32);
asm(".global AllocateBattleStorage\n.thumb_set AllocateBattleStorage,0x08022841");

/* Only the channel byte is initialized; the allocator's other bytes persist. */
u8 *CreateBattleRowTrack(u32 channel)
{
    u8 *track = AllocateBattleStorage(328);
    track[324] = channel;
    return track;
}
