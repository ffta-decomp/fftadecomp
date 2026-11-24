typedef unsigned char u8;
typedef unsigned short u16;
struct MissionRecord { u16 identifier:10; u16 other:6; } __attribute__((packed));
struct MissionCollectionState { u8 unknown00[36]; struct MissionRecord *cached[16]; };
struct MissionCollectionRoot { unsigned int unknown00; struct MissionCollectionState *state; };
extern struct MissionCollectionRoot *MissionCollectionRoot;
asm(".global MissionCollectionRoot\n.set MissionCollectionRoot,0x03002810");

int StoreCachedMissionRecord(struct MissionRecord *record) __asm__("CoreRegion_000301B0");
int StoreCachedMissionRecord(struct MissionRecord *record)
{
    /* The ordinal is live through both ID branches and the success return. */
    register int index asm("r6")=0;
    asm("" : "+r"(index));
scan_slot:
    {
        struct MissionCollectionState *state=MissionCollectionRoot->state;
        register unsigned int offset asm("r1")=index*sizeof(struct MissionRecord *);
        /* Preserve the original embedded-array base before adding the ordinal.
           Both empty constraints consume initialized actual addresses. */
        register struct MissionRecord **base asm("r0")=state->cached;
        register struct MissionRecord **slot asm("r3");
        struct MissionRecord *current;
        asm("" : "+r"(base) : "r"(offset));
        slot=(struct MissionRecord **)((unsigned int)base+offset);
        asm("" : "+r"(slot));
        current=*slot;
        if (current==0 || current->identifier==0 || current->identifier==record->identifier) {
            *slot=record;
            return index;
        }
    }
    ++index;
    if(index<=15) goto scan_slot;
    return -1;
}
