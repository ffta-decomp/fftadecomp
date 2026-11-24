struct BattleRequest;
void *Allocate(unsigned int) __asm__("RetailCall_08022840");
void InitializeRequest(struct BattleRequest *) __asm__("RetailCall_080bd14c");
struct BattleRequest *CoreFrontier_000BD328(void)
{
    struct BattleRequest *request=Allocate(76);
    InitializeRequest(request);
    return request;
}
asm(".global RetailCall_08022840\n.thumb_set RetailCall_08022840,0x08022841\n.global RetailCall_080bd14c\n.thumb_set RetailCall_080bd14c,0x080bd14d\n");
