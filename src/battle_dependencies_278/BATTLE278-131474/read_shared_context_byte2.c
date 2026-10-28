typedef unsigned char u8;
typedef unsigned int u32;
struct SharedRecordByte2 { u8 unknown00[2]; u8 field2; };
struct SharedContextRoot { u8 unknown00[48]; struct SharedRecordByte2 *record; };
extern struct SharedContextRoot gSharedContextRoot;
__asm__(".global gSharedContextRoot\n.set gSharedContextRoot,0x0200f3f0");

/* Physical pointer/byte roles are established; broader meaning is tentative. */
u32 ReadSharedContextByte2(void)
{
    return gSharedContextRoot.record->field2;
}
