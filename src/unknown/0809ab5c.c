typedef unsigned int u32;
struct BattleIdentityPayload { void *unit; };
struct BattleIdentitySearch {
    void *unit;
    u32 unknown_04;
    struct BattleIdentityPayload *found;
};
extern struct BattleIdentityPayload *GetIdentityNodePayload(void *node);
int SelectBattlePayloadByUnitIdentity(void *node, struct BattleIdentitySearch *search)
{
    struct BattleIdentityPayload *payload;
    int result;
    payload = GetIdentityNodePayload(node);
    if (payload->unit == search->unit)
        goto matched;
    result = 1;
    goto finished;
matched:
    search->found = payload;
    result = 0;
finished:
    return result;
}
asm(".global GetIdentityNodePayload\n.thumb_set GetIdentityNodePayload,0x080c7b75\n");
