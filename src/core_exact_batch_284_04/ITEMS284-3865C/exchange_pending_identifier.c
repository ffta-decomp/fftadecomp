typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct PendingIdentifierRam {
    u8 prefix[0x1f3c];
    u16 pending[20];
};
extern struct PendingIdentifierRam gPendingIdentifierRam;
asm(".global gPendingIdentifierRam\n.set gPendingIdentifierRam,0x02000000\n");
u32 ExchangePendingIdentifier(u32 replacement, u16 index) __asm__("CoreRegion_0003865C");
/* No index bound is imposed here. The actual caller exchanges a record ID
 * and writes the old ID back to its reloaded selected record. */
u32 ExchangePendingIdentifier(u32 replacement, u16 index)
{
    u16 old = gPendingIdentifierRam.pending[index];
    gPendingIdentifierRam.pending[index] = replacement;
    return old;
}
