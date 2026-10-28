typedef unsigned char u8;
struct HandleByte43 { u8 unknown00[43]; u8 value43; };
/* The byte role remains tentative; truncate only at the physical store. */
void SetHandleByte43(struct HandleByte43 *handle, int value)
{
    handle->value43 = value;
}
