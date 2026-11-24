typedef unsigned int u32;
typedef struct TaskGroup TaskGroup;
typedef struct SceneTaskStorage {
    unsigned char unknown[32];
    TaskGroup *group;
    void *allocation;
} SceneTaskStorage;
extern void *AllocateGlobalPoolBytes(u32 amount);
extern TaskGroup *CreateTaskGroup(void *storage, u32 amount);
extern void CallClearViaR2(void *storage, u32 amount, void (*clear)(void *, u32));
__asm__(".global AllocateGlobalPoolBytes\n.thumb_set AllocateGlobalPoolBytes, 0x08022841\n.global CreateTaskGroup\n.thumb_set CreateTaskGroup, 0x08005c15\n.global CallClearViaR2\n.thumb_set CallClearViaR2, 0x0814224d");
#define CURRENT_STORAGE (*(SceneTaskStorage **)0x0200f438U)
#define CLEAR_CALLBACK (*(void (**)(void *, u32))0x0836d4b8U)
void InitializeSceneTaskStorage(u32 amount) __asm__("SceneRegisteredRoot_00025324");
void InitializeSceneTaskStorage(u32 amount)
{
    unsigned char *allocation = AllocateGlobalPoolBytes(amount);
    u32 storage_bytes;
    CURRENT_STORAGE = (SceneTaskStorage *)allocation;
    {
        register void (**clear_cell)(void *, u32) __asm__("r0") = (void (**)(void *, u32))0x0836d4b8U;
        register u32 clear_amount __asm__("r1") = 1160;
        /* Defined call operands: retain the original cell/count setup before
           dereferencing the callback; the retained count remains ordinary C. */
        __asm__("" : "+r"(clear_cell), "+r"(clear_amount));
        storage_bytes = clear_amount;
        {
            register void (*clear)(void *, u32) __asm__("r2") = *clear_cell;
            /* Capture callback before call argument R0 replaces clear_cell. */
            __asm__("" : "+r"(clear));
            CallClearViaR2(allocation, clear_amount, clear);
        }
    }
    CURRENT_STORAGE->allocation = allocation;
    CURRENT_STORAGE->group = CreateTaskGroup(allocation + storage_bytes, amount - 1160);
}
