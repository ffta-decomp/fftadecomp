typedef unsigned short u16;
typedef unsigned int u32;
struct PendingHandleFlagWord { u32 flags; };
/* Halfword masks must not narrow the untouched upper flags. */
void ChangePendingHandleFlags(struct PendingHandleFlagWord *handle, u16 clear_mask, u16 set_mask)
{
    handle->flags = (handle->flags & ~(u32)clear_mask) | (u32)set_mask;
}
