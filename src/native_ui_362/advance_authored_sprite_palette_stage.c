typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,unknown2;void **sprite_cell;u32 unknown8[5];} Event;
typedef struct Work {u16 timer;u8 unknown2[6];void **sprite_cell;void *first_sprite,*first_palette,*second_palette,*stage;} Work;
void *RetailCall_080d5cc0(const void*,u16,u16,u16,u16,u8,u8,u8);
void *RetailCall_080dfd8c(const void*,u8,u16,u16,void*);
void *RetailCall_08011484(void*);
void *RetailCall_080d4704(const void*,void*);
void *RetailCall_080d4724(const void*,void*,u16);
void *RetailCall_080d4774(void*);
s32 RemainingBand43_00112F80(void*,Event*,Work*);

/* Authored stage: original wrap countdowns and stored child polls. */
s32 RemainingBand43_00112F80(void *parent,Event *event,Work *work)
{
    switch((s32)event->phase) {
    case 0:
        work->sprite_cell=event->sprite_cell;
        work->timer=10;
        break;
    case 1: break;
    case 256: {
        u32 remaining=work->timer-1;
        work->timer=remaining;
        if((u16)remaining!=0) break;
        work->first_sprite=RetailCall_080d5cc0((const void*)0x08505d4c,1,120,112,658,8,1,0);
        work->stage=RetailCall_080dfd8c((const void*)0x083a37a8,3,4,0,parent);
        event->phase++;
        break;
    }
    case 257:
        work->first_sprite=RetailCall_08011484(work->first_sprite);
        if(work->first_sprite!=0) break;
        work->timer=10;
        event->phase++;
        break;
    case 258: {
        u32 remaining=work->timer-1;
        work->timer=remaining;
        if((u16)remaining!=0) break;
        *work->sprite_cell=RetailCall_080d5cc0((const void*)0x085055d0,0,120,112,664,6,1,0);
        work->first_palette=RetailCall_080d4704((const void*)0x0894bd68,parent);
        work->second_palette=RetailCall_080d4724((const void*)0x08949f18,parent,70);
        event->phase++;
        break;
    }
    case 259:
        work->first_palette=RetailCall_080d4774(work->first_palette);
        if(work->first_palette!=0) break;
        work->second_palette=RetailCall_080d4774(work->second_palette);
        if(work->second_palette!=0) break;
        event->phase++;
        break;
    case 260:
        event->phase=2;
        break;
    }
    return 0;
}
asm(".global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0,0x080d5cc1\n");
asm(".global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c,0x080dfd8d\n");
asm(".global RetailCall_08011484\n.thumb_set RetailCall_08011484,0x08011485\n");
asm(".global RetailCall_080d4704\n.thumb_set RetailCall_080d4704,0x080d4705\n");
asm(".global RetailCall_080d4724\n.thumb_set RetailCall_080d4724,0x080d4725\n");
asm(".global RetailCall_080d4774\n.thumb_set RetailCall_080d4774,0x080d4775\n");
