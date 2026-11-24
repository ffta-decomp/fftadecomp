typedef unsigned short u16;
struct BackgroundRoot { unsigned int words[5]; u16 *map; };
extern struct BackgroundRoot gBackgroundRoot;
extern const unsigned char gBackgroundImage[];
extern const u16 gBackgroundMap[];
extern u16 gBackgroundFlags;
extern void *AllocateMenuStorage(unsigned int bytes);
extern void DecodeCustomLzssGraphics(void *destination, const void *source);
extern void CpuSet(const void *source, void *destination, unsigned int control);
extern void FreeMenuStorage(void *allocation);
asm(".global gBackgroundRoot\n.set gBackgroundRoot,0x03000e60\n.global gBackgroundImage\n.set gBackgroundImage,0x083afa70\n.global gBackgroundMap\n.set gBackgroundMap,0x083b3d64\n.global gBackgroundFlags\n.set gBackgroundFlags,0x03000940\n.global AllocateMenuStorage\n.thumb_set AllocateMenuStorage,0x0804ca59\n.global DecodeCustomLzssGraphics\n.thumb_set DecodeCustomLzssGraphics,0x0800543d\n.global CpuSet\n.thumb_set CpuSet,0x0814186d\n.global FreeMenuStorage\n.thumb_set FreeMenuStorage,0x0804ca6d");
void CoreRegion_0004DD54(void)
{
    void *storage;
    u16 *map;
    register const u16 *source_base asm("r6");
    register int row asm("r1");
    storage = AllocateMenuStorage(19200);
    DecodeCustomLzssGraphics(storage, gBackgroundImage);
    CpuSet(storage, (void *)0x06000000, 9600);
    FreeMenuStorage(storage);
    source_base = gBackgroundMap;
    asm("" : "+r"(source_base));
    map = gBackgroundRoot.map;
    row = 0;
    do {
        register int scaled_row asm("r0") = row << 4;
        register int next_row asm("r4") = row + 1;
        const u16 *source;
        u16 *destination;
        int remaining;
        register unsigned int destination_offset asm("r0");
        asm("" : "+r"(scaled_row), "+r"(next_row) : "r"(row));
        source = (const u16 *)((unsigned int)((scaled_row - row) * 4) + (unsigned int)source_base);
        destination_offset = row << 6;
        asm("" : "+r"(destination_offset));
        destination = (u16 *)(destination_offset + (unsigned int)map);
        remaining = 29;
        do {
            *destination++ = *source++;
        } while (--remaining >= 0);
        row = next_row;
    } while (row <= 19);
    {
        register unsigned int flags_snapshot asm("r1") = gBackgroundFlags;
        register unsigned int flags_result asm("r0");
        register unsigned int flag_mask asm("r2");
        asm("" : "+r"(flags_snapshot));
        flag_mask = 256;
        asm("" : "+r"(flag_mask));
        flags_result = flag_mask | flags_snapshot;
        asm("" : "+r"(flags_result));
        gBackgroundFlags = flags_result;
    }
}
