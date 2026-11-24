struct MenuEntryContext {unsigned char observed[152];unsigned char state;};
extern void InitializeEntryText(void *);
extern void InitializeEntryRows(void *);
__asm__(".global InitializeEntryText\n.thumb_set InitializeEntryText,0x080500b1\n.global InitializeEntryRows\n.thumb_set InitializeEntryRows,0x080501cd");
void EnterMenuContentStateTwo(struct MenuEntryContext *ctx) {
 ctx->state=2;
 InitializeEntryText(ctx);
 InitializeEntryRows(ctx);
}
