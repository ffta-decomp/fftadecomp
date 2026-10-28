typedef unsigned char u8;
typedef unsigned short u16;
struct HandleHalfwordView { u8 unaccessed[18]; u16 first; u16 unaccessed_at20; u16 second; };
void SetHandleHalfwords(struct HandleHalfwordView *handle, u16 first, u16 second)
{
    handle->first = first;
    handle->second = second;
}
