typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
struct Unit {
    u32 identity;
    u8 reserved_04[2];
    u8 category;
    u8 reserved_07[255];
    u8 reset;
    u8 reserved_107;
};
extern struct Unit gPrimaryUnits[];
extern u32 NextRandom(void);
extern int SignedModulo(int dividend, int divisor);
asm(".global gPrimaryUnits\n.set gPrimaryUnits,0x02000080\n.global NextRandom\n.thumb_set NextRandom,0x08002805\n.global SignedModulo\n.thumb_set SignedModulo,0x08142951");
void CoreConsumer_000C9E00(struct Unit *unit)
{
    int retries=3;
    register struct Unit *primary asm("r9");
    register struct Unit *secondary asm("r10");
    register u8 *root asm("r8");
    int base, range, index;
    u32 candidate;
    struct Unit *cursor;
    primary=gPrimaryUnits;
    asm("" : "+r"(primary));
    secondary=(struct Unit *)((u8 *)primary+0x2f44);
    asm("" : "+r"(secondary));
    root=(u8 *)primary-128;
    asm("" : "+r"(root));
    goto choose;
retry:
    if (--retries == -1)
        goto assigned;
choose:
    if (unit->category>5) {
        base=500;
        range=225;
    } else if (unit->category==4) {
        base=310;
        range=190;
    } else {
        base=0;
        range=310;
    }
    candidate=((const u32 *)0x085680dc)[base+SignedModulo((s16)NextRandom(),range)];
    index=0;
    {
        register struct Unit *first_read asm("r1")=primary;
        asm("" : "+r"(first_read));
        if (first_read->identity!=candidate) {
        cursor=(struct Unit *)(root+128);
        do {
            ++cursor;
            ++index;
            if (index>23)
                break;
        } while (cursor->identity!=candidate);
    }
    }
    if (index!=24)
        goto retry;
    index=0;
    {
        register struct Unit *first_read asm("r1")=secondary;
        asm("" : "+r"(first_read));
        if (first_read->identity!=candidate) {
        cursor=(struct Unit *)(root+0x2fc4);
        do {
            ++cursor;
            ++index;
            if (index>11)
                break;
        } while (cursor->identity!=candidate);
    }
    }
    if (index!=12)
        goto retry;
assigned:
    unit->identity=candidate;
    unit->reset=0;
}
