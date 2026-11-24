/* Original opcode52 unit/status filter and explicit selection-lane transaction. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Unit {u8 gap[40];u16 flags;u8 tail[222];};
struct Record {struct Unit *unit;};
struct Game {u8 gap[0x80];struct Unit units[24];u8 gap2[0x2178-0x80-24*264];u8 selections[3];u8 gap3[0x2fc4-0x217b];struct Unit secondary[12];u8 gap4[0x3ca6-0x2fc4-12*264];u16 selected;};
extern struct Game gGame;
extern void * GetContentContext(void);
extern struct Unit * FindUnit(int);
extern struct Record * FindRecord(void *,struct Unit *);
extern int CollectRecords(void *,struct Record **);
extern int Check8240(struct Unit *);
extern int Check8260(struct Unit *);
extern int Check8298(struct Unit *);
extern int ReadProperty(struct Unit *,int);
extern struct Unit * ResolveSceneUnit(u8);

asm(".global gGame\n.set gGame,0x02000000\n.global GetContentContext\n.thumb_set GetContentContext,0x8096d7d\n.global FindUnit\n.thumb_set FindUnit,0x8125579\n.global FindRecord\n.thumb_set FindRecord,0x8099561\n.global CollectRecords\n.thumb_set CollectRecords,0x8099cdd\n.global Check8240\n.thumb_set Check8240,0x80c8241\n.global Check8260\n.thumb_set Check8260,0x80c8261\n.global Check8298\n.thumb_set Check8298,0x80c8299\n.global ReadProperty\n.thumb_set ReadProperty,0x80c7ea5\n.global ResolveSceneUnit\n.thumb_set ResolveSceneUnit,0x8121cb5\n");
unsigned int Scene51_0012260C(void *unused,u8 *command)
{
    struct Record *records[13];
    struct Unit *selected;
    struct Unit *unit;
    struct Record *record;
    struct Record **cursor;
    void *context;
    int index = 0;
    int count;
    u8 value;
    if (command[1] > 253) {
        context = GetContentContext();
        if (FindRecord(context,FindUnit(2))) {
            unit = gGame.units;
            goto mark;
        }
        count = CollectRecords(GetContentContext(),records);
        selected = 0;
        if (index < count) {
        cursor = records;
        __asm__ volatile("" : "+r"(cursor));
        for (; index < count; ++cursor,++index) {
            record = *cursor;
            if ((u8)Check8240(record->unit)) continue;
            if ((u8)Check8260(record->unit)) continue;
            if ((u8)Check8298(record->unit)) continue;
            if (command[1] == 254) {
                value = ReadProperty(record->unit,1);
                if (value == 94) continue;
                if (value == 10) continue;
                if (value == 9) continue;
                if (value == 4) continue;
                if (value == 12) continue;
            }
            selected = record->unit;
            break;
        }
        }
primary_setup:
        unit = gGame.units;
        index = 0;
        goto primary_test;
primary_next:
        {
        register unsigned int byte_step __asm__("r0");
        ++index;
        byte_step = sizeof(struct Unit);
        __asm__("" : "+r"(byte_step));
        unit = (struct Unit *)((u8 *)unit + byte_step);
        }
        if (index > 23) goto complete;
primary_test:
        if (unit != selected) goto primary_next;
mark:
        unit->flags |= 0x400;
        goto complete;
    } else {
        selected = ResolveSceneUnit(command[1]);
        {
        u8 *selection0, *selection1, *selection2;
        register u8 *game_base __asm__("r9");
        u16 *selected_field;
        unit = gGame.secondary;
        selection0 = (u8 *)((unsigned int)unit - 0xE4C);
        selection1 = (u8 *)((unsigned int)unit - 0xE4B);
        selection2 = (u8 *)((unsigned int)unit - 0xE4A);
        game_base = (u8 *)((unsigned int)unit - 0x2FC4);
        __asm__("" : "+r"(game_base));
        selected_field = (u16 *)((unsigned int)unit + 0xCE2);
        for (; index <= 11; index++,unit++) {
            if (unit == selected) {
                switch (command[2]) {
                case 0: *selection0 = index+1; break;
                case 1: *selection1 = index+1; break;
                case 2: *selection2 = index+1; break;
                }
                if (command[2] == 0) *selected_field = game_base[0x2178];
                break;
            }
        }
    }
}
complete:
    return 272;
}
