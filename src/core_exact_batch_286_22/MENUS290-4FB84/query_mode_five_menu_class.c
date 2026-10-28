typedef unsigned char u8;
typedef unsigned short u16;
struct MenuClassRoot {u8 prefix[0x424];u16 record_values[0];};
struct MenuClassContext {struct MenuClassRoot *root;};
extern unsigned ReadMenuItemClass(unsigned);
__asm__(".global ReadMenuItemClass\n.thumb_set ReadMenuItemClass,0x080cb99d");
unsigned QueryModeFiveMenuClass(struct MenuClassContext *ctx,unsigned index) {
 u16 value=ctx->root->record_values[index*2];
 unsigned id;
 __asm__("" : "+r"(value));
 id=394;
 if(value<=85) --id;
 return (u8)ReadMenuItemClass(id)+13;
}
