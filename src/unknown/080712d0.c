#ifndef ROSTER_PAGE_H
#define ROSTER_PAGE_H
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
extern u8 gUnitMemory[];
extern u8 *gRosterView;
extern u8 gRosterScratch[];
extern const u8 gRosterTileArchive[];
extern void ReadRosterTileChunk(const void *,void *,u32,u32);
extern void CopyRosterHalfwords(const void *,void *,u32);
#endif

void RefreshRosterPages(void) __asm__("CoreRegion_000712D0");
void RefreshRosterPages(void)
{
    u8 *scratch=gRosterScratch;
    void *destination=(void *)0x06017b00U;
    const u8 *archive=gRosterTileArchive;
    s32 halfwords,count,index,pages;
    u8 *page_view;
    ReadRosterTileChunk(archive,scratch,52,1);
    halfwords=320;
    CopyRosterHalfwords(scratch,destination,halfwords);
    destination=(void *)0x06017d80U;
    ReadRosterTileChunk(archive,scratch,53,1);
    CopyRosterHalfwords(scratch,destination,halfwords);
    count=0;
    for(index=0;index<24;index++) {
        if(gUnitMemory[132+264*index]!=0) count++;
    }
    gRosterView[0x95c]=count;
    page_view=gRosterView;
    pages=count/4;
    if(count&3) pages++;
    page_view[0x98a]=pages;
}
__asm__(".global gUnitMemory\n.set gUnitMemory,0x02000000\n"
        ".global gRosterView\n.set gRosterView,0x03002818\n"
        ".global gRosterScratch\n.set gRosterScratch,0x02003cb0\n"
        ".global gRosterTileArchive\n.set gRosterTileArchive,0x083b5a5c\n"
        ".global ReadRosterTileChunk\n.thumb_set ReadRosterTileChunk,0x08005319\n"
        ".global CopyRosterHalfwords\n.thumb_set CopyRosterHalfwords,0x0814186d\n");
