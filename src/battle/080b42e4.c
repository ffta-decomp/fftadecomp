/* Method-local interface declarations from the frozen build. */
typedef unsigned short u16;
typedef signed short s16;
extern int ReadClassProperty(u16,int);
extern int ReadItemProperty(u16,int);

asm(".global ReadClassProperty\n.thumb_set ReadClassProperty,0x80ca7a5\n.global ReadItemProperty\n.thumb_set ReadItemProperty,0x80ccd51");
static inline u16 BuildClassDescriptor(u16 class_id)
{
    s16 category = ReadClassProperty(class_id,3);
    if (category == 13 || category == 14) return 448;
    if (category == 19) return 448;
    return 384;
}
u16 BuildItemOrClassDescriptorFlags(u16 item_id,u16 class_id)
{
    u16 saved_item = item_id;
    s16 category;
    u16 properties;
    u16 flags;
    if (!item_id) {
        return BuildClassDescriptor(class_id);
    }
    properties = ReadItemProperty(item_id,4);
    flags = 0;
    if (properties & 128) {
        return BuildClassDescriptor(class_id);
    }
    if (properties & 64) flags = 1;
    flags |= 128;
    if (!ReadItemProperty(item_id,11)) flags |= 256;
    switch ((u16)ReadItemProperty(saved_item,6)) {
    case 2: return 4;
    case 3:
        if ((flags & 15) == 1) return flags;
        flags |= 66;
        return flags;
    case 4: return flags | 32;
    case 5: case 6:
        flags |= 48;
        return flags;
    case 7: return flags | 16;
    default: return flags | 64;
    }
}
