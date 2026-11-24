typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
u32 CoreRegion_00037F0C(void *object,s8 relative) { s16 value=*(u16*)((u8*)object+26)+relative; u32 result; if(value<0) result=0; else { if(value <= *(s16*)((u8*)object+24)-1) result=(u16)value; else result=(u16)(*(u16*)((u8*)object+24)-1); } return result; }
