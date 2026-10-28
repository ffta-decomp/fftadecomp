typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;
extern unsigned row_index(void*,int);extern void mark(void*,int,unsigned);
void RemainingCore48_00067E9C(u8 *panel,u8 row){if(panel[8]==5){unsigned index=(u16)row_index(panel+80,(s8)row);u8 *root=*(u8 **)panel;register unsigned offset __asm__("r0")=4*index;register u8 *entries __asm__("r1");u8 *entry;__asm__("" : "+r"(offset));entries=root+0x424;entries+=offset;__asm__("" : "+r"(entries));entry=*(u8 **)entries;if(*(u16 *)(entry+2))return;}mark(panel+80,(s8)row,255);}
__asm__(".thumb_set row_index,0x08017b69\n.thumb_set mark,0x08017b1d");
