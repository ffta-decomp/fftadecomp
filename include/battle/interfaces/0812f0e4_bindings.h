typedef unsigned char u8;typedef unsigned int u32;
struct ActorRule {u8 unknown[253],candidate_mode;};
extern u32 QueryCellPayload(u32,u32);extern u8 ReadCellFlags(u32,u32);
__asm__(".global QueryCellPayload\n.thumb_set QueryCellPayload,0x0801CC7D");
__asm__(".global ReadCellFlags\n.thumb_set ReadCellFlags,0x0801CD09");
