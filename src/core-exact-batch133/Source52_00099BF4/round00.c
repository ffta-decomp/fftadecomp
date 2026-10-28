typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ExistingRecordHandle;
struct ActorHandleView { u8 prefix[68]; struct ExistingRecordHandle *handle; };
typedef char HandleOffset[(u32)&(((struct ActorHandleView *)0)->handle)==68?1:-1];
extern u32 ReadExistingHandleValue(const struct ExistingRecordHandle *);
u16 ReadActorHandleValue16(const struct ActorHandleView *record)
{
    return (u16)ReadExistingHandleValue(record->handle);
}
asm(".global ReadExistingHandleValue\n.thumb_set ReadExistingHandleValue,0x08021c8d\n");
