typedef unsigned char u8;
typedef unsigned int u32;

extern u8 gRamBase[];
extern u32 EvaluateMissionEventByte(u32 value);
extern void ForwardMissionRecord(const void *descriptor, u8 condition);

asm(".global gRamBase\n.set gRamBase, 0x02000000\n"
    ".global EvaluateMissionEventByte\n.thumb_set EvaluateMissionEventByte, 0x08036351\n"
    ".global ForwardMissionRecord\n.thumb_set ForwardMissionRecord, 0x08009c19\n");
