#include "../../../src/task_tree_core.h"
struct SlotSectors { u16 count; u8 sectors[16]; };
struct SaveHeader {
    u8 signature[8];
    u32 sequence,checksum;
    u8 slot,flags;
    u8 sectors[4];
    u8 unknown22;
};
typedef char SlotSectorsSize[sizeof(struct SlotSectors)==20?1:-1];
extern const void *SaveStorageDevice;
extern const u8 SaveSignature[8];
extern u8 LastReadSaveSlot;
extern u32 GetSlotSectors(u8,struct SlotSectors *);
extern void ReadFlashSector(u16,u32,void *,u32);
extern int MemDiff(const void *,const void *,u32);
extern u32 CalculateSaveImageChecksum(const u8 *,u32,u32);
u32 ReadValidateEncodedSaveImage(u8 slot,u8 *image)
{
    struct SlotSectors sectors;
    u32 length = 0x3ca8;
    struct SaveHeader *header;
    u32 last_sector_bytes;
    u16 attempt;
    if (slot <= 1)
        length = 0x2fc4;
    header = (struct SaveHeader *)image;
    if (SaveStorageDevice == 0)
        return 0;
    if ((u8)GetSlotSectors(slot,&sectors) != 4)
        return 0;
    last_sector_bytes = length - ((((length + 0xfff) >> 12) - 1) << 12);
    attempt = 0;
    do {
        u16 sector_index;
        for (sector_index = 0; sector_index < sectors.count; ++sector_index) {
            u8 sector = sectors.sectors[sector_index];
            if (sector_index < sectors.count - 1)
                ReadFlashSector(sector,0,image + sector_index * 0x1000,0x1000);
            else
                ReadFlashSector(sector,0,image + sector_index * 0x1000,last_sector_bytes);
        }
        if (MemDiff(image,SaveSignature,8) == 0) {
            u32 expected_checksum = header->checksum;
            header->checksum = 0;
            header->sectors[0] = 0;
            header->sectors[1] = 0;
            header->sectors[2] = 0;
            header->sectors[3] = 0;
            header->unknown22 = 0;
            if (CalculateSaveImageChecksum(image,length,0) == expected_checksum) {
                header->checksum = expected_checksum;
                goto verified;
            }
        }
        ++attempt;
    } while (attempt <= 2);
    {
        register u32 failed_status asm("r0") = 0;
        /* Preserve the native numeric failed-validation result before its test. */
        asm("" : "+r" (failed_status));
        if (failed_status == 0)
            goto failed;
    }
verified:
    if (slot <= 1)
        LastReadSaveSlot = slot;
    return 1;
failed:
    return 0;
}
asm(".global SaveStorageDevice\n.set SaveStorageDevice,0x0200f370\n"
    ".global SaveSignature\n.set SaveSignature,0x08149ff8\n"
    ".global LastReadSaveSlot\n.set LastReadSaveSlot,0x030009cc\n"
    ".global GetSlotSectors\n.thumb_set GetSlotSectors,0x0813b061\n"
    ".global ReadFlashSector\n.thumb_set ReadFlashSector,0x08141b15\n"
    ".global MemDiff\n.thumb_set MemDiff,0x081443b1\n"
    ".global CalculateSaveImageChecksum\n.thumb_set CalculateSaveImageChecksum,0x0813adf1\n");
