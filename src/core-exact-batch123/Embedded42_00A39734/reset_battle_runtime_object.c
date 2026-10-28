typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct BattleRuntimeObject {
    u16 flags;
    u8 unknown_02[4];
    u16 state_at_06;
    s16 index_at_08;
    s16 index_at_0a;
    u8 unknown_0c[50];
    u8 byte_at_3e;
    u8 unknown_3f[277];
    u32 word_at_154;
};
void ResetBattleRuntimeObject(struct BattleRuntimeObject *object)
    __asm__("Embedded42_00A39734");
/* The enclosing type and field meanings are tentative; these widths and offsets
 * are the complete accessed prefix of the native callback, not a full record. */
void ResetBattleRuntimeObject(struct BattleRuntimeObject *object)
{
    object->flags &= 0xfffd;
    object->state_at_06 = 0xffff;
    object->index_at_08 = -1;
    object->index_at_0a = -1;
    object->byte_at_3e = 0;
    object->flags |= 0x20;
    object->word_at_154 = 0;
}
