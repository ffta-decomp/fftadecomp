typedef unsigned char u8;
typedef unsigned int u32;
struct WorksetReadyView { u8 prefix[15]; u8 ready; };
typedef char ReadyOffset[(u32)&(((struct WorksetReadyView *)0)->ready)==15?1:-1];
u32 HasWorksetSelection(const struct WorksetReadyView *workset)
{
    u32 selected = 0;
    if (workset->ready == 1)
        selected = 1;
    return selected;
}
