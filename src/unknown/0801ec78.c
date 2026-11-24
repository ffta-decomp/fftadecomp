typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef struct SpatialDescriptorTable { u16 count; u8 records[0]; } __attribute__((packed)) SpatialDescriptorTable;
extern unsigned QuerySpatialDescriptor(s16,s16,s16,s16,s16,const u8 *,u8,u8);
void QuerySpatialDescriptorBatch(u16 x,u16 y,u16 z,u16 extent,u16 threshold,const SpatialDescriptorTable *table,u8 *output,u8 mode_a,u8 mode_b)
{
    u16 index=0;
    while((unsigned)index < (unsigned)table->count) {
        output[index]=QuerySpatialDescriptor((s16)x,(s16)y,(s16)z,(s16)extent,(s16)threshold,table->records+6*index,mode_a,mode_b);
        index++;
    }
}
asm(".global QuerySpatialDescriptor\n.thumb_set QuerySpatialDescriptor,0x0801e955\n");
