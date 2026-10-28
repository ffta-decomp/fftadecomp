typedef unsigned char u8;
typedef unsigned int u32;
struct ResultWorkspace {
    u8 unknown00[193];
    u8 count;
    u8 unknown194[74];
};
typedef void (*ClearMemory)(void *, u32);
extern void PopulateResultWorkspace(void *, struct ResultWorkspace *);
asm(".global PopulateResultWorkspace\n.thumb_set PopulateResultWorkspace,0x080a7a81");

/* The phase controller consumes a null pointer for an empty result workspace. */
struct ResultWorkspace *BuildBattleResultWorkspace(void *source)
{
    ClearMemory *clear_cell = (ClearMemory *)0x0836d4b8;
    struct ResultWorkspace *workspace = (struct ResultWorkspace *)0x0200f8c0;
    (*clear_cell)(workspace, 268);
    PopulateResultWorkspace(source, workspace);
    if (workspace->count == 0)
        return 0;
    return workspace;
}
