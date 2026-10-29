typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MissionNoticeEvent {
    u32 unused_00;
    u8 *owner;
    u32 unused_08[3];
    u16 mode;
    u8 unused_16[6];
};
typedef u32 (*MissionNoticeCallback)(u32,void *,void *);
extern u32 AdvanceSelectedMissionNotice(u32,void *,void *);
extern void *CreateMissionNoticeTask(MissionNoticeCallback,u32,const struct MissionNoticeEvent *,u32);
__asm__(".global AdvanceSelectedMissionNotice\n.thumb_set AdvanceSelectedMissionNotice,0x0812803d\n"
        ".global CreateMissionNoticeTask\n.thumb_set CreateMissionNoticeTask,0x08121b8d");
void BeginSelectedMissionNotice(u8 *owner,u32 incoming_mode) __asm__("Scene51_001286DC");
void BeginSelectedMissionNotice(u8 *owner,u32 incoming_mode)
{
    struct MissionNoticeEvent event;
    u32 mode = (u8)incoming_mode;
    owner[6] = 0;
    event.owner = owner;
    event.mode = (u16)mode;
    CreateMissionNoticeTask(AdvanceSelectedMissionNotice,1040,&event,0);
}
