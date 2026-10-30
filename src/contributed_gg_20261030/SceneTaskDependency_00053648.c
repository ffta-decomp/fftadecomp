/* Contributed by gg; original source and attribution follow. */
asm(".global f_0800543C\n.thumb_set f_0800543C,0x0800543D\n.global f_0814186C\n.thumb_set f_0814186C,0x0814186D\n");
/* SceneTaskDependency_00053648
   entry 0x08053648, 44 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned int u32;

extern void f_0800543C(void *a, const void *b);
extern void f_0814186C(const void *a, void *b, u32 n);

void f_target(void)
{
    u8 *buffer = (u8 *)0x02003CB0;

    f_0800543C(buffer, (const void *)0x083AF710);
    f_0814186C(buffer, (void *)0x06015800, 0x180);
}
