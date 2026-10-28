typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Choice {u16 index,enabled,ordinal,unknown6;u32 descriptor;u16 label;u8 category,unknown15;u16 value,unknown18;};
struct Entry8 {u8 unknown[4];u16 label;u8 tail[2];};
struct Entry36 {u8 unknown[4];u16 label;u8 tail[30];};
struct Row {u8 values[8];};
extern const struct Row gChoices[];
extern const u32 gDescriptors[];
extern const struct Entry8 gCategory3[],gCategory5[],gCategory6[],gCategory7[];
extern const struct Entry36 gCategory4[];
extern u8 GetGameFlag(u16);
typedef char ChoiceSize20[(sizeof(struct Choice)==20)?1:-1];
typedef char Entry8Size8[(sizeof(struct Entry8)==8)?1:-1];
typedef char Entry36Size36[(sizeof(struct Entry36)==36)?1:-1];

asm(".global gChoices\n.set gChoices,0x08391d1c\n.global gDescriptors\n.set gDescriptors,0x085668b0\n.global gCategory3\n.set gCategory3,0x08391b20\n.global gCategory4\n.set gCategory4,0x08391a6c\n.global gCategory5\n.set gCategory5,0x08391b48\n.global gCategory6\n.set gCategory6,0x08391b50\n.global gCategory7\n.set gCategory7,0x08391b58\n.global GetGameFlag\n.thumb_set GetGameFlag,0x80c9541");
void CoreRegion_0003CDAC(int *count_out, int group, struct Choice *choices)
{
    int count = *count_out;
    register int row_index asm("r0");
    register const struct Row *row_base asm("r1");
    register u32 row_address asm("r0");
    register const struct Row *row asm("r3");
    int entry;
    row_base = gChoices;
    /* The original ROM base is defined before the subtracted index. */
    asm("" : "+r"(row_base));
    row_index = group - 2;
    /* Original SUB result is a full working value consumed by row addressing. */
    asm("" : "+r"(row_index));
    row_address = (u32)row_index * sizeof(*row);
    asm("" : "+r"(row_address));
    row = (const struct Row *)(row_address + (u32)row_base);
    asm("" : "+r"(row));
    entry = row->values[1];
    if (entry) {
        struct Choice *choice;
        register u32 choice_address asm("r1");
        --entry;
        choice_address = (u32)count * sizeof(*choice);
        asm("" : "+r"(choice_address));
        choice_address += (u32)choices;
        /* Consume the original destructive byte-offset-to-row address. */
        asm("" : "+r"(choice_address));
        choice = (struct Choice *)choice_address;
        choice->index = count;
        choice->enabled = 1;
        choice->ordinal = count;
        choice->descriptor = gDescriptors[2];
        choice->label = gCategory3[entry].label;
        choice->category = 3;
        choice->value = entry;
        ++count;
    }
    entry = row->values[2];
    if (entry) {
        struct Choice *choice;
        register u32 choice_address asm("r1");
        --entry;
        choice_address = (u32)count * sizeof(*choice);
        asm("" : "+r"(choice_address));
        choice_address += (u32)choices;
        /* Consume the original destructive byte-offset-to-row address. */
        asm("" : "+r"(choice_address));
        choice = (struct Choice *)choice_address;
        choice->index = count;
        choice->enabled = 1;
        choice->ordinal = count;
        choice->descriptor = gDescriptors[3];
        choice->label = gCategory4[entry].label;
        choice->category = 4;
        choice->value = entry;
        ++count;
    }
    entry = row->values[3];
    if (entry) {
        struct Choice *choice;
        register u32 choice_address asm("r1");
        --entry;
        choice_address = (u32)count * sizeof(*choice);
        asm("" : "+r"(choice_address));
        choice_address += (u32)choices;
        /* Consume the original destructive byte-offset-to-row address. */
        asm("" : "+r"(choice_address));
        choice = (struct Choice *)choice_address;
        choice->index = count;
        choice->enabled = 1;
        choice->ordinal = count;
        choice->descriptor = gDescriptors[4];
        choice->label = gCategory5[entry].label;
        choice->category = 5;
        choice->value = entry;
        ++count;
    }
    entry = row->values[4];
    if (entry && GetGameFlag(1448)) {
        struct Choice *choice;
        register u32 choice_address asm("r1");
        --entry;
        choice_address = (u32)count * sizeof(*choice);
        asm("" : "+r"(choice_address));
        choice_address += (u32)choices;
        /* Consume the original destructive byte-offset-to-row address. */
        asm("" : "+r"(choice_address));
        choice = (struct Choice *)choice_address;
        choice->index = count;
        choice->enabled = 1;
        choice->ordinal = count;
        choice->descriptor = gDescriptors[5];
        choice->label = gCategory6[entry].label;
        choice->category = 6;
        choice->value = entry;
        ++count;
    }
    row_base = gChoices;
    /* The original ROM base is defined before the subtracted index. */
    asm("" : "+r"(row_base));
    row_index = group - 2;
    asm("" : "+r"(row_index));
    row_address = (u32)row_index * sizeof(*row);
    asm("" : "+r"(row_address));
    row_address += (u32)row_base;
    /* The post-helper row is a separate one-use derived address. */
    asm("" : "+r"(row_address));
    entry = ((const struct Row *)row_address)->values[5];
    if (entry) {
        struct Choice *choice;
        register u32 choice_address asm("r1");
        --entry;
        choice_address = (u32)count * sizeof(*choice);
        asm("" : "+r"(choice_address));
        choice_address += (u32)choices;
        /* Consume the original destructive byte-offset-to-row address. */
        asm("" : "+r"(choice_address));
        choice = (struct Choice *)choice_address;
        choice->index = count;
        choice->enabled = 1;
        choice->ordinal = count;
        choice->descriptor = gDescriptors[6];
        choice->label = gCategory7[entry].label;
        choice->category = 7;
        choice->value = entry;
        ++count;
    }
    *count_out = count;
}
