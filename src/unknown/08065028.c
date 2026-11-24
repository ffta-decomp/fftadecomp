typedef unsigned int u32;
extern void ReleaseEventRuntimeObject(void *object);
/* Return -1 when no active event runtime object exists; otherwise release its handle. */
int ReleaseActiveEventRuntimeObject(void)
{
    void **event_root = *(void *** volatile)0x0200f454;
    if (event_root == 0 || *event_root == 0)
        return -1;
    ReleaseEventRuntimeObject(*event_root);
    return 0;
}
