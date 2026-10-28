typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void ResetMissionChooserRequest(u8 slot, u8 request_value)
    __asm__("CoreFrontier_00060DEC");
void ResetMissionChooserRequest(u8 slot, u8 request_value)
{
    u32 context_root_address = 0x0200f44cU;
    u32 byte_offset;
    u8 *context;
    u16 *request;

    /* The real singleton address is defined before the slot offset. */
    asm("" : "+r"(context_root_address));
    byte_offset = (u32)slot * 4U + 296U;
    context = *(u8 **)context_root_address;
    request = (u16 *)(context + byte_offset);
    request[0] = 0U;
    request[1] = request_value;
}
