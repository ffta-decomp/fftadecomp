typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
extern u32 IsTaskStateTwo(void*);
extern void ReleaseTask(void*);
__asm__(".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo,0x08005bb1\n.global ReleaseTask\n.thumb_set ReleaseTask,0x08005b59");
u32 PollStageHandleArray(void **tasks,u32 count_word) __asm__("RemainingBand43_000D48DC");
u32 PollStageHandleArray(void **tasks,u32 count_word)
{
    u32 count=(u16)count_word;
    u32 all_done=1;
    u16 index;
    for(index=0;index<count;index++) {
        register u32 offset __asm__("r1")=(u32)index*4;
        void *task;
        register u32 saved_offset __asm__("r4");
        __asm__("" : "+r"(offset));
        task=*(void **)(offset+(u32)tasks);
        /* The first read consumes the ordinal offset before its saved copy. */
        __asm__("" : "+r"(task) : "r"(offset));
        saved_offset=offset;
        __asm__("" : "+r"(saved_offset));
        if(task) {
            u32 raw=IsTaskStateTwo(task);
            u32 ready;
            if(raw) {
                ready=1;
            } else {
                /* Preserve the original independent zero definition. This
                   initialized raw result is dead after this branch. */
                __asm__("" : "+r"(raw));
                ready=0;
            }
            /* Both are initialized native definitions; preserve numeric bool
               before its branch and the byte offset across the opaque query. */
            __asm__("" : "+r"(ready));
            if(ready) {
                register void **slot __asm__("r4")=(void **)(saved_offset+(u32)tasks);
                /* The byte offset dies; its R4 becomes the actual slot base
                   that must survive ReleaseTask for the following zero store. */
                __asm__("" : "+r"(slot));
                ReleaseTask(*slot);
                *slot=0;
            } else {
                all_done=0;
            }
        }
    }
    return all_done;
}
