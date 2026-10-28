typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;
extern unsigned count(void*);extern void mark(void*,int,unsigned,unsigned,unsigned);
void SceneTaskDependency_00052790(void){u8 *root=*(u8 **)0x0200F428;u8 *list=root+0xD1C;register u8 *cursor __asm__("r0")=root+0xD3C;u8 i;int selected;__asm__("" : "+r"(cursor));i=0;selected=*(s8 *)(cursor+17);for(;(unsigned)i<(u16)count(list);i++){if(i==selected)mark(list,i,11,2,(u8)(list[21]-2));else mark(list,(s8)i,255,2,(u8)(list[21]-2));}}
__asm__(".thumb_set count,0x08017b51\n.thumb_set mark,0x0802acd5");
