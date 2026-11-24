typedef unsigned short u16;
typedef unsigned int u32;

u32 GetInventoryItemConsumedByAction(u16 action_id)
    __asm__("ActionDependency_00133C00");
u32 GetInventoryItemConsumedByAction(u16 action_id)
{
    switch (action_id) {
    case 0xfb: return 0x16a;
    case 0xfc: return 0x16b;
    case 0xfd: return 0x16c;
    case 0xfe: return 0x16d;
    case 0xff: return 0x16e;
    case 0x100: return 0x177;
    case 0x101: return 0x171;
    case 0x102: return 0x172;
    case 0x103: return 0x173;
    case 0x104: return 0x174;
    case 0x105: return 0x16f;
    case 0x106: return 0x170;
    case 0x107: return 0x175;
    case 0x108: return 0x176;
    default: return 0;
    }
}
