typedef unsigned short u16;
struct SequenceEntry {unsigned char data[20];};
struct SequenceObject {unsigned char unknown0[10];u16 phase;u16 index;unsigned char unknown14[38];struct SequenceEntry *base;struct SequenceEntry *current;};
void CoreDependency29_00021E28(struct SequenceObject *object, unsigned int index)
{
    object->index=index;
    object->phase=0;
    object->current=&object->base[index];
}
