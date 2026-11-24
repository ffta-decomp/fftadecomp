typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef signed short s16; typedef signed int s32;
typedef void (*Callback)(void*,u16*,void*);
typedef struct Work {u16 countdown;u8 target_index,target_count,mode,unknown5;s16 x,y;u16 unknown10;void *first,*second;u32 unknown20;void *cell;u8 outputA[8];void *spriteA;u8 outputB[4];void *spriteB;u32 unknown48;void *initial,*record,*handles[4],*sequence;} Work;
void RetailCall_0801e6f0(u16*,u16*);
void *RetailCall_080e03f8(void*,const void*,u8,u8,const s16*,void*);
u32 RetailCall_080dd494(void*);
void *RetailCall_080dd4b4(void*,u8);
void RetailCall_080de268(void*);
void RetailCall_0814186c(const void*,void*,u32);
void RetailCall_080d38b4(void);
void *RetailCall_080e05dc(void*);
void *RetailCall_080dfd8c(const void*,u8,u16,u16,void*);
/* Site view: original signed H8 arrives sign-extended in R1; the native
 * callee stores only LOW16 R1. Its existing implementation is unchanged. */
void *RetailCall_080d6098(s32,s16,s32,u8,u32,void*,const void*,void*);
void *RetailCall_08005b6c(Callback,u16,const u32*,void*);
void *RetailCall_080d6134(void*);
void *RetailCall_080e051c(void*);
void *RetailCall_080dd4a4(void*,u8);
void *RetailCall_080dd4c4(const void*);
u32 RetailCall_080db838(const void*);
u32 RetailCall_080d8b4c(void);
u8 RetailCall_080dbab8(void**,u32);
void *RetailCall_080dcfe4(void*,const void*,u8,u16,u16,void*,u16);
u32 RetailCall_080dd580(const void*);

s32 OriginalActionCallback_0011802C(void *parent, u16 *event_input, Work *work_input)
{
    /* Retail's independently addressed subobjects occupy SP16..SP83.
     * Keep both distinct 28-byte templates, all four scalar OUT/fill values,
     * and the final packed coordinate word; no padding or invented zeroing. */
    struct LocalStorage {
        u16 coordinate_x, coordinate_y;
        u16 palette_fill, palette_clear;
        u32 first_event[7], second_event[7];
        u32 packed_coordinates;
    } local;
    /* Actual incoming R1 state base is retained in R6 across state calls.
     * Other incoming values remain ordinary C inputs, not fixed homes. */
    register u16 *event asm("r6") = event_input;
    register Work *incoming_work asm("r2") = work_input;
    /* Consume the actual state capture before capturing the still-incoming
     * work value. Both operands are initialized, and no instruction is emitted. */
    asm("" : "+r"(incoming_work) : "r"(event));
    {
        Work *work = incoming_work;
        s32 phase = event[0];
        switch (phase) {
        case 0: {
            u8 mode;
            u8 index;
            u32 returned_count, count_test;
            u16 input_mode = event[11];
            work->mode = input_mode;
            work->record = ((void **)event)[1];
            mode = 8;
            if ((u8)input_mode != 0)
                mode = 0;
            {
                /* Actual OUT address survives the projector and feeds the later Y
                 * load. The initialized input annotation emits no instruction. */
                register u16 *coordinate_y_address asm("r4") = &local.coordinate_y;
                u32 loaded_x, shifted_y;
                RetailCall_0801e6f0(&local.coordinate_x, coordinate_y_address);
                loaded_x = local.coordinate_x;
                {
                    /* Actual literal operand is defined before the old packed load. */
                    register u32 preserve_high asm("r1") = 0xffff0000;
                    asm("" : : "r"(preserve_high));
                    local.packed_coordinates = (local.packed_coordinates & preserve_high) | loaded_x;
                }
                asm("" : : "r"(coordinate_y_address));
                shifted_y = (u32)(*coordinate_y_address - 32) << 16;
                local.packed_coordinates = (local.packed_coordinates & 0x0000ffff) | shifted_y;
            }
            work->initial = RetailCall_080e03f8(work->record,
                (const void *)0x083a5144, mode, 6,
                (const s16 *)&local.packed_coordinates, parent);
            returned_count = RetailCall_080dd494(work->record);
            work->target_count = returned_count;
            count_test = returned_count << 24;
            /* Original LOW8 predicate is defined before loop/source initialization. */
            asm("" : : "r"(count_test));
            index = 0;
            {
                /* Independent original source addresses survive the target loop. */
                u16 *palette_fill_address = &local.palette_fill;
                u16 *palette_clear_address = &local.palette_clear;
                asm("" : "+r"(palette_fill_address), "+r"(palette_clear_address));
                if (count_test != 0) {
                    do {
                        RetailCall_080de268(RetailCall_080dd4b4(work->record,index));
                        index++;
                    } while (index < work->target_count);
                }
                *palette_fill_address = 0x056e;
                {
                    u16 *palette_destination = (u16 *)0x03003920;
                    asm("" : "+r"(palette_destination));
                    RetailCall_0814186c(palette_fill_address,palette_destination,0x01000010);
                    *palette_clear_address = 0;
                    palette_destination += 16;
                    RetailCall_0814186c(palette_clear_address,palette_destination,0x01000010);
                }
            }
            break;
        }
        case 1:
            RetailCall_080d38b4();
            break;
        case 256:
            work->initial = RetailCall_080e05dc(work->initial);
            if (work->initial != 0)
                break;
            work->sequence = RetailCall_080dfd8c((const void *)0x083a6000,3,4,0,parent);
            work->x = 120;
            work->y = 80;
            work->spriteA = RetailCall_080d6098(120,80,0,1,2,
                work->outputA,(const void *)0x083a51a4,parent);
            work->countdown = 66;
            event[0]++;
            break;
        case 257:
            if (--work->countdown != 0)
                break;
            work->first = RetailCall_08005b6c((Callback)0x081179b5,48,local.first_event,parent);
            work->spriteB = RetailCall_080d6098(work->x,work->y,0,1,1,
                work->outputB,(const void *)0x083a51d4,parent);
            event[0]++;
            break;
        case 258:
            work->spriteA = RetailCall_080d6134(work->spriteA);
            if (work->spriteA != 0)
                break;
            work->spriteB = RetailCall_080d6134(work->spriteB);
            if (work->spriteB != 0)
                break;
            work->first = RetailCall_080e051c(work->first);
            if (work->first != 0)
                break;
            event[0]++;
            break;
        case 259:
            work->sequence = RetailCall_080dfd8c((const void *)0x083a6018,2,4,0,parent);
            work->second = RetailCall_08005b6c((Callback)0x08117b9d,372,local.second_event,parent);
            event[0]++;
            break;
        case 260:
            work->second = RetailCall_080e051c(work->second);
            if (work->second != 0)
                break;
            work->countdown = 1;
            event[0]++;
            break;
        case 261:
            if (--work->countdown != 0)
                break;
            work->cell = RetailCall_080dd4a4(work->record,work->target_index);
            RetailCall_080db838(RetailCall_080dd4c4(work->cell));
            event[0]++;
            /* Original same-call fall-through. */
        case 262: {
            u32 variant;
            u32 index;
            void *child;
            if ((u8)RetailCall_080d8b4c() != 0)
                break;
            RetailCall_080dbab8(work->handles,4);
            index = work->target_index;
            {
                /* Same initialized ONE survives to both original parity sites. */
                u32 one = 1;
                asm("" : "+r"(one));
                {
                    /* The original destructive AND consumes this real mask copy. */
                    register u32 parity asm("r0") = one;
                    asm("" : "+r"(parity));
                    parity &= index;
                    variant = parity ? 4 : 2;
                }
                child = RetailCall_080dcfe4(work->cell,(const void *)0x083a5fec,
                    12-({
                        /* Preserve the actual destructive mask working value. */
                        register u32 lane_mask asm("r3") = 6;
                        asm("" : "+r"(lane_mask));
                        lane_mask &= index;
                        lane_mask;
                    }),10,variant,parent,10);
                work->handles[work->target_index & 3] = child;
                if ((u8)RetailCall_080dd580(work->cell) != 0) {
                    u32 fresh_index = work->target_index;
                    register u32 parity asm("r0") = one;
                    u32 flags;
                    asm("" : "+r"(parity));
                    parity &= fresh_index;
                    flags = parity ? 16 : 8;
                    work->sequence = RetailCall_080dfd8c((const void *)0x083a6028,
                        1,flags|4,10,parent);
                }
                {
                    u32 next_index = work->target_index + 1;
                    /* Publish the native byte before its separately narrowed test. */
                    work->target_index = next_index;
                    if ((u8)next_index == work->target_count)
                        event[0]++;
                    else {
                        u32 restart_delay = 40;
                        work->countdown = restart_delay;
                        /* The original reuses this just-stored fullword to form state. */
                        asm("" : "+r"(restart_delay));
                        event[0] = restart_delay + 221;
                    }
                }
            }
            break;
        }
        case 263:
            if ((u8)RetailCall_080dbab8(work->handles,4) != 0)
                event[0] = 2;
            break;
        }
        return 0;
    }
}
asm(".global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x08005b6d\n");
asm(".global RetailCall_0801e6f0\n.thumb_set RetailCall_0801e6f0,0x0801e6f1\n");
asm(".global RetailCall_080d38b4\n.thumb_set RetailCall_080d38b4,0x080d38b5\n");
asm(".global RetailCall_080d6098\n.thumb_set RetailCall_080d6098,0x080d6099\n");
asm(".global RetailCall_080d6134\n.thumb_set RetailCall_080d6134,0x080d6135\n");
asm(".global RetailCall_080d8b4c\n.thumb_set RetailCall_080d8b4c,0x080d8b4d\n");
asm(".global RetailCall_080db838\n.thumb_set RetailCall_080db838,0x080db839\n");
asm(".global RetailCall_080dbab8\n.thumb_set RetailCall_080dbab8,0x080dbab9\n");
asm(".global RetailCall_080dcfe4\n.thumb_set RetailCall_080dcfe4,0x080dcfe5\n");
asm(".global RetailCall_080dd494\n.thumb_set RetailCall_080dd494,0x080dd495\n");
asm(".global RetailCall_080dd4a4\n.thumb_set RetailCall_080dd4a4,0x080dd4a5\n");
asm(".global RetailCall_080dd4b4\n.thumb_set RetailCall_080dd4b4,0x080dd4b5\n");
asm(".global RetailCall_080dd4c4\n.thumb_set RetailCall_080dd4c4,0x080dd4c5\n");
asm(".global RetailCall_080dd580\n.thumb_set RetailCall_080dd580,0x080dd581\n");
asm(".global RetailCall_080de268\n.thumb_set RetailCall_080de268,0x080de269\n");
asm(".global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c,0x080dfd8d\n");
asm(".global RetailCall_080e03f8\n.thumb_set RetailCall_080e03f8,0x080e03f9\n");
asm(".global RetailCall_080e051c\n.thumb_set RetailCall_080e051c,0x080e051d\n");
asm(".global RetailCall_080e05dc\n.thumb_set RetailCall_080e05dc,0x080e05dd\n");
asm(".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n");
