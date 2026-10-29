typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void BiosCpuFastSet(const void *,void *,u32);
extern void BiosLz77UnCompWram(const void *,void *);
extern void WriteMapTerrainRuns(const u8 *,const u16 *);
struct TerrainSourceHeader { u32 format:8; u32 index:24; } __attribute__((packed));
struct TerrainMapRecord { u8 unknown00[16]; u32 terrain_relative; u8 unknown14[68]; } __attribute__((packed));
typedef char CheckHeaderSize[sizeof(struct TerrainSourceHeader)==4?1:-1];
typedef char CheckRecordSize[sizeof(struct TerrainMapRecord)==88?1:-1];
typedef char CheckTerrainOffset[(u32)&((struct TerrainMapRecord *)0)->terrain_relative==16?1:-1];
extern const struct TerrainMapRecord gAuthoredMapRecords[];
extern u8 gMapTerrainCells[],gMapTerrainScratch[];
__asm__(".global BiosCpuFastSet\n.thumb_set BiosCpuFastSet,0x08141869\n"
        ".global BiosLz77UnCompWram\n.thumb_set BiosLz77UnCompWram,0x08141891\n"
        ".global WriteMapTerrainRuns\n.thumb_set WriteMapTerrainRuns,0x0801f099\n"
        ".global gAuthoredMapRecords\n.set gAuthoredMapRecords,0x08569104\n"
        ".global gMapTerrainCells\n.set gMapTerrainCells,0x02007cb0\n"
        ".global gMapTerrainScratch\n.set gMapTerrainScratch,0x02003cb0");
void LoadAuthoredMapTerrainSource(const u8 *) __asm__("Registered39_0001F438");
void LoadAuthoredMapTerrainSource(const u8 *source)
{
    const struct TerrainSourceHeader *header=(const struct TerrainSourceHeader *)source;
    const u8 *runs;
    u32 empty;
    if(header->format==16) {
        BiosLz77UnCompWram(source,gMapTerrainCells);
        return;
    }
    if(header->format==1) {
        u32 index=header->index;
        if(index!=0xffffff) {
            const struct TerrainMapRecord *record=&gAuthoredMapRecords[index];
            u32 offset=record->terrain_relative;
            LoadAuthoredMapTerrainSource((const u8 *)gAuthoredMapRecords+offset);
        } else {
            empty=0;
            BiosCpuFastSet(&empty,gMapTerrainCells,0x01000080);
        }
        runs=source+4;
        goto apply_runs;
    }
    if(header->format!=17)goto raw_copy;
    {
        u32 index=header->index;
        if(index!=0xffffff) {
            const struct TerrainMapRecord *record=&gAuthoredMapRecords[index];
            u32 offset=record->terrain_relative;
            LoadAuthoredMapTerrainSource((const u8 *)gAuthoredMapRecords+offset);
        } else {
            empty=0;
            BiosCpuFastSet(&empty,gMapTerrainCells,0x01000080);
        }
        BiosLz77UnCompWram(source+4,gMapTerrainScratch);
        runs=gMapTerrainScratch;
    }
apply_runs:
    WriteMapTerrainRuns(runs,0);
    goto done;
raw_copy:
    BiosCpuFastSet(source+4,gMapTerrainCells,128);
done:
    return;
}
