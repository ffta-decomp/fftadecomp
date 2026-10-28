typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void *AllocateScratch(u32 bytes) __asm__("0x08022840");
extern void RetailCall_080b5278(void *workspace, u32 argument0, u16 argument1,
    u16 argument2, u8 argument3, u8 argument4, u8 argument5) __asm__("0x080b5278");

void *CoreFrontier_000B7E1C(u32 argument0, u32 argument1, u32 argument2,
    u32 argument3, u32 argument4, u32 argument5) {
    u16 argument1_u16 = (u16)argument1;
    u16 argument2_u16 = (u16)argument2;
    u8 argument3_u8 = (u8)argument3;
    u8 argument4_u8 = (u8)argument4;
    u8 argument5_u8 = (u8)argument5;
    void *workspace = AllocateScratch(0x1160);

    RetailCall_080b5278(workspace, argument0, argument1_u16, argument2_u16,
        argument3_u8, argument4_u8, argument5_u8);
    return workspace;
}
