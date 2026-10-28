#ifndef INITIAL_PROGRESSION_DEFAULTS_INTERFACES_H
#define INITIAL_PROGRESSION_DEFAULTS_INTERFACES_H
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
extern u8 gInitialProgressionSave[];
extern const u8 *const gPrimaryDefaultNames[];
extern const u8 *const gSecondaryDefaultNames[];
extern u16 CopyEncodedTextToBuffer(u8 *destination, const u8 *source);
__asm__(
".global gInitialProgressionSave\n.set gInitialProgressionSave,0x02000000\n"
".global gPrimaryDefaultNames\n.set gPrimaryDefaultNames,0x085516D0\n"
".global gSecondaryDefaultNames\n.set gSecondaryDefaultNames,0x08565F14\n"
".global CopyEncodedTextToBuffer\n.thumb_set CopyEncodedTextToBuffer,0x08018C25\n");
#endif


/* The persistent progression numbers and default-name table entries are kept
 * literal; no narrative mode labels are inferred from these initial values. */
void InitializeProgressionDefaults(void)
{
    register u8 *save asm("r4") = gInitialProgressionSave;
    asm("" : "+r"(save));
    {
        register u32 first_offset asm("r1") = 0x2190;
        register u8 *destination asm("r0");
        register u32 initial_progression asm("r1");
        register u32 second_offset asm("r2");
        asm("" : "+r"(first_offset));
        destination = save + first_offset;
        asm("" : "+r"(destination));
        initial_progression = 1;
        asm("" : "+r"(initial_progression));
        *destination = initial_progression;
        second_offset = 0x2191;
        asm("" : "+r"(second_offset));
        destination = save + second_offset;
        asm("" : "+r"(destination));
        *destination = initial_progression;
    }
    {
        register u32 primary_offset asm("r1") = 0x1f1c;
        register u8 *destination asm("r0");
        asm("" : "+r"(primary_offset));
        destination = save + primary_offset;
        asm("" : "+r"(destination));
        CopyEncodedTextToBuffer(destination, gPrimaryDefaultNames[2]);
    }
    {
        register u32 secondary_offset asm("r2") = 0x21a0;
        register const u8 *const *defaults asm("r0");
        asm("" : "+r"(secondary_offset));
        save += secondary_offset;
        asm("" : "+r"(save));
        defaults = gSecondaryDefaultNames;
        asm("" : "+r"(defaults));
        {
            register const u8 *source asm("r1") = defaults[0];
            asm("" : "+r"(source));
            CopyEncodedTextToBuffer(save, source);
        }
    }
}
