/* Contributed by gg; original source and attribution follow. */
asm(".global f_08022854\n.thumb_set f_08022854,0x08022855\n");
/* CoreFrontier_000BCA54
   entry 0x080BCA54, 32 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned int u32;

extern void f_08022854(void *payload);

void f_target(u8 *object)
{
    u8 *target = object;
    u32 handle = *(u32 *)(object + 0x3C);
    if (handle != 0) {
        f_08022854((void *)handle);
        *(u32 *)(object + 0x3C) = 0;
    }
    f_08022854(target);
}
