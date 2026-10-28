typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneDialogEvent {
    u32 unknown_00;
    void *scene;
    u8 unknown_08[12];
    u16 mode;
    u16 message;
    u8 unknown_24[4];
};
typedef char EventSizeCheck[(sizeof(struct SceneDialogEvent)==28)?1:-1];
extern u32 CreateSceneGroup(void (*callback)(void),u32 bytes,void *event,void *parent);
extern void SceneDialogCallback(void);
void StartSceneOpcode12Dialog(u8 *scene,u32 raw_mode,u32 raw_message)
    asm("SceneActionDependency_001263DC");
void StartSceneOpcode12Dialog(u8 *scene,u32 raw_mode,u32 raw_message)
{
    struct SceneDialogEvent event;
    u32 mode=(u8)raw_mode;
    u32 message=(u8)raw_message;
    scene[6]=0;
    event.scene=scene;
    event.mode=mode;
    event.message=message;
    CreateSceneGroup(SceneDialogCallback,180,&event,*(void **)(scene+8));
}
asm(".global CreateSceneGroup\n.thumb_set CreateSceneGroup,0x08121b8d\n.global SceneDialogCallback\n.thumb_set SceneDialogCallback,0x08125fa9\n");
