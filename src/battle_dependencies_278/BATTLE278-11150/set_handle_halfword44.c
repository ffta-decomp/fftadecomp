typedef unsigned char u8;
typedef signed short s16;
struct HandleHalfword44 { u8 unknown00[44]; s16 value44; };
/* The halfword role is tentative; preserve the physical store and truncation. */
void SetHandleHalfword44(struct HandleHalfword44 *handle, int value)
{
    handle->value44 = value;
}
