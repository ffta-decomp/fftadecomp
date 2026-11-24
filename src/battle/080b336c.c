#include "ffta/unsigned_types.h"
typedef signed short s16;
/* The fourth halfword is allocation-unit padding. The angle consumer reads
   only x/y/z; assigning the fields must not manufacture a zero padding word. */
struct PackedTriplet { signed int x:16; signed int y:16; signed int z:16; };
struct BattleNode { u8 unknown00[8]; s16 x, y, z; };
struct TargetNode { u8 unknown00[68]; void *handle; };
struct BattleTransfer {
    u8 unknown00[0x141c];
    void *context;
    struct BattleNode *actor;
    u8 unknown1424[0x14e8-0x1424];
    struct TargetNode *targets[13];
    u16 saved_handle_words[13];
    u16 target_count;
    u8 unknown1538[0x1550-0x1538];
    u8 *owned_buffer;
    void *owner;
    void *handle;
    u16 range;
};
typedef char packed_triplet_size[(sizeof(struct PackedTriplet)==8)?1:-1];
extern int QuantizeTransferAngle(const struct PackedTriplet *, const struct PackedTriplet *);
extern void *GetTransferRegistry(void *);
extern void *GetTransferOwner(void *);
extern int SelectTransferRange(void *,u32,int);
extern void *GetTransferHandle(void *);
extern void SetTransferHandleRange(void *,u16,u16);
extern const void *GetDirectionalTransfer(s16,s16,s16,s16);
extern void *AllocateTransferBuffer(u32);
extern int ExtractTransferFrame(const void *,void *,u16,u16);
extern void QueueActorTransfer(void *,const void *,void *,u16);
extern int CollectTransferTargets(void *,struct TargetNode **);
extern u16 GetTargetHandleWord(void *);

void PrepareBattleActorTransfer(struct BattleTransfer *root)
{
    const void *sources[4];
    struct PackedTriplet origin, target;
    void *registry;
    const void **source_cursor;
    int angle, selected, count, index;
    origin.x=0;
    origin.y=0;
    origin.z=0;
    target=origin;
    target.x=32;
    angle=QuantizeTransferAngle(&origin,&target);
    registry=GetTransferRegistry(*(void **)((u8 *)root->context+128));
    root->owner=GetTransferOwner(registry);
    selected=SelectTransferRange(registry,1,16);
    root->range=selected;
    root->handle=GetTransferHandle(root->owner);
    SetTransferHandleRange(root->handle,(u16)selected,16);
    {
        struct BattleNode *node=root->actor;
        int x, shifted_z, z;
        x=node->x;
        /* The original snapshots x before deriving the shifted z operand. */
        asm("" : : "r" (x));
        shifted_z=(s16)(node->z+48);
        z=node->z;
        sources[2]=GetDirectionalTransfer(x,shifted_z,x,z);
    }
    {
        struct BattleNode *node=root->actor;
        int x, shifted_z, z;
        x=node->x;
        /* The original snapshots x before deriving the shifted z operand. */
        asm("" : : "r" (x));
        shifted_z=(s16)(node->z-48);
        z=node->z;
        sources[0]=GetDirectionalTransfer(x,shifted_z,x,z);
    }
    {
        struct BattleNode *node=root->actor;
        int shifted_x=(s16)(node->x-48);
        int z=node->z;
        int x=node->x;
        sources[3]=GetDirectionalTransfer(shifted_x,z,x,z);
    }
    {
        struct BattleNode *node=root->actor;
        int shifted_x=(s16)(node->x+48);
        int z=node->z;
        int x=node->x;
        sources[1]=GetDirectionalTransfer(shifted_x,z,x,z);
    }
    root->owned_buffer=AllocateTransferBuffer(512);
    {
        register u8 **buffer_cell asm("r5");
        /* Actual zero index and buffer-cell pointer copy, before the source
         * cursor definition. The C compiler owns the stack-object address. */
        asm volatile("mov %0,#0\n\tadd %1,%2,#0"
                     : "=&l"(index), "=&l"(buffer_cell)
                     : "l"(&root->owned_buffer) : "cc");
        source_cursor=sources;
        do {
            ExtractTransferFrame(*source_cursor++,*buffer_cell+128*index,(u16)angle,1);
            ++index;
        } while(index<4);
    }
    QueueActorTransfer((u8 *)root+0x1560,root->owned_buffer,
                       (void *)(0x06010000+((u32)root->range<<5)),128);
    count=CollectTransferTargets(*(void **)((u8 *)root->context+128),root->targets);
    root->target_count=count;
    index=0;
    if(index<count) {
        do {
            root->saved_handle_words[index]=GetTargetHandleWord(root->targets[index]->handle);
            ++index;
        } while(index<root->target_count);
    }
}
asm(".thumb_set QuantizeTransferAngle,0x080a8431\n"
    ".thumb_set GetTransferRegistry,0x08099c31\n"
    ".thumb_set GetTransferOwner,0x08021b1d\n"
    ".thumb_set SelectTransferRange,0x08021c91\n"
    ".thumb_set GetTransferHandle,0x08021b9d\n"
    ".thumb_set SetTransferHandleRange,0x08021c85\n"
    ".thumb_set GetDirectionalTransfer,0x080a83ed\n"
    ".thumb_set AllocateTransferBuffer,0x08022841\n"
    ".thumb_set ExtractTransferFrame,0x08005319\n"
    ".thumb_set QueueActorTransfer,0x08000add\n"
    ".thumb_set CollectTransferTargets,0x08099cdd\n"
    ".thumb_set GetTargetHandleWord,0x08021de1\n");
