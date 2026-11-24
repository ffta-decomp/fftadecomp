typedef unsigned short u16;
typedef unsigned int u32;
extern u16 *GetTaskPayload(void*);
__asm__(".global GetTaskPayload\n.thumb_set GetTaskPayload,0x08005bfd");
void SetFollowupDelay(void *task,u32 delay_word) __asm__("RemainingBand43_000DF950");
void SetFollowupDelay(void *task,u32 delay_word)
{
    u16 delay=(u16)delay_word;
    GetTaskPayload(task)[6]=delay;
}
