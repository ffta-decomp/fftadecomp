typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned u32;
struct Context {u8 pad0[0x8000];u16 palette0[256],palette1[256];u8 panel[0x21c];u32 field861c;u8 phase8620,active8621;u8 pad8622[0x895a-0x8622];u16 elapsed895a,duration895c;u8 lower895e,upper895f,zero8960,zero8961,flag8962,pad8963;u16 timer8964;u8 next8966,exit8967;u16 fade8968;u8 pad896a[0x8988-0x896a];u8 flag8988,pad8989[2],flag898b,pad898c,flag898d,pad898e,frame898f,counter8990,counter8991,counter8992,pad8993[0x899c-0x8993];};
extern struct Context *ctx;
asm(".global ctx\n.set ctx,0x0200f3b0");
extern unsigned Interpolate(unsigned,unsigned,int,unsigned);
extern void Draw(const void *,int,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);
asm(".global Interpolate\n.thumb_set Interpolate,0x08137195\n.global Draw\n.thumb_set Draw,0x08001f35");
unsigned Registered39_00137040(void){
 ctx->frame898f++;
 if(ctx->frame898f==5)ctx->counter8990=1;
 if(ctx->frame898f==10)ctx->counter8991=1;
 if(ctx->frame898f==15)ctx->counter8992=1;
 if(ctx->counter8990){unsigned value=Interpolate(ctx->counter8990,30,-100,28);Draw((void *)0x083a8c9e,(short)value,72,0,0,0,0,0,0,0,0);if(ctx->counter8990<=29)ctx->counter8990++;}
 if(ctx->counter8991){unsigned value=Interpolate(ctx->counter8991,30,-100,20);Draw((void *)0x083a8cac,(short)value,88,0,0,0,0,0,0,0,0);if(ctx->counter8991<=29)ctx->counter8991++;}
 if(ctx->counter8992){unsigned value=Interpolate(ctx->counter8992,30,-100,12);Draw((void *)0x083a8cc0,(short)value,112,0,0,0,0,0,0,0,0);if(ctx->counter8992>29)return 1;ctx->counter8992++;}
 return 0;
}
