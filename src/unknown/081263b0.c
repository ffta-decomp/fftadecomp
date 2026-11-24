typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
typedef struct {u8 unknown0[6];u8 complete,unknown7;void *parent;}Scene;
typedef struct {u16 phase,unknown2;Scene *scene;u8 unknown8[12];u16 command,unknown22;u32 unknown24;}Event;
extern void *CreateSceneTask(void*,u32,const Event*,void*) asm("0x08121b8d");
void SceneActionDependency_001263B0(Scene *scene,u32 command)
{
 Event event;
 command=(u8)command;
 scene->complete=0;
 event.scene=scene;
 event.command=command;
 CreateSceneTask((void*)0x08125de9,180,&event,scene->parent);
}
