/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct Unit {
    u8 unknown0[40];
    u16 flags40;
} Unit;
typedef struct Actor { Unit *unit; u8 unknown4[124]; void *list128; } Actor;
typedef struct ActorRow { Actor *actor; u8 unknown4[12]; u32 flags16; u8 unknown20[24]; } ActorRow;
typedef struct ActorRows { u8 unknown0[16]; u16 mode16; u8 unknown18[14]; ActorRow rows32[0]; } ActorRows;
typedef struct FoundNode { Unit *unit; } FoundNode;
#define OFF(T,F) ((u32)&(((T *)0)->F))
typedef char row_size44[sizeof(ActorRow)==44?1:-1];
typedef char rows_offset32[OFF(ActorRows,rows32)==32?1:-1];
typedef char actor_offset128[OFF(Actor,list128)==128?1:-1];
extern u32 ReadRowRule(ActorRow *,u32);
extern FoundNode *FindMarkedActor(void *,Actor *);
extern void SetUnitStateEABit3(Unit *,u32);
extern void RefreshActor(Actor *);
__asm__(".global ReadRowRule\n.thumb_set ReadRowRule,0x080a8859");
__asm__(".global FindMarkedActor\n.thumb_set FindMarkedActor,0x08099495");
__asm__(".global RefreshActor\n.thumb_set RefreshActor,0x080995c1");

void ClearActorSelectionAndApplyRowFlags(ActorRows *);
void ClearActorSelectionAndApplyRowFlags(ActorRows *rows)
{
    s32 ordinal;
    FoundNode *node;
    for(ordinal=0;ordinal<((u8 *)rows)[704];++ordinal) {
        if((u8)ReadRowRule(&rows->rows32[ordinal],3)) {
            while((node=FindMarkedActor(rows->rows32[ordinal].actor->list128,
                                       rows->rows32[ordinal].actor))!=0)
                SetUnitStateEABit3(node->unit,0);
        }
        if(rows->rows32[ordinal].flags16&0x800) {
            while((node=FindMarkedActor(rows->rows32[ordinal].actor->list128,
                                       rows->rows32[ordinal].actor))!=0)
                SetUnitStateEABit3(node->unit,0);
            rows->rows32[ordinal].actor->unit->flags40&=0xfffe;
            rows->rows32[ordinal].actor->unit->flags40|=0x20;
            if(rows->mode16==176 || rows->mode16==106)
                rows->rows32[ordinal].actor->unit->flags40|=0x100;
            RefreshActor(rows->rows32[ordinal].actor);
        }
    }
}
