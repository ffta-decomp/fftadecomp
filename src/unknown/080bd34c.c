struct BattleRequest;
unsigned int PollRequest(struct BattleRequest *) __asm__("RetailCall_080bd1ec");
unsigned char CoreFrontier_000BD34C(struct BattleRequest *request)
{
    return (unsigned char)PollRequest(request);
}
asm(".global RetailCall_080bd1ec\n.thumb_set RetailCall_080bd1ec,0x080bd1ed\n");
