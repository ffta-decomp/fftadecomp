typedef unsigned char u8;
typedef unsigned int u32;
void SetSceneContextByte458(u32 value) __asm__("CoreConsumer_000BD11C");
void SetSceneContextByte458(u32 value)
{
 u8 *context = *(u8 **)0x020101F0;
 context[458] = value;
}
