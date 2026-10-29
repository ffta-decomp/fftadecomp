#include "interfaces.h"
asm(".global gContext\n.set gContext,0x0200f438\n.global GetOptions\n.thumb_set GetOptions,0x80cce61\n.global GetContentContext\n.thumb_set GetContentContext,0x8096d7d\n.global FindRecord\n.thumb_set FindRecord,0x80970e9\n.global CheckOption\n.thumb_set CheckOption,0x80cd561\n.global ReadOptionProperty\n.thumb_set ReadOptionProperty,0x80ccd51\n");
u8 Source52_00025FDC(u8 mode)
{
    u8 range[2];
    u8 *table = 0;
    int special = 0;
    int index;
    u8 *last;
    u8 *entry;
    register u8 *range_work asm("r0");
    register unsigned entry_offset asm("r0");
    switch (mode) {
    case 6:
        table = GetOptions(gContext->unit,1,&range[0],&range[1]);
        special = gContext->unit[53];
        break;
    case 7:
        table = GetOptions(gContext->unit,2,&range[0],&range[1]);
        special = gContext->unit[54];
        break;
    }
    if (FindRecord(GetContentContext(),gContext->unit)) {
        range_work = range;
        asm("" : "+r"(range_work));
        index = *range_work;
        range_work += 1;
        asm("" : "+r"(range_work) : "r"(index));
        last = range_work;
        if (index <= *last) {
            entry_offset = index*8 + 4;
            asm("" : "+r"(entry_offset));
            entry = (u8 *)(entry_offset + (unsigned)table);
            do {
                if ((entry[2] == 1 || entry[2] == 4) && CheckOption(gContext->unit,index) && ReadOptionProperty(*(u16 *)entry,21)) return 1;
                entry += 8;
                index++;
            } while (index <= *last);
        }
    } else {
        if (special == 1) return 1;
        range_work = range;
        asm("" : "+r"(range_work));
        index = *range_work;
        range_work += 1;
        asm("" : "+r"(range_work) : "r"(index));
        last = range_work;
        if (index <= *last) {
            entry = (u8 *)(index*8 + (unsigned)table);
            do {
                if ((entry[6] == 1 || entry[6] == 4) && CheckOption(gContext->unit,index)) return 1;
                entry += 8;
                index++;
            } while (index <= *last);
        }
    }
    return 0;
}
