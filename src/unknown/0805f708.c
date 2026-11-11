/* Contributed by gg; original source and attribution follow. */
/* CoreRegion30_0005F708
   entry 0x0805F708, 106 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
extern void Call_08017FBC(u8 *,u32);
extern void Call_08017FB0(u8 *,u32);
extern void Call_08025B54(u8 *,int);
extern void Call_08017884(u8 *,u32,u32);
extern void Call_08017AF4(u8 *,int,u32);
__asm__(".global Call_08017FBC\n.thumb_set Call_08017FBC,0x08017FBD\n.global Call_08017FB0\n.thumb_set Call_08017FB0,0x08017FB1\n.global Call_08025B54\n.thumb_set Call_08025B54,0x80601D1\n.global Call_08017884\n.thumb_set Call_08017884,0x08017885\n.global Call_08017AF4\n.thumb_set Call_08017AF4,0x08017AF5");
void f_target(u8 *request,u32 input_direction,u32 input_row,u32 input_scroll)
{
 u8 direction=input_direction;
 u8 row=input_row;
 u8 scroll=input_scroll;
 register u8 *control __asm__("r9")=request+92;
 register u8 *target __asm__("r0")=request+112;
 register u8 *widget __asm__("r8");
 __asm__("" : "+r"(control), "+r"(target));
 {
  register u32 widget_offset __asm__("r1")=60;
  register u8 *widget_address __asm__("r1");
  __asm__("" : "+r"(widget_offset), "+r"(target));
  widget_offset += (u32)request;
  widget_address=(u8 *)widget_offset;
  __asm__("" : "+r"(widget_address), "+r"(target));
  widget=widget_address;
  __asm__("" : "+r"(widget), "+r"(target));
 }
 Call_08017FBC(target,direction);
 if (!scroll) {
  register u32 selected __asm__("r1")=row;
  __asm__("" : "+r"(selected));
  Call_08017FB0(control,selected);
 }
 else {
   Call_08025B54(request,(s8)row);
   Call_08017884(widget,direction,1);
 }
 {
  register u8 *current __asm__("r0")=control;
  __asm__("" : "+r"(current));
  Call_08017AF4(widget,*(s8 *)(current+17),11);
 }
}
