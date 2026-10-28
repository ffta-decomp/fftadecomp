typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern void C2B590(void *,u32);
asm(".global C2B590\n.thumb_set C2B590,0x0802b591");
extern void C17D18(void *,u8);
asm(".global C17D18\n.thumb_set C17D18,0x08017d19");
extern void C5C520(void);
asm(".global C5C520\n.thumb_set C5C520,0x0805c521");
extern void C2A4B4(u32,u32,u32,u32);
asm(".global C2A4B4\n.thumb_set C2A4B4,0x0802a4b5");
extern void C2B59C(void *,u32);
asm(".global C2B59C\n.thumb_set C2B59C,0x0802b59d");
extern u32 C2B548(void *);
asm(".global C2B548\n.thumb_set C2B548,0x0802b549");
extern void C2B048(void *,u32,u32,u32,u32,u32);
asm(".global C2B048\n.thumb_set C2B048,0x0802b049");
extern void C2B53C(void *,u32);
asm(".global C2B53C\n.thumb_set C2B53C,0x0802b53d");
extern u32 CCCBC4(void);
asm(".global CCCBC4\n.thumb_set CCCBC4,0x080ccbc5");
extern u32 CC9540(u32);
asm(".global CC9540\n.thumb_set CC9540,0x080c9541");
extern void CC9574(u32,u32);
asm(".global CC9574\n.thumb_set CC9574,0x080c9575");
extern void C2B554(void *,u32);
asm(".global C2B554\n.thumb_set C2B554,0x0802b555");
extern u32 CCCB94(void);
asm(".global CCCB94\n.thumb_set CCCB94,0x080ccb95");
extern void C2B56C(void *,u32);
asm(".global C2B56C\n.thumb_set C2B56C,0x0802b56d");
extern void C2A1FC(void *,u32,u32,u32,u32,u32,u32);
asm(".global C2A1FC\n.thumb_set C2A1FC,0x0802a1fd");
extern void C2B368(void *,void *,u32,u32);
asm(".global C2B368\n.thumb_set C2B368,0x0802b369");
extern u32 C17180(void *);
asm(".global C17180\n.thumb_set C17180,0x08017181");
extern void C16210(void *,void *,u16,u16);
asm(".global C16210\n.thumb_set C16210,0x08016211");
extern void C5C3D4(const u8 *,void *,s32,u32);
asm(".global C5C3D4\n.thumb_set C5C3D4,0x0805c3d5");
extern u32 C17B50(void *);
asm(".global C17B50\n.thumb_set C17B50,0x08017b51");
extern void C17AD8(void *);
asm(".global C17AD8\n.thumb_set C17AD8,0x08017ad9");
extern void C15D58(void *,u32,u32);
asm(".global C15D58\n.thumb_set C15D58,0x08015d59");
extern void C17AF4(void *,u32,u32);
asm(".global C17AF4\n.thumb_set C17AF4,0x08017af5");
extern void C19AE4(void *,u32,void *,void *,u32);
asm(".global C19AE4\n.thumb_set C19AE4,0x08019ae5");
extern void *C13390(void *);
asm(".global C13390\n.thumb_set C13390,0x08013391");
extern u32 C13434(void);
asm(".global C13434\n.thumb_set C13434,0x08013435");
extern void C29F7C(void *,u32,u32,u32,void *,u32);
asm(".global C29F7C\n.thumb_set C29F7C,0x08029f7d");
extern void C16234(void *);
asm(".global C16234\n.thumb_set C16234,0x08016235");
extern void C2A290(void *,u32);
asm(".global C2A290\n.thumb_set C2A290,0x0802a291");
extern u32 C11860(void);
asm(".global C11860\n.thumb_set C11860,0x08011861");
extern void C6ADC(void *,u32,u32);
asm(".global C6ADC\n.thumb_set C6ADC,0x08006add");
extern void C2A534(void);
asm(".global C2A534\n.thumb_set C2A534,0x0802a535");
extern void C6B8C(void *,u8);
asm(".global C6B8C\n.thumb_set C6B8C,0x08006b8d");

struct FontWorkspace { u8 unknown00[16]; u32 tile_base; };
struct KeyRecord { u16 held, pressed; };
extern struct FontWorkspace gFontWorkspace;
extern struct KeyRecord gKeyRecord;
extern const u8 *gSceneNames[];
asm(".global gFontWorkspace\n.set gFontWorkspace,0x030008b0\n.global gKeyRecord\n.set gKeyRecord,0x03000000\n.global gSceneNames\n.set gSceneNames,0x085567f0");

struct SelectionRecordAt17 { u8 unknown00[17]; u8 selection; };
struct ScenePublicationView {
    u8 unknown0000[0x2c4c];
    u32 callback0;
    u8 **state_cell_pointer;
    u16 kind, unknown56;
    u32 callback1;
    u8 *task_state;
    u16 mode;
    u8 unknown62[14];
    u8 *state_cell;
    u32 range, sentinel;
};
typedef char PublicationStateCellOffset[(u32)&((struct ScenePublicationView *)0)->state_cell==0x2c70?1:-1];
typedef char SelectionAt17[(u32)&((struct SelectionRecordAt17 *)0)->selection==17?1:-1];

extern const u16 gChoiceCommands[];
extern const u16 gChoiceOrder[];
asm(".global gChoiceCommands\n.set gChoiceCommands,0x0852a13e\n.global gChoiceOrder\n.set gChoiceOrder,0x08393828");

#define ROOT (*(u8 **)0x0200f428)
#define B(p,o) (*(u8 *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
#define W(p,o) (*(u32 *)((p)+(o)))
#define FONTBASE (gFontWorkspace.tile_base)

void SceneNestedTask_00058D40(u8 task, u8 *state)
{
    switch (*state) {
    case 0: {
        u8 status;
        C2B590(ROOT+0x1414,1);
        C17D18(ROOT+0xd40,0);
        C17D18(ROOT+0xd54,0);
        C17D18(ROOT+0xf3c,0);
        C17D18(ROOT+0xf50,0);
        C5C520();
        C2A4B4(0,0,240,160);
        C2B59C(ROOT+0x1414,0);
        status=(u8)C2B548(ROOT+0x1414);
        C2B048(ROOT+0x1414,status,4,0,54,
                (u16)((s32)(0x0600a800-FONTBASE)/32));
        C2B53C(ROOT+0x1414,1);
        CCCBC4();
        if ((u8)CC9540(0x30a)==1 && (u8)CCCBC4()>4 &&
                !(u8)CC9540(0x5a0)) {
            CC9574(0x5a0,1);
            C2B554(ROOT+0x1414,163);
            *state=5;
            break;
        }
        if ((u8)CCCB94())
            C2B554(ROOT+0x1414,144);
        else
            C2B554(ROOT+0x1414,143);
        *state=2;
        break;
    }
    case 1:
        if (!(u8)C2B548(ROOT+0x1414)) {
            C2B56C(ROOT+0x1414,54);
            C2B53C(ROOT+0x1414,1);
        } else {
            C2B53C(ROOT+0x1414,4);
        }
        C2B59C(ROOT+0x1414,0);
        C2B554(ROOT+0x1414,145);
        *state=2;
        break;
    case 2: {
        u8 *base;
        if ((u8)C2B548(ROOT+0x1414)!=5) break;
        C2A1FC(ROOT+0xcf4,0,9,12,7,384,0);
        base=ROOT;
        C2B368(base+0xcf4,base+0xb54,3,0);
        *state=3;
        break;
    }
    case 3: {
        u8 *setup_base;
        struct ScenePublicationView *publish_base;
        u16 row;
        if (!(u8)C17180(ROOT+0xcf4)) break;
        setup_base=ROOT;
        C16210(setup_base+0xcf4,setup_base+0xd68,
                (u16)((s32)(0x0600c000-FONTBASE)/32),2);
        row=0;
        while (row<(u16)C17B50(ROOT+0xd20)) {
            C5C3D4(gSceneNames[row+36],
                    ROOT+0xd20,(s16)row,0);
            row++;
        }
        C17AD8(ROOT+0xd20);
        C15D58(ROOT+0xcf4,0x08017e81,0);
        C17D18(ROOT+0xd40,3);
        C17AF4(ROOT+0xd20,0,11);
        publish_base=(struct ScenePublicationView *)ROOT;
        publish_base->kind=2;
        publish_base->callback0=0x080592d1;
        publish_base->state_cell_pointer=&publish_base->state_cell;
        publish_base->state_cell=state;
        publish_base->range=40;
        publish_base->sentinel=255;
        publish_base->mode=1;
        publish_base->callback1=0x080592f9;
        publish_base->task_state=state;
        *state=4;
        break;
    }
    case 4: {
        if (gKeyRecord.pressed & 4) {
            u8 *base=ROOT;
            const u16 *commands=gChoiceCommands;
            const u16 *order=gChoiceOrder;
            const struct SelectionRecordAt17 *selection=(const struct SelectionRecordAt17 *)(base+0xd40);
            u16 selected=order[selection->selection];
            C19AE4(base,commands[selected],
                    (void *)0x030008b0,(void *)0x03000990,2);
            C13390(ROOT);
            C13434();
            *state=60;
            B(ROOT,0xcd5)=4;
        } else {
            u8 *idle_base=ROOT;
            C29F7C(idle_base+0xcf4,128,0,0,idle_base+0x2c4c,2);
            C16234(ROOT+0xcf4);
        }
        break;
    }
    case 5:
        if (!(u8)C2B548(ROOT+0x1414)) *state=255;
        break;
    case 20:
        C2A290(ROOT+0xcf4,0);
        *state=21;
        break;
    case 21:
        if ((u8)C17180(ROOT+0xcf4)) *state=254;
        break;
    case 40:
        C2A290(ROOT+0xcf4,0);
        *state=41;
        break;
    case 41:
        if ((u8)C17180(ROOT+0xcf4)) {
            C2B53C(ROOT+0x1414,4);
            C2B554(ROOT+0x1414,151);
            *state=42;
        }
        break;
    case 42:
        if (!(u8)C2B548(ROOT+0x1414)) *state=255;
        break;
    case 60:
        if ((u16)C11860()) {
            C13390(ROOT+0x1414);
            *state=B(ROOT,0xcd5);
        }
        break;
    case 254:
        C6ADC(ROOT+0xcd8,0,0x08059455);
        break;
    case 255:
        C2A534();
        C6B8C(ROOT+0xcd8,task);
        B(ROOT,0xcd4)=254;
        break;
    }
}
