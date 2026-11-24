typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
struct PendingHandleCondition {
    u32 flags;
    u8 unaccessed_4[8];
    s16 signed_value;
    s16 signed_threshold;
};
u32 IsPendingHandleReady(const struct PendingHandleCondition *handle)
{
    if (handle->signed_value < handle->signed_threshold &&
        (handle->flags & 0x100u) == 0)
        return 0;
    return 1;
}
