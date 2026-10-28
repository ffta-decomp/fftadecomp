typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned u32;
struct Context {u8 pad0[0x8000];u16 palette0[256],palette1[256];u8 panel[0x21c];u32 field861c;u8 phase8620,active8621;u8 pad8622[0x895a-0x8622];u16 elapsed895a,duration895c;u8 lower895e,upper895f,zero8960,zero8961,flag8962,pad8963;u16 timer8964;u8 next8966,exit8967;u16 fade8968;u8 pad896a[0x8988-0x896a];u8 flag8988,pad8989[2],flag898b,repeat898c,flag898d,skip898e,frame898f,counter8990,counter8991,counter8992,pad8993[0x899c-0x8993];};
extern struct Context *ctx;
struct Keys {u16 held,pressed;};extern struct Keys keys;
asm(".global keys\n.set keys,0x03000000");
asm(".global ctx\n.set ctx,0x0200f3b0");
extern void Draw(const void *,int,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
extern void Fade(unsigned,unsigned,unsigned);
extern void Service(unsigned);
asm(".global Draw\n.thumb_set Draw,0x08001f35\n.global Fade\n.thumb_set Fade,0x08147ad1\n.global Service\n.thumb_set Service,0x08141541");
unsigned Registered39_00136DEC(void){
 u16 x=65;unsigned show=1;
 switch(ctx->flag898d){
 case 0:ctx->flag898b++;x=300-4*ctx->flag898b;if((short)x<=64){x=65;{struct Context *phase=ctx;phase->repeat898c=0;phase->flag898b=0;}ctx->flag898d++;}break;
 case 1:ctx->flag898b++;if(ctx->flag898b>34)show=0;if(ctx->flag898b>49){ctx->repeat898c++;ctx->flag898b=0;}if(ctx->repeat898c>7){{struct Context *phase=ctx;phase->repeat898c=0;phase->flag898b=0;}ctx->flag898d++;}break;
 case 2:ctx->flag898b++;x=65-4*ctx->flag898b;if((short)x < -100){{struct Context *phase=ctx;phase->repeat898c=0;phase->flag898b=0;}show=0;ctx->flag898d++;}break;
 case 3:show=0;ctx->flag898b++;if(ctx->flag898b>64){{struct Context *phase=ctx;phase->repeat898c=0;phase->flag898b=0;phase->flag898d=0;}}break;
 case 4:show=1;ctx->flag898b++;if(ctx->flag898b>5){Fade(336,16,15);ctx->flag898b=0;ctx->flag898d=5;}break;
 case 5:ctx->flag898b++;x=65-8*ctx->flag898b;if((short)x < -100){{struct Context *phase=ctx;phase->repeat898c=0;phase->flag898b=0;}return 1;}break;
 }
 if(show){
 register const void *asset asm("r0")=(void *)0x083a8c84;
 register int draw_x asm("r1")=(short)x;
 register unsigned draw_y asm("r2")=105;
 register unsigned zero asm("r3")=0;
 asm("" : "+r"(asset),"+r"(draw_x),"+r"(draw_y),"+r"(zero));
 Draw(asset,draw_x,draw_y,zero,zero,zero,zero,zero,zero,zero,zero);
}
 if((keys.pressed &8) && !ctx->skip898e){Service(153);ctx->skip898e=1;ctx->flag898d=4;ctx->flag898b=0;}
 return 0;
}
