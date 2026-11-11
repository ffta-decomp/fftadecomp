typedef unsigned char u8;
struct PendingHandleCode { u8 prefix[30]; u8 tagged_code; };
int ReadPendingHandleTag(const struct PendingHandleCode *handle)
{
    if (handle->tagged_code & 0x80)
        return handle->tagged_code & ~0x80;
    return -1;
}
