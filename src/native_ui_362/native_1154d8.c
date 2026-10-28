typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u16 counter,pad;u32 untouched;void *child;} TimedWork;
extern void *CreateScript(const void *,void *) __asm__("0x080D3E9C");
extern void *PollScript(void *) __asm__("0x080D3F08");
extern u32 LayerMask(u32) __asm__("0x080035A8");
u32 RemainingBand43_001154D8(void *parent,u16 *event,TimedWork *work)
{
    switch(*event) {
    case 0:
        work->counter=30;
        break;
    case 256:
        if(!--work->counter) {
            work->child=CreateScript((const void *)0x0894DC2C,parent);
            ++*event;
        }
        break;
    case 257:
        work->child=PollScript(work->child);
        if(!work->child) {
            *(u16 *)0x03000940&=~LayerMask(3);
            ++*event;
        }
        break;
    case 258:
        *event=2;
        break;
    }
    return 0;
}
