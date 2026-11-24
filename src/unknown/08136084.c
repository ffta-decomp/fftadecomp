typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned u32;
struct Context {u8 pad0[0x8000];u16 palette0[256],palette1[256];u8 panel[0x21c];u32 field861c;u8 phase8620,active8621;u8 pad8622[0x895a-0x8622];u16 elapsed895a,duration895c;u8 lower895e,upper895f,zero8960,zero8961,flag8962,pad8963;u16 timer8964;u8 next8966,exit8967;u16 fade8968;u8 pad896a[0x8988-0x896a];u8 flag8988,pad8989[2],flag898b,pad898c,flag898d,pad898e[0x899c-0x898e];};
extern struct Context *ctx;
struct Shadow {u8 pad[74];volatile unsigned b74:8,b75:8,b76:8,b77:8;};
extern struct Shadow shadow;
asm(".global shadow\n.set shadow,0x03000940");
asm(".global ctx\n.set ctx,0x0200f3b0");
#define B(o) (ctx[o])
#define H(o) (*(u16 *)(ctx+(o)))
#define W(o) (*(u32 *)(ctx+(o)))
#define FN(name,addr) asm(".global " #name "\n.thumb_set " #name "," #addr)
extern void *Allocate(unsigned);FN(Allocate,0x08137aed);
extern void ZeroDispatch(void *,unsigned,void *);FN(ZeroDispatch,0x0814224d);
extern unsigned Mode(void);FN(Mode,0x08137b15);
extern void Setup1(void);FN(Setup1,0x08135b41);
extern void Setup2(void);FN(Setup2,0x08135e89);
extern void *Palette(unsigned,unsigned,unsigned,void *);FN(Palette,0x08147d2d);
extern void Refresh(void *);FN(Refresh,0x081369ed);
extern unsigned Ready(void *);FN(Ready,0x08136539);
extern void Prepare(void);FN(Prepare,0x081457fd);
extern void Setup3(void);FN(Setup3,0x08135985);
extern void Setup4(void);FN(Setup4,0x08135d6d);
extern unsigned Connected(void);FN(Connected,0x0814180d);
extern void Sound(unsigned);FN(Sound,0x081416dd);
extern unsigned Wait1(void);FN(Wait1,0x08136ded);
extern unsigned Wait2(void);FN(Wait2,0x08137041);
extern unsigned Flag(void);FN(Flag,0x0813bce5);
extern void UpdateState(u8 *);FN(UpdateState,0x08136a11);
extern void Cleanup(void *);FN(Cleanup,0x081379c9);
extern void CleanupPalette(void);FN(CleanupPalette,0x08148541);
extern void Fade(unsigned,unsigned,unsigned);FN(Fade,0x08147a7d);
extern void RefreshFade(void);FN(RefreshFade,0x08148601);
extern void EndSound(unsigned);FN(EndSound,0x08141749);
extern void Animate(unsigned,unsigned,unsigned,unsigned,unsigned,unsigned);FN(Animate,0x081379f1);
extern void Finish1(void);FN(Finish1,0x08137b01);
extern void Finish2(void);FN(Finish2,0x08137ad1);
extern void Remove(void *);FN(Remove,0x08006b9d);
extern void Common(void *);FN(Common,0x081371dd);
void Registered39_00136084(unsigned unused,u8 *state)
{
 switch(*state){
 case 0:
  ctx=Allocate(0x899c);ZeroDispatch(ctx,0x899c,*(void **)0x0836d4b8);
  if((u8)Mode()==2 || *(u8 *)0x0300280c==1)*state=3;else *state=1;
  ctx->phase8620=0;break;
 case 1:
  Setup1();Setup2();Refresh(Palette(0,256,10,ctx->palette0));
  Refresh(Palette(256,256,10,ctx->palette1));*state=9;ctx->next8966=2;ctx->timer8964=40;ctx->flag8988=0;break;
 case 2:if((u8)Ready(ctx->panel))*state=3;break;
 case 3:
  Prepare();Setup3();Setup4();{struct Context *phase=ctx;phase->flag898d=0;phase->flag898b=0;}
  if(!(u8)Connected() || (u8)Mode()==2)Sound(42);
  Refresh(Palette(0,256,10,ctx->palette0));Refresh(Palette(256,128,10,ctx->palette1));
  *state=9;ctx->next8966=5;ctx->timer8964=40;break;
 case 5:
  ctx->active8621=1;if(ctx->phase8620==0)ctx->phase8620=1;
  if(!(u8)Connected()){*state=10;ctx->fade8968=20;ctx->exit8967=5;}
  else if((u8)Wait1()){ctx->field861c=0;*state=6;}break;
 case 6:
  if((u8)Wait2()){*state=7;if((u8)Flag())ctx->flag8962=1;}break;
 case 7:
  if(!(u8)Connected()){*state=10;ctx->fade8968=20;ctx->exit8967=5;}
  else UpdateState(state);break;
 case 10:
  ctx->phase8620=3;Cleanup(&ctx->phase8620);CleanupPalette();Fade(0,512,ctx->fade8968);RefreshFade();EndSound(5);
  ctx->timer8964=ctx->fade8968;*state=9;ctx->next8966=255;break;
 case 11:
  ctx->phase8620=3;Cleanup(&ctx->phase8620);CleanupPalette();Fade(0,512,ctx->fade8968);RefreshFade();EndSound(5);
  ctx->duration895c=ctx->fade8968;ctx->elapsed895a=0;*state=8;ctx->next8966=255;
  ctx->lower895e=shadow.b76;ctx->upper895f=shadow.b77;ctx->zero8960=0;ctx->zero8961=0;break;
 case 8:
  Animate(ctx->duration895c,ctx->elapsed895a,ctx->lower895e,ctx->upper895f,ctx->zero8960,ctx->zero8961);
  if(ctx->elapsed895a>=ctx->duration895c)*state=ctx->next8966;else ctx->elapsed895a++;break;
 case 9:
  if(ctx->timer8964==0)*state=ctx->next8966;else ctx->timer8964--;break;
 case 255:
  {register u8 *out asm("r2")=(u8 *)0x0200f390;
   register struct Context *root asm("r0")=ctx;
   register unsigned offset asm("r3")=0x8967;
   register u8 *address asm("r1");
   register u8 value asm("r1");
   asm("" : "+r"(root) : "r"(out),"r"(offset));
   address=(u8 *)root+offset;
   asm("" : "+r"(address) : "r"(out));
   value=*address;
   asm("" : "+r"(value) : "r"(out));
   *out=value;}Finish1();Finish2();Remove((void *)0x0200f3a0);break;
 }
 {register struct Context *root asm("r0")=ctx;
 register unsigned offset asm("r4")=0x8620;
 asm("" : "+r"(root) : "r"(offset));
 Common((u8 *)root+offset);}
}
