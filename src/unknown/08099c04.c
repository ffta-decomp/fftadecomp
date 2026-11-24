typedef unsigned char u8;
struct ExistingResourceHandle;
struct ActorResourceView {
    u8 reserved[68];
    struct ExistingResourceHandle *handle;
};
typedef char HandleOffset[(unsigned int)&(((struct ActorResourceView *)0)->handle)==68?1:-1];
extern void *ReadExistingResourceFlags(struct ExistingResourceHandle *, u8 *, u8 *);
void *ReadActorResourceFlags(const struct ActorResourceView *actor,
                              u8 *horizontal_flag, u8 *vertical_flag)
{
    return ReadExistingResourceFlags(actor->handle, horizontal_flag, vertical_flag);
}
asm(".global ReadExistingResourceFlags\n.thumb_set ReadExistingResourceFlags,0x08021da9\n");
