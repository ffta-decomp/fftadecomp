#include "../../task_tree_core.h"
struct SceneTaskDefinition { TaskCallback callback; u16 payload_size; u16 unread06; };
struct SceneDefinitionEvent {
 u32 unknown00;
 void *owner;
 u32 argument;
 u32 flags;
 u32 unknown10;
 u16 definition_id;
 u16 unknown16;
 u32 unknown18;
};
typedef char EventSize[(sizeof(struct SceneDefinitionEvent)==28)?1:-1];
extern const struct SceneTaskDefinition gSceneDefinitions[];
extern TaskGroup *gSceneDefinitionGroup;
extern TaskNode *gManagedSceneTask;
TaskNode *CreateSceneDefinitionTask(u16 definition_id,void *owner,u32 argument) __asm__("RemainingBand43_000D3818");
TaskNode *CreateSceneDefinitionTask(u16 definition_id,void *owner,u32 argument)
{
 struct SceneDefinitionEvent event;
 register const struct SceneTaskDefinition *base __asm__("r1");
 register u32 index __asm__("r0");
 register const struct SceneTaskDefinition *definition __asm__("r0");
 TaskCallback callback;
 u32 payload_size;
 TaskNode *created=0;
 event.definition_id=definition_id;
 event.owner=owner;
 event.argument=argument;
 event.flags=0;
 /* Preserve the original bank/index/address roles, reused from D3508. */
 base=gSceneDefinitions;
 asm("" : "+r"(base));
 index=(u32)definition_id-0x16B;
 asm("" : "+r"(index) : "r"(base));
 definition=(const struct SceneTaskDefinition *)(index*8+(u32)base);
 asm("" : "+r"(definition));
 callback=definition->callback;
 payload_size=definition->payload_size;
 created=CreateTaskNode_08005954(gSceneDefinitionGroup,callback,payload_size,(const u32 *)&event,gManagedSceneTask);
 return created;
}
asm(".global gSceneDefinitions\n.set gSceneDefinitions,0x08395320\n.global gSceneDefinitionGroup\n.set gSceneDefinitionGroup,0x0200F430\n.global gManagedSceneTask\n.set gManagedSceneTask,0x020159C0\n.global CreateTaskNode_08005954\n.thumb_set CreateTaskNode_08005954,0x08005955");
