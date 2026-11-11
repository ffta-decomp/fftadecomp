typedef unsigned char u8;
typedef unsigned short u16;
struct CycleRoot {u8 observed[0x560];u8 group;u8 unknown561;u8 subindex;u8 option;};
struct CycleContext {struct CycleRoot *root;};
unsigned CycleMenuSubindex(struct CycleContext *ctx,u16 keys) {
 struct CycleRoot *root=ctx->root;
 u8 value=root->subindex;
 unsigned maximum=5;
 if(root->group==16) {
  __asm__("" : "+r"(root));
  if(root->option==2) return value;
 }
 if(keys&16) {
  if(value<maximum) value=(u8)(value+1); else value=0;
 } else {
  if(value!=0) value=(u8)(value-1);else value=maximum;
 }
 return value;
}
