#ifndef SCENE_ACTION44_H
#define SCENE_ACTION44_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
typedef void (*TaskCallback)(TaskNode *,u16 *,void *);
struct SceneCommandOwner {u8 unaccessed[6];u8 complete;};
struct SceneAction44Seed {u32 unassigned_phase;struct SceneCommandOwner *owner;u32 unassigned_tail[5];};
typedef char SeedSize[sizeof(struct SceneAction44Seed)==28?1:-1];
extern void ProcessSceneAction44(TaskNode *,u16 *,void *);
extern TaskNode *CreateSceneCommandTask(TaskCallback,u16,const u32 *,TaskNode *);
#endif

void QueueSceneAction44(struct SceneCommandOwner *owner) __asm__("Remaining38_0012BD2C");
void QueueSceneAction44(struct SceneCommandOwner *owner)
{
    struct SceneAction44Seed seed;
    owner->complete=0;
    seed.owner=owner;
    CreateSceneCommandTask(ProcessSceneAction44,68,(const u32 *)&seed,0);
}
__asm__(".global ProcessSceneAction44\n.thumb_set ProcessSceneAction44,0x0812ba09\n"
        ".global CreateSceneCommandTask\n.thumb_set CreateSceneCommandTask,0x08121b8d\n");
