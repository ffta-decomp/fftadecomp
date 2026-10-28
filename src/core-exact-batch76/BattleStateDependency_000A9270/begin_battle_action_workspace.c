extern unsigned char gBattleActionWorkspace[];
extern void *GetGameAllocationPool(void);
extern void *GetBattleActionRegistry(void);
extern void *GetBattleRegistryContextAt8(void *registry);
extern void InitializeBattleActionWorkspace(void *workspace, void *pool, void *context);
void BeginBattleActionWorkspace(void)
{
    void *workspace = gBattleActionWorkspace;
    void *pool = GetGameAllocationPool();
    void *registry = GetBattleActionRegistry();
    void *context = GetBattleRegistryContextAt8(registry);
    InitializeBattleActionWorkspace(workspace, pool, context);
}
asm(".global gBattleActionWorkspace\n.set gBattleActionWorkspace,0x0200F9E8\n"
    ".global GetGameAllocationPool\n.thumb_set GetGameAllocationPool,0x08022869\n"
    ".global GetBattleActionRegistry\n.thumb_set GetBattleActionRegistry,0x08096d7d\n"
    ".global GetBattleRegistryContextAt8\n.thumb_set GetBattleRegistryContextAt8,0x08099c31\n"
    ".global InitializeBattleActionWorkspace\n.thumb_set InitializeBattleActionWorkspace,0x080a8afd\n"
);
