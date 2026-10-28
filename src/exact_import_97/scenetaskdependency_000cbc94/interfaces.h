typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct FixedItemChoiceState {
    u8 unknown00[0x1f30];
    u16 first_item, second_item, third_item, fourth_item, fifth_item;
};
typedef char FirstChoiceOffset[(u32)&((struct FixedItemChoiceState*)0)->first_item==0x1f30?1:-1];
typedef char LastChoiceOffset[(u32)&((struct FixedItemChoiceState*)0)->fifth_item==0x1f38?1:-1];
extern struct FixedItemChoiceState gFixedItemChoices;
__asm__(".global gFixedItemChoices\n.set gFixedItemChoices,0x02000000");
