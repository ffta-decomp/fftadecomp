typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Region content roles remain tentative; offsets are established by native stores. */
struct ProgressionContext {
 u8 reserved_0000[120];
 void *pool;
 u8 reserved_007c[28];
 void *workspace;
 u8 reserved_009c[2424];
 void *region_1;
 void *region_4;
 void *region_7;
 u8 reserved_0a20[192];
 void *region_2;
 void *region_5;
 void *region_8;
 u8 reserved_0aec[192];
 void *region_3;
 void *region_6;
 void *region_9;
 u8 reserved_0bb8[80];
 void *auxiliary;
};
extern u8 gPoolStorage[];
extern void *gProgressionPool;
extern struct ProgressionContext *gProgressionContext;
extern struct { u32 reserved; void *buffer; } gAuxiliaryBuffer;
extern void *InitializePool(void *storage,u32 bytes);
extern void *AllocatePoolBytes(void *pool,u32 bytes);
extern u32 QueryAllocationSize(u32 unused,const u8 *allocation);
extern void CpuSet(const void *source,void *destination,u32 control);
/* Compact variant: actual four allocations and three independent fills.
 * The accepted31060 MOV-zero lifetime transfer emits exactly2 instructionbytes.
 * It defines zero truthfully; all storage/call/reload behavior remains C. */
void CoreRegion_000311B0(void)
{
 u16 zero_context, zero_workspace, zero_buffer;
 register u16 *fill_source asm("r0");
 register u32 fill_zero asm("r4");
 gProgressionPool=InitializePool(gPoolStorage,0xB880);
 gProgressionContext=AllocatePoolBytes(gProgressionPool,0x7570);
 fill_source=&zero_context;
 /* Native MOVzero follows source-address materialization; zero spans the three fills. */
 asm("mov %0, #0" : "=l"(fill_zero) : "r"(fill_source) : "cc");
 *fill_source=fill_zero;
 CpuSet(fill_source,gProgressionContext,0x01003AB8);
 gProgressionContext->pool=gProgressionPool;
 gProgressionContext->workspace=AllocatePoolBytes(gProgressionPool,0x1840);
 zero_workspace=fill_zero;
 CpuSet(&zero_workspace,gProgressionContext->workspace,0x01000C20);
 gAuxiliaryBuffer.buffer=AllocatePoolBytes(gProgressionPool,0x740);
 zero_buffer=fill_zero;
 CpuSet(&zero_buffer,gAuxiliaryBuffer.buffer,0x010003A0);
 gProgressionContext->auxiliary=AllocatePoolBytes(gProgressionPool,0xF68);
 QueryAllocationSize((u32)gProgressionContext->pool,(const u8 *)gProgressionContext->workspace);

}
asm(".global gPoolStorage\n.set gPoolStorage,0x0200f390\n.global gProgressionPool\n.set gProgressionPool,0x0200f38c\n.global gProgressionContext\n.set gProgressionContext,0x03002810\n.global gAuxiliaryBuffer\n.set gAuxiliaryBuffer,0x03000e30\n.global InitializePool\n.thumb_set InitializePool,0x080070c9\n.global AllocatePoolBytes\n.thumb_set AllocatePoolBytes,0x08007139\n.global QueryAllocationSize\n.thumb_set QueryAllocationSize,0x0800717d\n.global CpuSet\n.thumb_set CpuSet,0x0814186d");
