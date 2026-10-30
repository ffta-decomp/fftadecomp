/* Contributed by gg; original source and attribution follow. */
asm(".global f_080C7D18\n.thumb_set f_080C7D18,0x080C7D19\n");
/* VisitContextTreePayloadsInOrderAt10
   entry 0x08099894, 28 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void f_080C7D18(void *node, void *cb, void *args);
typedef void (*Callback)(void);
typedef struct { void *ctx; Callback cb; } VisitArgs;

void f_target(void *tree, Callback cb, void *ctx)
{
    VisitArgs args;
    args.ctx = ctx;
    args.cb = cb;
    f_080C7D18(*(void **)((u8 *)tree + 0x10), (void *)0x0809AC01, &args);
}
