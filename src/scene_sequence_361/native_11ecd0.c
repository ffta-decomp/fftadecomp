typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Event28 { u32 opaque0[5]; u16 mode; u16 opaque22[3]; };
extern u32 CreateSceneTask(void *,u32,struct Event28 *,void *) __asm__("0x08005b6c");
u32 RemainingBand43_0011ECD0(u8 mode,void *parent)
{
    struct Event28 event;
    event.mode=mode;
    return CreateSceneTask((void *)0x0811eb29,8,&event,parent);
}
