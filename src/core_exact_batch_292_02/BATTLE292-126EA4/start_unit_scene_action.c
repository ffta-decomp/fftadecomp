typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ActionEvent {
    u32 event;
    u8 *owner;
    u32 untouched[3];
    u16 selector, argument, mode, untouched26;
};
extern void *CreateSceneAction(void *,u16,struct ActionEvent *,void *);
extern u8 UnitActionCallback[];
asm(".global CreateSceneAction\n.thumb_set CreateSceneAction,0x08121b8d\n.global UnitActionCallback\n.set UnitActionCallback,0x08126d35\n");
void StartUnitSceneAction(u8 *owner,u8 selector,u32 argument,u8 mode) asm("SceneActionDependency_00126EA4");
void StartUnitSceneAction(u8 *owner,u8 selector,u32 argument,u8 mode)
{
    struct ActionEvent event;
    owner[6]=0;
    event.owner=owner;
    event.selector=selector;
    event.argument=argument;
    event.mode=mode;
    CreateSceneAction(UnitActionCallback,12,&event,0);
}
