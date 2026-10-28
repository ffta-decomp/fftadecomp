typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattlePhaseSnapshot {
    u8 unknown_0000[656];
    void *owned_allocation;
    u8 unknown_0660[60];
    void *owned_payload;
    u16 saved_first, saved_second;
    u8 saved_byte_first, saved_byte_second, saved_byte_third, saved_byte_fourth;
};
struct RestoredBattleState {
    u16 flags;
    u8 unknown_0002[16];
    volatile u16 first;
    volatile u16 second;
    u8 unknown_0022[52];
    volatile u8 byte_first, byte_second, byte_third, byte_fourth;
};
extern struct RestoredBattleState gRestoredBattleState;
extern void FreeBattleAllocation(void *allocation);
extern void ReleaseOwnedPayload(void *allocation);
asm(".global gRestoredBattleState\n.set gRestoredBattleState,0x03000940\n.global FreeBattleAllocation\n.thumb_set FreeBattleAllocation,0x08022855\n.global ReleaseOwnedPayload\n.thumb_set ReleaseOwnedPayload,0x080920d1");
void ReleaseBattlePhaseSnapshot(struct BattlePhaseSnapshot *snapshot)
{
    register u32 old_flags asm("r1");
    register u32 mask asm("r2");
    register u32 merged_flags asm("r0");
    register struct RestoredBattleState *restored asm("r3");
    if (snapshot->owned_allocation != 0)
        FreeBattleAllocation(snapshot->owned_allocation);
    {
        register u32 source_offset asm("r2") = 720;
        register u8 *source_address asm("r0");
        /* The offset and computed source address have distinct original lifetimes. */
        asm("" : "+r" (source_offset));
        source_address = (u8 *)snapshot + source_offset;
        asm("" : "+r" (source_address));
        ReleaseOwnedPayload(*(void **)source_address);
    }
    restored = &gRestoredBattleState;
    /* The restore base is materialized before the first snapshot-byte address. */
    asm("" : "+r" (restored));
    {
        register u32 source_offset asm("r1") = 728;
        register u8 *source_address asm("r0");
        register u32 copied_byte asm("r0");
        register volatile u8 *destination asm("r2");
        /* The offset and computed source address have distinct original lifetimes. */
        asm("" : "+r" (source_offset));
        source_address = (u8 *)snapshot + source_offset;
        asm("" : "+r" (source_address));
        copied_byte = *source_address;
        /* The loaded byte replaces its consumed source address before destination access. */
        asm("" : "+r" (copied_byte));
        destination = &restored->byte_first;
        /* Keep the destination address distinct from the saved byte and its old read. */
        asm("" : "+r" (destination));
        /* Scalar-pointer volatile stores lack the old-byte read emitted by field stores. */
        (void)*destination;
        *destination = copied_byte;
    }
    {
        register u32 source_offset asm("r2") = 729;
        register u8 *source_address asm("r0");
        register u32 copied_byte asm("r0");
        register volatile u8 *destination asm("r2");
        /* The offset and computed source address have distinct original lifetimes. */
        asm("" : "+r" (source_offset));
        source_address = (u8 *)snapshot + source_offset;
        asm("" : "+r" (source_address));
        copied_byte = *source_address;
        /* The loaded byte replaces its consumed source address before destination access. */
        asm("" : "+r" (copied_byte));
        destination = &restored->byte_second;
        /* Keep the destination address distinct from the saved byte and its old read. */
        asm("" : "+r" (destination));
        /* Scalar-pointer volatile stores lack the old-byte read emitted by field stores. */
        (void)*destination;
        *destination = copied_byte;
    }
    {
        register u32 source_offset asm("r1") = 730;
        register u8 *source_address asm("r0");
        /* The offset and computed source address have distinct original lifetimes. */
        asm("" : "+r" (source_offset));
        source_address = (u8 *)snapshot + source_offset;
        asm("" : "+r" (source_address));
        restored->byte_third = *source_address;
    }
    {
        register u32 source_offset asm("r2") = 731;
        register u8 *source_address asm("r0");
        register u32 copied_byte asm("r0");
        register volatile u8 *destination asm("r2");
        /* The offset and computed source address have distinct original lifetimes. */
        asm("" : "+r" (source_offset));
        source_address = (u8 *)snapshot + source_offset;
        asm("" : "+r" (source_address));
        copied_byte = *source_address;
        /* The loaded byte replaces its consumed source address before destination access. */
        asm("" : "+r" (copied_byte));
        destination = &restored->byte_fourth;
        /* Keep the destination address distinct from the saved byte and its old read. */
        asm("" : "+r" (destination));
        /* Scalar-pointer volatile stores lack the old-byte read emitted by field stores. */
        (void)*destination;
        *destination = copied_byte;
    }
    {
        register u32 source_offset asm("r1") = 724;
        register u8 *source_address asm("r0");
        /* The offset and computed source address have distinct original lifetimes. */
        asm("" : "+r" (source_offset));
        source_address = (u8 *)snapshot + source_offset;
        asm("" : "+r" (source_address));
        restored->first = *(u16 *)source_address;
    }
    {
        register u32 source_offset asm("r2") = 726;
        register u8 *source_address asm("r0");
        /* The offset and computed source address have distinct original lifetimes. */
        asm("" : "+r" (source_offset));
        source_address = (u8 *)snapshot + source_offset;
        asm("" : "+r" (source_address));
        restored->second = *(u16 *)source_address;
    }
    old_flags = restored->flags;
    mask = 1024;
    /* Keep the observed old halfword, mask and merged result independently live. */
    asm("" : "+r" (old_flags), "+r" (mask));
    merged_flags = mask | old_flags;
    asm("" : "+r" (merged_flags));
    restored->flags = merged_flags;
    FreeBattleAllocation(snapshot);
}
