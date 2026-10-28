#include "interfaces.h"
asm(".global gRoot\n.set gRoot,0x0200f428\n.global gSurfaceA\n.set gSurfaceA,0x030008b0\n.global gSurfaceB\n.set gSurfaceB,0x03000990\n.global gKeys\n.set gKeys,0x03000000\n.global gTextTable\n.set gTextTable,0x085567f0\n.global gMessageMap\n.set gMessageMap,0x08393808\n.global gMessageBytes\n.set gMessageBytes,0x0852a13e\n.global gTextureSource\n.set gTextureSource,0x084c3e60");
asm(".global NSetupRegion\n.thumb_set NSetupRegion,0x0802a4b5");
asm(".global NSetEffect\n.thumb_set NSetEffect,0x08017d19");
asm(".global NInitializeMenu\n.thumb_set NInitializeMenu,0x08057bed");
asm(".global NGetStage\n.thumb_set NGetStage,0x0802b549");
asm(".global NInitializeController\n.thumb_set NInitializeController,0x0802b049");
asm(".global NSetControllerOption\n.thumb_set NSetControllerOption,0x0802b59d");
asm(".global NSetControllerEnabled\n.thumb_set NSetControllerEnabled,0x0802b591");
asm(".global NHasSelectedPoolUnit\n.thumb_set NHasSelectedPoolUnit,0x080ccc1d");
asm(".global NSetControllerMode\n.thumb_set NSetControllerMode,0x0802b53d");
asm(".global NSetControllerText\n.thumb_set NSetControllerText,0x0802b555");
asm(".global NInitializeWindow\n.thumb_set NInitializeWindow,0x08017425");
asm(".global NSetWindowOption\n.thumb_set NSetWindowOption,0x08016c91");
asm(".global NSetRegion\n.thumb_set NSetRegion,0x0802a371");
asm(".global NWindowReady\n.thumb_set NWindowReady,0x08017181");
asm(".global NFillWindow\n.thumb_set NFillWindow,0x0802aca1");
asm(".global NBindWindow\n.thumb_set NBindWindow,0x08016211");
asm(".global NDecodeTexture\n.thumb_set NDecodeTexture,0x08013e9d");
asm(".global NSetTexturePalette\n.thumb_set NSetTexturePalette,0x08013a89");
asm(".global NPrintTexture\n.thumb_set NPrintTexture,0x080161d5");
asm(".global NRefreshList\n.thumb_set NRefreshList,0x08017ad9");
asm(".global NSetWindowVisible\n.thumb_set NSetWindowVisible,0x0802a291");
asm(".global NProcessSelectedPoolUnits\n.thumb_set NProcessSelectedPoolUnits,0x080ccca1");
asm(".global NOpenListWindow\n.thumb_set NOpenListWindow,0x0802a1fd");
asm(".global NBindList\n.thumb_set NBindList,0x0802b369");
asm(".global NGetListCount\n.thumb_set NGetListCount,0x08017b51");
asm(".global NSetListText\n.thumb_set NSetListText,0x08057389");
asm(".global NSetWindowCallback\n.thumb_set NSetWindowCallback,0x08015d59");
asm(".global NSetListRange\n.thumb_set NSetListRange,0x08017af5");
asm(".global NOpenDetail\n.thumb_set NOpenDetail,0x08019ae5");
asm(".global NSuspendMessage\n.thumb_set NSuspendMessage,0x08013391");
asm(".global NBeginDetail\n.thumb_set NBeginDetail,0x08013435");
asm(".global NAdvanceChoice\n.thumb_set NAdvanceChoice,0x08029f7d");
asm(".global NAdvanceWindow\n.thumb_set NAdvanceWindow,0x08016235");
asm(".global NRegisterTask\n.thumb_set NRegisterTask,0x08006add");
asm(".global NDetailReady\n.thumb_set NDetailReady,0x08011861");
asm(".global NCloseMenu\n.thumb_set NCloseMenu,0x0802a535");
asm(".global NClearRegion\n.thumb_set NClearRegion,0x0802a2c1");
asm(".global NResetTasks\n.thumb_set NResetTasks,0x08006b5d");

/* Shared task frame: selected-unit processing and its notification/choice continuation. */
void SceneNestedTask_00054664(void *unused, u8 *state)
{
    u8 tiles[512], palette[512];
    u8 phase = *state;
    switch (phase) {
    case 0: {
        u8 stage;
        void *controller;
        u16 tile;
        NSetupRegion(0,0,240,160);
        NSetEffect(AT(0x14dc),0); NSetEffect(AT(0x14f0),0);
        NSetEffect(AT(0x1778),0); NSetEffect(AT(0x178c),0);
        NInitializeMenu();
        stage=NGetStage(AT(0xcd4));
        controller=AT(0xcd4);
        NInitializeController(controller,stage,4,0,55,(u16)(((s32)(0x0600a800-gSurfaceA.tiles))/32));
        NSetControllerOption(AT(0xcd4),0);
        NSetControllerEnabled(AT(0xcd4),1);
        if ((u8)NHasSelectedPoolUnit()) *state=200; else *state=20;
        break;
    }
    case 200:
        NSetControllerMode(AT(0xcd4),1); NSetControllerText(AT(0xcd4),107); *state=201; break;
    case 201:
        if (NGetStage(AT(0xcd4))!=5) break;
        NInitializeWindow(AT(0x1490),gSurfaceA.data,gSurfaceB.data,6,10,18,6,2048,32,13,3,11);
        NSetWindowOption(AT(0x1490),1); NSetRegion(6,10,18,6); *state=202; break;
    case 202: {
        void *window,*buffer;
        u16 tile;
        if (!NWindowReady(AT(0x1490))) break;
        NFillWindow(gSurfaceB.data+((BYTE(0x14a1)*32+BYTE(0x14a0))*2+2),832,11,4);
        window=AT(0x1490); buffer=AT(0x1504);
        tile=(u16)(((s32)(0x0600c000-gSurfaceA.tiles))/32);
        NBindWindow(window,buffer,tile,2);
        {
        u8 *formatAddress=AT(0x14db);
        u32 zero=0;
        *formatAddress=11;
        NDecodeTexture(tiles,gTextureSource,palette,9,zero,zero);
        NSetTexturePalette((void*)0x0600c000,BYTE(0x14d1)<<2);
        NPrintTexture(AT(0x19c8),(void*)0x0600c000,tiles,BYTE(0x14d1),zero,zero,zero);
        NRefreshList(AT(0x14bc)); BYTE(0x2db0)=zero; *state=203; } break;
    }
    case 203: {
        if (BYTE(0x2db0)<=19) ++BYTE(0x2db0);
        /* A requires the minimum display delay; B bypasses it. */
        if (!((gKeys.pressed&1) && BYTE(0x2db0)>19) && !(gKeys.pressed&2)) break;
        NSetWindowVisible(AT(0x1490),1); NProcessSelectedPoolUnits(); *state=204; break;
    }
    case 204:
        if (!NWindowReady(AT(0x1490))) break;
        *state=20; NSetRegion(0,0,0,0); break;
    case 20:
        if (NGetStage(AT(0xcd4))==5) NSetControllerMode(AT(0xcd4),4);
        else NSetControllerMode(AT(0xcd4),1);
        NSetControllerText(AT(0xcd4),90); *state=21; break;
    case 21:
        if (NGetStage(AT(0xcd4))!=5) break;
        NOpenListWindow(AT(0x1490),0,9,12,9,384,0);
        NBindList(AT(0x1490),AT(0xb54),3,0); *state=22; break;
    case 22: {
        void *window,*buffer;
        u16 tile;
        u8 index;
        if (!NWindowReady(AT(0x1490))) break;
        window=AT(0x1490); buffer=AT(0x1504);
        tile=(u16)(((s32)(0x0600c000-gSurfaceA.tiles))/32);
        NBindWindow(window,buffer,tile,3);
        for (index=0;index<NGetListCount(AT(0x14bc));index=(u8)(index+1))
            NSetListText(gTextTable[24+index],AT(0x14bc),index,0);
        NRefreshList(AT(0x14bc)); NSetWindowCallback(AT(0x1490),(void*)0x08017e81,0);
        NSetEffect(AT(0x14dc),3); NSetListRange(AT(0x14bc),0,11);
        {
            u8 *root=gRoot;
            *(u16*)(root+0x2cec)=2;
            *(void**)(root+0x2ce4)=(void*)0x0805463d;
            *(void**)(root+0x2ce8)=root+0x2d08;
            *(void**)(root+0x2d08)=state;
            *(u32*)(root+0x2d0c)=40;
            *(u32*)(root+0x2d10)=44;
            *(u16*)(root+0x2cf8)=1;
            *(void**)(root+0x2cf0)=(void*)0x08054da9;
            *(void**)(root+0x2cf4)=state;
            NSetEffect(root+0x14dc,3);
        } *state=23; break;
    }
    case 23:
        if (gKeys.pressed&4) {
            const u8 *messages=gMessageBytes;
            const u16 *map=gMessageMap;
            struct DetailEffect { u8 prefix[17]; u8 row; };
            struct DetailEffect *effect=(struct DetailEffect*)AT(0x14dc);
            NOpenDetail(gRoot,messages[map[effect->row]*2],&gSurfaceA,&gSurfaceB,2);
            NSuspendMessage(gRoot); NBeginDetail(); *state=60; BYTE(0x1475)=phase;
        } else {
            NAdvanceChoice(AT(0x1490),128,0,0,AT(0x2ce4),2); NAdvanceWindow(AT(0x1490));
        }
        break;
    case 40: NSetWindowVisible(AT(0x1490),0); *state=41; break;
    case 41: if (NWindowReady(AT(0x1490))) *state=BYTE(0x2d38); break;
    case 42: NRegisterTask(AT(0x1478),0,(void*)0x08054e15); break;
    case 43: NRegisterTask(AT(0x1478),0,(void*)0x08055f11); break;
    case 44: NSetControllerMode(AT(0xcd4),4); NSetControllerText(AT(0xcd4),102); *state=45; break;
    case 45: if (!NGetStage(AT(0xcd4))) *state=255; break;
    case 60: if (NDetailReady()) { NSuspendMessage(AT(0xcd4)); *state=BYTE(0x1475); } break;
    case 255:
        NCloseMenu(); NClearRegion(0,0,0,0); NSetRegion(0,0,0,0);
        NResetTasks(AT(0x1478)); BYTE(0x1474)=254; break;
    }
}
