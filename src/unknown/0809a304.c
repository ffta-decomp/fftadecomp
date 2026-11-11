typedef unsigned char u8;
typedef unsigned int u32;

struct BattleStatusNode {
    u8 unknown_00[30];
    /* Numeric status meanings remain tentative; preserve the observed byte. */
    u8 status_code;
    u8 unknown_1f[17];
    u32 flags;
};
extern void RefreshNodeBaseStatus(struct BattleStatusNode *);

void RefreshBattleNodeStatus(struct BattleStatusNode *node)
{
    RefreshNodeBaseStatus(node);
    if ((node->flags & 8192) != 0)
        node->status_code = 14;
    if ((node->flags & 4096) != 0)
        node->status_code = 5;
    if ((node->flags & 64) != 0)
        node->status_code = 15;
}

asm(".global RefreshNodeBaseStatus\n"
    ".thumb_set RefreshNodeBaseStatus, 0x0809801d\n");
