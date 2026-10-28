typedef unsigned char u8;
struct CompletionMenuContext {u8 unknown0[8];u8 mode;u8 unknown9[27];u8 widget[0];};
extern unsigned QueryMenuCompletion(void *);
extern void RefreshMenuCategoryStyle(void *);
extern void RefreshCompletedMenu(void *);
__asm__(".global QueryMenuCompletion\n.thumb_set QueryMenuCompletion,0x08017181\n.global RefreshMenuCategoryStyle\n.thumb_set RefreshMenuCategoryStyle,0x08068159\n.global RefreshCompletedMenu\n.thumb_set RefreshCompletedMenu,0x080681c5");
unsigned RefreshMenuAfterCompletion(struct CompletionMenuContext *ctx) {
 u8 status=QueryMenuCompletion(ctx->widget);
 if(status && ctx->mode==4) {
  RefreshMenuCategoryStyle(ctx);
  RefreshCompletedMenu(ctx);
 }
 return status;
}
