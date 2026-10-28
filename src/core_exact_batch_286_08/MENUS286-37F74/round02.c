typedef unsigned char u8;
typedef unsigned int u32;
extern void BindFirst(void *,void *,void *,u8) asm("RetailCall_08017c28");
extern void BindSecond(void *,void *,void *,u8) asm("RetailCall_08017db4");
void BindInputRequests(u8 *control,void *first,void *second,u8 firstFlags,u8 secondFlags) asm("CoreRegion_00037F74");
void BindInputRequests(u8 *control,void *first,void *second,u8 firstFlags,u8 secondFlags) {
 void *data=control+44;
 BindFirst(control+76,data,first,(u8)firstFlags);
 BindSecond(control+96,data,second,(u8)secondFlags);
}
asm(".global RetailCall_08017c28\n.thumb_set RetailCall_08017c28,0x08017c29\n.global RetailCall_08017db4\n.thumb_set RetailCall_08017db4,0x08017db5\n");
