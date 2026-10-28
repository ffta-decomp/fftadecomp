typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u16 gSaveSectorMap[16];
extern u32 (*gSaveSectorAction)(u16);
extern void WaitSaveRetry(u32);
extern void DiscoverSaveSlotsAndSectorMap(void);
void ProcessSaveSlotSectors(u32 slot_raw)
{
    u32 shifted_slot=slot_raw<<24;
    s32 index=0;
    u32 slot=shifted_slot>>24;
    for(;index<=15;index++) {
        u32 owner=gSaveSectorMap[index]>>8;
        if(owner==slot || owner==255) {
            u32 (**action)(u16)=&gSaveSectorAction;
            u16 sector=index;
            if((u16)(*action)(sector)!=0) {
                WaitSaveRetry(10);
                if((u16)(*action)(sector)!=0) {
                    WaitSaveRetry(10);
                    (*action)(sector);
                }
            }
        }
    }
    DiscoverSaveSlotsAndSectorMap();
}
asm(".global gSaveSectorMap\n.set gSaveSectorMap,0x030027b0\n"
    ".global gSaveSectorAction\n.set gSaveSectorAction,0x0200f37c\n"
    ".global WaitSaveRetry\n.thumb_set WaitSaveRetry,0x080033c9\n"
    ".global DiscoverSaveSlotsAndSectorMap\n.thumb_set DiscoverSaveSlotsAndSectorMap,0x0813ae31\n");

asm(".global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n");
