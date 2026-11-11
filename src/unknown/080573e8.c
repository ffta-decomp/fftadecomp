typedef unsigned char u8;
typedef signed char s8;
extern u8 *gMenuContext;
extern void ApplyMenuRowStyle(void *,int,unsigned,unsigned,unsigned);
extern void CommitMenuPanel(void *);
void HighlightThreeRowMenu(void)
{
 u8 *root=gMenuContext;
 u8 *view=root+0x14bc;
 register u8 *cursor asm("r0")=root+0x14dc;
 u8 index;
 int selected;
 asm("" : "+r" (cursor));
 index=0;
 selected=*(s8 *)(cursor+17);
 do {
  if(index==selected) ApplyMenuRowStyle(view,(s8)(5*index),11,0,view[21]);
  else ApplyMenuRowStyle(view,(s8)(5*index),255,0,view[21]);
  index++;
 } while(index<=2);
 CommitMenuPanel(view);
}
asm(".global gMenuContext\n.set gMenuContext,0x0200f428\n.global ApplyMenuRowStyle\n.thumb_set ApplyMenuRowStyle,0x08058349\n.global CommitMenuPanel\n.thumb_set CommitMenuPanel,0x0802b109");
