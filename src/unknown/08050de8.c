typedef unsigned char u8;
struct MenuExitContext {u8 unknown0[9];u8 continuation;u8 unknown10[10];u8 mode;u8 unknown21[7];u8 panel[76];u8 cursor[0];};
extern void SetExitPanelMode(void *,unsigned);
extern void SetExitCursorVisible(void *,unsigned);
extern unsigned RegisterMenuExit(void *,void *);
__asm__(".global SetExitPanelMode\n.thumb_set SetExitPanelMode,0x08017509\n.global SetExitCursorVisible\n.thumb_set SetExitCursorVisible,0x08017d19\n.global RegisterMenuExit\n.thumb_set RegisterMenuExit,0x080098f5");
void BeginMenuPanelExit(struct MenuExitContext *ctx) {
 SetExitPanelMode(ctx->panel,ctx->mode);
 SetExitCursorVisible(ctx->cursor,0);
 ctx->continuation=RegisterMenuExit((void *)0x0804f939,ctx);
}
