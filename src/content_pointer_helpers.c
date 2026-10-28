typedef unsigned short u16;

extern const void *const gJobContentPointers[];

const void *GetContentPointer123(u16 index)
{
    return gJobContentPointers[index + 123];
}

u16 AddContentIndex1081(u16 index)
{
    return index + 1081;
}
