typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern u32 ReadItemProperty(u32 item_id, u32 property);
extern void PlayGameCue(u32 cue);
asm(".global ReadItemProperty\n.thumb_set ReadItemProperty,0x080ca7a5\n"
    ".global PlayGameCue\n.thumb_set PlayGameCue,0x08141521\n");

void PlayItemCategoryCue(u32 raw_item_id) asm("BattleRuntimeDependency_000A7EC4");
void PlayItemCategoryCue(u32 raw_item_id)
{
    u32 item_id = (u16)raw_item_id;
    s32 category;
    if (item_id == 0)
        category = -1;
    else
        category = ReadItemProperty(item_id, 3);

    switch (category) {
    case 1: case 2: case 3: case 4:
    case 5: case 6: case 7: case 9:
        PlayGameCue(123);
        break;
    case 8: case 15:
        PlayGameCue(124);
        break;
    case 10: case 11: case 12:
        PlayGameCue(125);
        break;
    case 13: case 14:
        PlayGameCue(138);
        break;
    case 16:
        switch (item_id) {
        case 206: case 207: case 209:
            PlayGameCue(131);
            break;
        case 208: case 211:
            PlayGameCue(132);
            break;
        case 203:
            PlayGameCue(130);
            break;
        default:
            PlayGameCue(129);
            break;
        }
        break;
    case 19:
        break;
    default:
        PlayGameCue(126);
        break;
    }
}
