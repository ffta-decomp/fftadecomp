typedef unsigned char u8;typedef unsigned int u32;
struct CycleBits {u8 reserved:2;u8 cycle:2;u8 remaining:4;} __attribute__((packed));
struct ProgressionData {u8 prefix[0x2e58];struct CycleBits flags;u8 gap[0x161];u8 outer_counter,inner_counter;};
extern struct ProgressionData gProgressionData;
extern void NRefresh(void),NWrap(void);
asm(".global gProgressionData\n.set gProgressionData,0x02000000\n.global NRefresh\n.thumb_set NRefresh,0x08035e05\n.global NWrap\n.thumb_set NWrap,0x080cc199");
#define OFFSET(t,m) ((u32)&((t*)0)->m)
typedef char outer_offset[(OFFSET(struct ProgressionData,outer_counter)==0x2fba)?1:-1];
typedef char inner_offset[(OFFSET(struct ProgressionData,inner_counter)==0x2fbb)?1:-1];
