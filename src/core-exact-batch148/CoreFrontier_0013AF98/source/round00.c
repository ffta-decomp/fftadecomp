typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SaveSectorList { u16 count; u8 sectors[0]; };
typedef char SectorArrayOffset[(u32)&(((struct SaveSectorList *)0)->sectors)==2?1:-1];
extern u16 gSaveSectorMap[16];
extern u16 gSaveSectorScanStartValue;
u8 CollectSaveSectorAllocationCandidates(u8 slot,struct SaveSectorList *candidates,
                                       struct SaveSectorList *owned)
{
    u16 count,index,sector;
    const u16 *scan_start;
    count=0;
    index=0;
    scan_start=&gSaveSectorScanStartValue;
    for(;index<=15;index++) {
        if((gSaveSectorMap[index]>>8)==slot)
            owned->sectors[count++]=index;
    }
    owned->count=count;
    sector=*scan_start&15;
    count=0;
    index=0;
    for(;index<=15;index++) {
        if(gSaveSectorMap[sector]==65535)
            candidates->sectors[count++]=sector;
        if(sector<=14)sector++;
        else sector=0;
    }
    for(index=0;index<owned->count;index++)
        candidates->sectors[count++]=owned->sectors[index];
    candidates->count=count;
    return count;
}
asm(".global gSaveSectorMap\n.set gSaveSectorMap,0x030027b0\n"
    ".global gSaveSectorScanStartValue\n.set gSaveSectorScanStartValue,0x03000eb4\n");
