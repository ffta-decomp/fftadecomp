typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Only the observed physical layout, not a complete item-schema interpretation. */
struct ItemDefinitionView {
    u8 unknown00[26];
    u8 attributes[3];
    u8 unknown1d[3];
};
typedef char ItemSize[(sizeof(struct ItemDefinitionView)==32)?1:-1];
typedef char AttributeOffset[((u32)&((struct ItemDefinitionView *)0)->attributes==26)?1:-1];
extern const struct ItemDefinitionView ItemDefinitionsForAttributeRule[];
__asm__(".global ItemDefinitionsForAttributeRule\n.set ItemDefinitionsForAttributeRule,0x0851d180");
