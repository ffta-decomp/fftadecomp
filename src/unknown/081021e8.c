typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
extern const u8 resource[];
extern void *make_model(const void*,unsigned,int,int,int,unsigned,unsigned);
extern unsigned f10884(void*,unsigned),f112e8(void*,unsigned),f1115c(void*,unsigned),f1121c(void*,int),f111a8(void*,unsigned),f112a4(void*,unsigned);
void *RemainingBand43_001021E8(u8 mode,const s16 *point,void **slots)
{
 void *primary;
 u8 i;
 primary=make_model(resource,mode,point[0],(s16)(point[1]+56),point[2],640,12);
 f10884(primary,1);f112e8(primary,1);f1115c(primary,0);f1121c(primary,-1);
 for(i=0;i<4;i++) {
  slots[i]=make_model(resource,mode,point[0],(s16)(point[1]+56),point[2],640,12);
  f1115c(slots[i],0);f111a8(slots[i],1);f1121c(slots[i],-1);f112a4(slots[i],1);
 }
 return primary;
}
__asm__(".global resource\n.set resource,0x08502ed8\n.global make_model\n.thumb_set make_model,0x080d5e81\n.global f10884\n.thumb_set f10884,0x08010885\n.global f112e8\n.thumb_set f112e8,0x080112e9\n.global f1115c\n.thumb_set f1115c,0x0801115d\n.global f1121c\n.thumb_set f1121c,0x0801121d\n.global f111a8\n.thumb_set f111a8,0x080111a9\n.global f112a4\n.thumb_set f112a4,0x080112a5");
