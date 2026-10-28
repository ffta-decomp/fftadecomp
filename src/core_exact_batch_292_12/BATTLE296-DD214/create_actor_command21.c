#ifndef WORKER2_COMMAND_STAGE_H
#define WORKER2_COMMAND_STAGE_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct ActorCommandSeed {
 void *actor;
 u8 command;
 u8 postwait;
 u16 mode;
 u16 remaining;
 u16 unused_options;
} ActorCommandSeed;
typedef struct ActorCommandEvent {
 u16 state;
 u16 unknown2;
 const ActorCommandSeed *seed;
 u32 unknown8;
 u32 unknown12;
 u32 unknown16;
 u16 options;
 u16 unknown22;
 u32 unknown24;
} ActorCommandEvent;
#define OFFSET_OF(T,M) ((u32)&(((T*)0)->M))
typedef char seed_size_12[(sizeof(ActorCommandSeed)==12)?1:-1];
typedef char event_size_28[(sizeof(ActorCommandEvent)==28)?1:-1];
typedef char event_options_20[(OFFSET_OF(ActorCommandEvent,options)==20)?1:-1];
extern void *CreateBattleTask(void *,u32,const ActorCommandEvent *,void *);
#endif

/* Complete DD214..DD248: bind command21 and postwait30 to the existing
 * actor-command callback. Undefined event/seed fields stay uninitialized. */
void *CreateActorCommand21(void *actor,u32 options,u32 remaining,void *parent)
 __asm__("RemainingBand43_000DD214");
void *CreateActorCommand21(void *actor,u32 options,u32 remaining,void *parent)
{
 ActorCommandEvent event;
 ActorCommandSeed seed;
 ActorCommandSeed *seed_fields;
 u32 command=21;
 u32 postwait=30;
 /* Initial native word store addresses the first pointer cell directly;
  * only the following narrow stores share the materialized seed address. */
 *(void **)&seed=actor;
 /* Original DD21C stores the actor before DD21E forms the field address. */
 seed_fields=&seed;
 seed_fields->command=command;
 seed_fields->mode=0;
 seed_fields->postwait=postwait;
 seed_fields->remaining=remaining;
 event.options=options;
 event.seed=seed_fields;
 return CreateBattleTask((void *)0x080dcad5,12,&event,parent);
}
__asm__(".global CreateBattleTask\n.thumb_set CreateBattleTask,0x08005b6d\n");
