#include "interfaces.h"
asm(".global ReadSaveByte\n.thumb_set ReadSaveByte,0x080C95A9\n"
    ".global GetBattleContext\n.thumb_set GetBattleContext,0x08096D7D\n"
    ".global GetContextUnit\n.thumb_set GetContextUnit,0x0809A9C1\n"
    ".global gPrimaryUnits\n.set gPrimaryUnits,0x02000080\n"
    ".global gSecondaryUnits\n.set gSecondaryUnits,0x02002FC4\n");


struct UnitRecord *CoreContinuation_0002DE58(const struct UnitKey *input)
{
    register const struct UnitKey *key asm("r5")=input;
    register struct UnitRecord *unit asm("r2");
    int ordinal;
    asm("" : : "r"(key));
    if (ReadSaveByte(13)==1) {
        for (ordinal=0;ordinal<2;++ordinal) {
            register u32 group_offset asm("r0");
            register u8 *group_address asm("r1");
            unit=GetContextUnit(GetBattleContext(),ordinal);
            asm("" : : "r"(unit));
            group_offset=260;
            asm("" : "+r"(group_offset));
            group_address=(u8 *)unit+group_offset;
            if (*group_address!=255) {
                register u32 shifted_key asm("r0")=(u32)key->packed<<28;
                register u32 current_group asm("r1");
                asm("" : "+r"(shifted_key), "+r"(group_address));
                current_group=*group_address;
                asm("" : "+r"(current_group) : "r"(shifted_key));
                if (current_group==(shifted_key>>28)) return unit;
            }
        }
    }
    unit=gPrimaryUnits;
    for (ordinal=0;ordinal<24;++ordinal,++unit) {
        register u32 group_offset asm("r0")=260;
        register u8 *group_address asm("r3");
        asm("" : "+r"(group_offset));
        group_address=(u8 *)unit+group_offset;
        if (*group_address!=255) {
            register u32 status asm("r1")=unit->status;
            asm("" : "+r"(status));
            if (status&129) {
                register u32 shifted_key asm("r0")=(u32)key->packed<<28;
                register u32 current_group asm("r1");
                asm("" : "+r"(shifted_key), "+r"(group_address));
                current_group=*group_address;
                asm("" : "+r"(current_group) : "r"(shifted_key));
                if (current_group==(shifted_key>>28)) return unit;
            }
        }
    }
    unit=gSecondaryUnits;
    for (ordinal=0;ordinal<12;++ordinal,++unit) {
        register u32 group_offset asm("r0")=260;
        register u8 *group_address asm("r3");
        asm("" : "+r"(group_offset));
        group_address=(u8 *)unit+group_offset;
        if (*group_address!=255) {
            register u32 status asm("r1")=unit->status;
            asm("" : "+r"(status));
            if (status&1) {
                register u32 shifted_key asm("r0")=(u32)key->packed<<28;
                register u32 current_group asm("r1");
                asm("" : "+r"(shifted_key), "+r"(group_address));
                current_group=*group_address;
                asm("" : "+r"(current_group) : "r"(shifted_key));
                if (current_group==(shifted_key>>28)) return unit;
            }
        }
    }
    return 0;
}
