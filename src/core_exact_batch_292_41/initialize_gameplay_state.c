#ifndef GAMEPLAY_INITIALIZATION_INTERFACES_H
#define GAMEPLAY_INITIALIZATION_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*ClearBytesFunction)(void *, u32);
struct InitialRosterDefinition {
    u8 preceding[0x438];
    u16 count;
    u16 alignment;
    const u8 *records;
};
extern u8 gInitialSaveImage[0x3ca8];
extern u8 gInitialSecondaryRegion[0x4000];
extern u8 gInitialUnitRecords[];
extern const u8 gInitialSaveTemplate[4];
extern const struct InitialRosterDefinition gInitialRosterDefinition;
extern ClearBytesFunction gClearBytesFunction;
extern u8 gInitializationByte284C;
extern u8 gInitializationByte280C;
extern void SeedRandom(u32 seed);
extern void CopyBytes(void *destination, const void *source, u32 bytes);
extern void EnableFixedJobFlags(void);
extern void InitializePersistentFields099C4(void);
extern void ConstructInitialUnit(void *destination, const void *source, u8 level);
extern void InitializeValuationCategoryPairs(void);
extern int AddInventoryItem(u16 item, u8 quantity);
/* Link existing implementations and real objects; no helper bodies or stubs. */
__asm__(
".global gInitialSaveImage\n.set gInitialSaveImage,0x02000000\n"
".global gInitialSecondaryRegion\n.set gInitialSecondaryRegion,0x02003CB0\n"
".global gInitialUnitRecords\n.set gInitialUnitRecords,0x02000080\n"
".global gInitialSaveTemplate\n.set gInitialSaveTemplate,0x0851BA4E\n"
".global gInitialRosterDefinition\n.set gInitialRosterDefinition,0x0854CD7C\n"
".global gClearBytesFunction\n.set gClearBytesFunction,0x0836D4B8\n"
".global gInitializationByte284C\n.set gInitializationByte284C,0x0300284C\n"
".global gInitializationByte280C\n.set gInitializationByte280C,0x0300280C\n"
".global SeedRandom\n.thumb_set SeedRandom,0x08002825\n"
".global CopyBytes\n.thumb_set CopyBytes,0x081443FD\n"
".global EnableFixedJobFlags\n.thumb_set EnableFixedJobFlags,0x080C9341\n"
".global InitializePersistentFields099C4\n.thumb_set InitializePersistentFields099C4,0x080099C5\n"
".global ConstructInitialUnit\n.thumb_set ConstructInitialUnit,0x080C9645\n"
".global InitializeValuationCategoryPairs\n.thumb_set InitializeValuationCategoryPairs,0x080CC0DD\n"
".global AddInventoryItem\n.thumb_set AddInventoryItem,0x080CA901\n");
typedef char initial_definition_count_offset[((u32)&((struct InitialRosterDefinition *)0)->count==0x438)?1:-1];
typedef char initial_definition_records_offset[((u32)&((struct InitialRosterDefinition *)0)->records==0x43c)?1:-1];
#endif


void InitializeGameplayState(void)
{
    u32 count;
    u32 ordinal;
    u32 unit_offset;
    const u8 *initial_definition;
    u32 zero;

    {
        register ClearBytesFunction *clear asm("r5") = &gClearBytesFunction;
        register u8 *save asm("r4");
        /* Two original object definitions; both are consumed by the clears. */
        asm("" : "+r"(clear));
        save = gInitialSaveImage;
        asm("" : "+r"(save));
        (*clear)(save, 0x3ca8);
        (*clear)(gInitialSecondaryRegion, 0x4000);
        SeedRandom(1);
        save += 0x2fc0;
        asm("" : "+r"(save));
        CopyBytes(save, gInitialSaveTemplate, 4);
    }
    EnableFixedJobFlags();
    InitializePersistentFields099C4();

    count = gInitialRosterDefinition.count;
    {
        register const u8 *records asm("r1") = gInitialRosterDefinition.records;
        asm("" : "+r"(records));
        initial_definition = records;
    }
    ordinal = 0;
    if (ordinal < count) {
        register const u8 *definition asm("r4") = initial_definition;
        /* The template cursor starts only after the empty-roster guard. */
        asm("" : "+r"(definition));
        unit_offset = 0;
        do {
            register u32 unit_address asm("r0") = 0x02000080;
            register u32 stride asm("r2");
            asm("" : "+r"(unit_address));
            unit_address = unit_offset + unit_address;
            /* Numeric byte-address phase precedes its pointer consumption. */
            asm("" : "+r"(unit_address));
            ConstructInitialUnit((u8 *)unit_address, definition, 0);
            definition += 48;
            stride = 264;
            asm("" : "+r"(stride));
            unit_offset += stride;
            ++ordinal;
        } while (ordinal < count);
    }
    InitializeValuationCategoryPairs();

    {
        register u32 enabled asm("r1") = 1;
        register u8 *save asm("r6");
        register int remaining asm("r5");
        register u32 field_offset asm("r2");
        register u8 *flag asm("r0");
        /* Reconstruct the fresh persistent base and actual descending stores. */
        asm("" : "+r"(enabled));
        save = gInitialSaveImage;
        asm("" : "+r"(save));
        remaining = 8;
        asm("" : "+r"(remaining));
        field_offset = 0x21c4;
        asm("" : "+r"(field_offset));
        flag = save + field_offset;
        do {
            *flag = enabled;
            flag -= 2;
            --remaining;
        } while (remaining >= 0);

        zero = 0;
        {
            register u32 resource_offset asm("r0") = 0x1f64;
            register u32 *resource asm("r1");
            asm("" : "+r"(resource_offset));
            resource = (u32 *)(save + resource_offset);
            asm("" : "+r"(resource));
            *resource = 5000;
        }
        AddInventoryItem(362, 10);
        AddInventoryItem(367, 4);
        AddInventoryItem(373, 4);
        AddInventoryItem(375, 2);
        gInitializationByte284C = zero;
        gInitializationByte280C = zero;
        {
            register u32 final_offset asm("r2") = 0x2185;
            register u8 *final_flag asm("r1");
            asm("" : "+r"(final_offset));
            final_flag = save + final_offset;
            asm("" : "+r"(final_flag));
            *final_flag = 1;
        }
    }
}
