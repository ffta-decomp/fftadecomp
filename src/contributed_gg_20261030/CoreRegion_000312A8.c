/* Contributed by gg; original source and attribution follow. */
asm(".global f_081443FC\n.thumb_set f_081443FC,0x081443FD\n");
/* CoreRegion_000312A8
   entry 0x080312A8, 36 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void f_081443FC(void *dst, void *src, u32 len);

void f_target(void)
{
    f_081443FC((void *)(*(u32 *)0x03002810 + 0xBB8), (void *)0x03000940, 0x50);
}
