/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneObjectView { u8 unknown00[16]; u8 flags; };
struct SceneStateView { u8 unknown00[29]; u8 mode; u16 scene_id; u8 unknown20[1424]; void *handle; };
extern u32 RetailCall_08011860(void *);
extern void RetailCall_08017d18(void *,u32);
extern void RetailCall_08017e28(struct SceneObjectView *);
extern void RetailCall_08013390(void *);
extern void SetGameFlag(u32,u32);
asm(".global RetailCall_08011860\n.thumb_set RetailCall_08011860,0x08011861\n.global RetailCall_08017d18\n.thumb_set RetailCall_08017d18,0x08017d19\n.global RetailCall_08017e28\n.thumb_set RetailCall_08017e28,0x08017e29\n.global RetailCall_08013390\n.thumb_set RetailCall_08013390,0x08013391\n.global SetGameFlag\n.thumb_set SetGameFlag,0x080c9575");

u32 AdvanceSceneInputAndSpecialFlag(void *context)
{
    void *primary=(u8 *)context+92;
    struct SceneObjectView *secondary=(struct SceneObjectView *)((u8 *)context+112);
    struct SceneStateView **root;
    if (!(u16)RetailCall_08011860(context))
        return 0;
    root=(struct SceneStateView **)0x0200f44c;
    RetailCall_08017d18(primary,(*root)->mode);
    if (secondary != 0) {
        secondary->flags &= 191;
        RetailCall_08017e28(secondary);
    }
    RetailCall_08013390((*root)->handle);
    if ((*root)->scene_id==0x479)
        SetGameFlag(0x581,1);
    return 1;
}
