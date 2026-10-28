typedef unsigned char u8; typedef unsigned short u16; typedef unsigned u32;
#define W(p,n) (*(u8 **)((p)+(n)))
#define H(p,n) (*(u16 *)((p)+(n)))
extern void clear_text(void*); extern void text_setup(void*,unsigned,void*,void*); extern void refresh_default(void);extern void refresh_a(void);extern void refresh_b(void);extern u8 *payload(void*);extern void row_visible(void*,unsigned);
void RemainingCore48_000665B0(u8 *panel){
 u8 *row=panel+112;u8 *child=panel+132;u8 *root;
 clear_text(W(panel,0)+2992);root=W(panel,0);text_setup(root+2992,H(root,12),(void*)0x030008B0,(void*)0x03000990);
 switch(panel[8]) {case 1:case 2:refresh_default();break;case 3:break;case 5:case 6:refresh_a();break;case 4:if(payload(W(panel,16))[9]&1)refresh_b();else refresh_a();break;}
 W(panel,0)[10]=row[16];
 if(H(row,10)+H(row,14)<=64)row_visible(row,0);else row_visible(row,1);
 if(child){if(H(child,8)<=224 && H(child,10)<=64)child[16]&=251;{register unsigned flags __asm__("r1")=child[16];__asm__("" : "+r"(flags));{register unsigned result __asm__("r0")=64|flags;__asm__("" : "+r"(result));child[16]=result;}}}
 if(panel[8]==4){u8 *p=payload(W(panel,16));register unsigned flags __asm__("r2")=p[9];__asm__("" : "+r"(flags));{register unsigned result __asm__("r1")=8|flags;__asm__("" : "+r"(result));p[9]=result;}}
}
__asm__(".thumb_set clear_text,0x08013391\n.thumb_set text_setup,0x08019a8d\n.thumb_set refresh_default,0x08013435\n.thumb_set refresh_a,0x080615b1\n.thumb_set refresh_b,0x080615c9\n.thumb_set payload,0x08005bfd\n.thumb_set row_visible,0x08017d19");
