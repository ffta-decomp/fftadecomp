typedef signed short s16;
typedef unsigned char u8;
extern u8 *GetEventRuntimePayload(void *event_object);
/* Read the signed field at offset 6 of an event object's payload (object + 0x18). */
s16 GetEventRuntimePayloadField06(void *event_object)
{
    return *(s16 *)(GetEventRuntimePayload(event_object) + 6);
}
