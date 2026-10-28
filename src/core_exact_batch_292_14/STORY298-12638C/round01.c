typedef unsigned char u8;typedef unsigned short u16;
struct Scene {u8 fields0[6];u8 completion,field7;void *parent;};
struct Event {u16 state,field2;struct Scene *scene;void *command;unsigned field12,field16,field20,field24;};
extern void *CreateSceneTask(void *,unsigned,const struct Event *,void *);
asm(".global CreateSceneTask\n.thumb_set CreateSceneTask,0x08121b8d");
void SceneActionDependency_0012638C(struct Scene *scene,void *command){struct Event event;scene->completion=0;event.scene=scene;event.command=command;CreateSceneTask((void *)0x08125a5d,180,&event,scene->parent);}
