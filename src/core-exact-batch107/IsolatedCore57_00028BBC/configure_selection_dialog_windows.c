typedef unsigned int u32;
extern void Call_0802A2C0(u32,u32,u32,u32);
extern void Call_0802A370(u32,u32,u32,u32);
__asm__(".global Call_0802A2C0\n.thumb_set Call_0802A2C0,0x0802A2C1\n.global Call_0802A370\n.thumb_set Call_0802A370,0x0802A371");
void IsolatedCore57_00028BBC(void)
{
 Call_0802A2C0(2,2,26,6);
 Call_0802A370(1,9,14,11);
}
