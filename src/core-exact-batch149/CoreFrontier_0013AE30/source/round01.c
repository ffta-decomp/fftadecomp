typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SaveSectorHeader {
    u8 signature[8]; u32 version; u8 unknown_0c[4];
    u8 slot; u8 unknown_11; u8 sectors[4]; u8 unknown_16[106];
};
typedef char HeaderSize[sizeof(struct SaveSectorHeader)==128?1:-1];
extern u32 gHighestSaveVersion;
extern u8 gPresentSaveSlots;
extern u16 gSaveSectorMap[16];
extern u8 gCurrentSaveSlot;
extern const u8 gSaveSignature[8];
extern void ReadFlashSector(u16,u32,void *,u32);
extern int CompareBytes(const void *,const void *,u32);
void DiscoverSaveSlotsAndSectorMap(void)
{
    struct SaveSectorHeader header;
    /* Native workspace spans16B; only slots0..2 are accessed. */
    s32 best_version[4];
    u8 best_sector[3];
    u32 selected_slot;
    u16 index,slot,sector;
    selected_slot=255;
    gHighestSaveVersion=0;
    gPresentSaveSlots=0;
    for(index=0;index<=15;index++)gSaveSectorMap[index]|=65535;
    for(slot=0;slot<=2;slot++) {
        best_version[slot]=-1;
        best_sector[slot]=255;
        for(sector=0;sector<=15;sector++) {
            ReadFlashSector(sector,0,&header,128);
            if(CompareBytes(&header,gSaveSignature,8)==0 && header.slot==slot) {
                gPresentSaveSlots|=1<<slot;
                if(best_version[slot]<(s32)header.version) {
                    best_version[slot]=header.version;
                    best_sector[slot]=sector;
                }
                if(gHighestSaveVersion<header.version) {
                    gHighestSaveVersion=header.version;
                    if(slot<=1)selected_slot=(u8)slot;
                }
            }
        }
    }
    for(slot=0;slot<=2;slot++) {
        if(best_sector[slot]!=255) {
            ReadFlashSector(best_sector[slot],0,&header,128);
            gSaveSectorMap[header.sectors[0]]=slot<<8;
            gSaveSectorMap[header.sectors[1]]=(slot<<8)|1;
            gSaveSectorMap[header.sectors[2]]=(slot<<8)|2;
            gSaveSectorMap[header.sectors[3]]=(slot<<8)|3;
        }
    }
    if(selected_slot!=255)gCurrentSaveSlot=*(u8 *)&selected_slot;
    else gCurrentSaveSlot=0;
}
asm(".global gHighestSaveVersion\n.set gHighestSaveVersion,0x03000860\n"
    ".global gPresentSaveSlots\n.set gPresentSaveSlots,0x030009c8\n"
    ".global gSaveSectorMap\n.set gSaveSectorMap,0x030027b0\n"
    ".global gCurrentSaveSlot\n.set gCurrentSaveSlot,0x030009cc\n"
    ".global gSaveSignature\n.set gSaveSignature,0x08149ff8\n"
    ".global ReadFlashSector\n.thumb_set ReadFlashSector,0x08141b15\n"
    ".global CompareBytes\n.thumb_set CompareBytes,0x081443b1\n");
