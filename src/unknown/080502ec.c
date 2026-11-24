typedef unsigned char u8;
struct SelectionRoot {u8 observed[0x560];u8 group;u8 observed561;u8 subindex;u8 option;};
struct SelectionContext {struct SelectionRoot *root;};
unsigned QueryNormalizedMenuSelection(struct SelectionContext *ctx) {
 register struct SelectionContext *entry_context __asm__("r2")=ctx;
 struct SelectionRoot *root=entry_context->root;
 unsigned group;
 unsigned base;
 register unsigned computed_base __asm__("r0");
 register struct SelectionRoot *final_root __asm__("r2");
 __asm__("" : "+r"(entry_context), "+r"(root));
 group=root->group;
 computed_base=18*group+1;
 __asm__("" : "+r"(computed_base));
 base=computed_base;
 if(group==16 && root->option==2) root->option=1;
 final_root=entry_context->root;
 __asm__("" : "+r"(final_root));
 return base+6*final_root->option+final_root->subindex;
}
