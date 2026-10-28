typedef unsigned char u8;
typedef unsigned short u16;
struct BattlePendingHandleOwner {
    u8 unaccessed_prefix[68];
    void *primary;
    u8 unaccessed_72[4];
    void *secondary[2];
};
extern void ChangePendingHandleFlags(void *handle, u16 clear_mask, u16 set_mask);
void UpdateBattlePendingHandleFlags(struct BattlePendingHandleOwner *owner,
    u16 clear_mask, u16 set_mask)
{
    int ordinal;
    ChangePendingHandleFlags(owner->primary, clear_mask, set_mask);
    for (ordinal = 0; ordinal <= 1; ordinal++) {
        void *handle = owner->secondary[ordinal];
        if (handle != 0)
            ChangePendingHandleFlags(handle, clear_mask, set_mask);
    }
}
asm(".global ChangePendingHandleFlags\n.thumb_set ChangePendingHandleFlags,0x08021DE5\n");
