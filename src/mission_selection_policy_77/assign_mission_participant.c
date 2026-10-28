/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Participant { u8 id,flags; u16 mission_id; };
struct Mission { u16 id:10; u16 reserved:6; u8 unknown[2]; u8 participants[0]; } __attribute__((packed));
struct MissionContext { u8 prefix[0x11A3]; u8 slot; u8 gap[6]; u8 candidate_count; u8 gap11AB[157]; struct Participant *records[130]; struct Mission *mission; };
extern struct MissionContext *gMissionContext;
extern void ClearMissionParticipantSlot(u16);
__asm__(".global gMissionContext\n.set gMissionContext,0x0200F448");
__asm__(".global ClearMissionParticipantSlot\n.thumb_set ClearMissionParticipantSlot,0x0805DDC9");

/* Assign or toggle the selected mission participant, preserving slot ownership. */
void AssignMissionParticipant(u16 candidate_index)
{
    int count=gMissionContext->candidate_count;
    struct Participant *old=gMissionContext->records[count+gMissionContext->slot];
    struct Participant *selected=gMissionContext->records[candidate_index];
    if (old) {
        if (old->mission_id==selected->mission_id) {
            if (selected->flags&1) {
                int index;
                for (index=0; index<gMissionContext->candidate_count; ++index) {
                    struct Participant *alternative;
                    if (index==candidate_index) continue;
                    alternative=gMissionContext->records[index];
                    if (alternative->mission_id==old->mission_id) {
                        alternative->flags|=1;
                        selected->flags&=254;
                        gMissionContext->records[gMissionContext->candidate_count+gMissionContext->slot]=gMissionContext->records[gMissionContext->candidate_count+(gMissionContext->slot^1)];
                        gMissionContext->records[gMissionContext->candidate_count+(gMissionContext->slot^1)]=old;
                        break;
                    }
                }
            }
            ClearMissionParticipantSlot(gMissionContext->slot);
            return;
        }
        old->mission_id=0;
        old->flags&=254;
    }
    gMissionContext->mission->participants[gMissionContext->slot]=selected->id;
    selected->mission_id=gMissionContext->mission->id;
    gMissionContext->records[gMissionContext->candidate_count+gMissionContext->slot]=selected;
}
