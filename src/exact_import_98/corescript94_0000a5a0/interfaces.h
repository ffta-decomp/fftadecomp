typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NestedEmptyUnitContext {
    u8 unknown_prefix[2];
    u16 script_pc;
};
struct __attribute__((packed)) NestedEmptyUnitCommand {
    u8 opcode;
    u8 skip_low;
    u8 skip_high;
};
struct ContentConsumerContext;
extern struct ContentConsumerContext *GetContentConsumerContext(void);
extern u8 CountEligibleScriptUnits(struct ContentConsumerContext *context);
typedef char EmptyUnitPcOffset[((u32)&((struct NestedEmptyUnitContext *)0)->script_pc == 2) ? 1 : -1];
typedef char EmptyUnitCommandSize[(sizeof(struct NestedEmptyUnitCommand) == 3) ? 1 : -1];
__asm__(".global GetContentConsumerContext\n.thumb_set GetContentConsumerContext,0x08096d7d\n.global CountEligibleScriptUnits\n.thumb_set CountEligibleScriptUnits,0x0809a77d");
