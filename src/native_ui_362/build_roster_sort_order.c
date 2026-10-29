typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
#define ACTIVE_ROSTER_START() ({ register u8 *record_base __asm__("r0") = RosterStorage; __asm__("" : "+r"(record_base)); record_base+132; })
struct RosterSortPair { s32 key; s32 slot; };
typedef char PairIsEightBytes[(sizeof(struct RosterSortPair)==8)?1:-1];
extern u8 RosterStorage[];
extern u8 *RosterDisplay;
extern void CompactRosterSlots(void);
extern void SortRosterPairs(struct RosterSortPair *,s32,s32,u32);
__asm__(".global RosterStorage\n.set RosterStorage,0x02000000\n"
        ".global RosterDisplay\n.set RosterDisplay,0x03002818\n"
        ".global CompactRosterSlots\n.thumb_set CompactRosterSlots,0x080891bd\n"
        ".global SortRosterPairs\n.thumb_set SortRosterPairs,0x08087d99");
/* Each arm has its actual key projection and fresh count reload after sorting. */
#define KEYED_ORDER(KEY,CREG,IREG,PREG) \
    do { \
        register u32 count __asm__(CREG) = 0; \
        register s32 slot __asm__("r3") = 0; \
        register u8 **root_value __asm__("r6") = &RosterDisplay; \
        register u8 **sort_root __asm__("r9"); \
        register u8 *active __asm__("r4"); \
        register u32 stride __asm__("r5"); \
        register u8 **first_count_slot __asm__(IREG); \
        register u8 **post_count_slot __asm__(PREG); \
        register u8 **copy_root __asm__("r5"); \
        register u8 *count_address __asm__("r0"); \
        register u32 count_field __asm__("r4"); \
        u32 read_count; \
        __asm__("" : "+r"(count), "+r"(slot), "+r"(root_value)); \
        sort_root = root_value; \
        __asm__("" : "+r"(sort_root)); \
        active = ACTIVE_ROSTER_START(); \
        __asm__("" : "+r"(active)); \
        stride = 264; \
        __asm__("" : "+r"(stride)); \
        do { \
            if (*active != 0) { \
                register u32 old_count __asm__(IREG) = count; \
                register u32 key_index __asm__("r0"); \
                register u8 *key_base __asm__("r6"); \
                register u8 *key_address __asm__(CREG); \
                register u32 key_value __asm__("r0"); \
                register u32 incremented __asm__("r0"); \
                register u32 payload_index __asm__(IREG); \
                register u8 *payload_address __asm__("r0"); \
                __asm__("" : "+r"(old_count)); \
                key_index = old_count<<3; \
                __asm__("" : "+r"(key_index)); \
                key_base = (u8 *)pairs; \
                __asm__("" : "+r"(key_base)); \
                key_address = key_base+key_index; \
                __asm__("" : "+r"(key_address)); \
                key_value = (KEY); \
                __asm__("" : "+r"(key_value)); \
                *(s32 *)key_address = key_value; \
                incremented = old_count+1; \
                __asm__("" : "+r"(incremented)); \
                incremented <<= 24; \
                __asm__("" : "+r"(incremented)); \
                count = incremented>>24; \
                payload_index = old_count<<3; \
                __asm__("" : "+r"(payload_index)); \
                payload_address = (u8 *)pairs+4; \
                __asm__("" : "+r"(payload_address)); \
                payload_address += payload_index; \
                __asm__("" : "+r"(payload_address)); \
                *(s32 *)payload_address = slot; \
            } \
            active += stride; \
            slot++; \
        } while (slot <= 23); \
        first_count_slot = sort_root; \
        __asm__("" : "+r"(first_count_slot)); \
        count_address = *first_count_slot; \
        __asm__("" : "+r"(count_address)); \
        count_field = 0x95C; \
        __asm__("" : "+r"(count_field)); \
        count_address += count_field; \
        __asm__("" : "+r"(count_address)); \
        *count_address = (u8)count; \
        SortRosterPairs(pairs,0,(s32)count-1,direction); \
        slot = 0; \
        post_count_slot = sort_root; \
        __asm__("" : "+r"(post_count_slot)); \
        count_address = *post_count_slot; \
        __asm__("" : "+r"(count_address)); \
        count_address += count_field; \
        __asm__("" : "+r"(count_address)); \
        read_count = *count_address; \
        __asm__("" : "+r"(read_count)); \
        if (slot < (s32)read_count) { \
            u32 payload_address; \
            copy_root = sort_root; \
            __asm__("" : "+r"(copy_root)); \
            payload_address = (u32)pairs+4; \
            do { \
                output[slot] = (u8)*(s32 *)payload_address; \
                payload_address += 8; \
                slot++; \
            } while (slot < (s32)(*copy_root)[count_field]); \
        } \
    } while (0)
void BuildRosterSortOrder(u32 mode,u8 *output) __asm__("Region27_00072130");
void BuildRosterSortOrder(u32 mode,u8 *output)
{
    struct RosterSortPair pairs[24];
    register u32 mode_byte __asm__("r9");
    register u32 direction __asm__("r8");
    u32 projected_mode = mode<<24;
    u32 clear_address;
    u8 *active;
    u32 row_offset;
    s32 remaining;
    u32 rank;
    mode_byte = projected_mode>>24;
    __asm__("" : "+r"(mode_byte));
    direction = projected_mode>>31;
    __asm__("" : "+r"(direction));
    {
        register u32 one __asm__("r0") = 1;
        register u32 working_direction __asm__("r2");
        __asm__("" : "+r"(one));
        working_direction = direction;
        __asm__("" : "+r"(working_direction));
        working_direction ^= one;
        __asm__("" : "+r"(working_direction));
        direction = working_direction;
        __asm__("" : "+r"(direction));
    }
    CompactRosterSlots();
    {
        register u32 clear_byte __asm__("r1") = 255;
        register u32 clear_address __asm__("r0");
        __asm__("" : "+r"(clear_byte));
        clear_address = (u32)output;
        __asm__("" : "+r"(clear_address));
        clear_address += 23;
        __asm__("" : "+r"(clear_address));
        do {
            *(u8 *)clear_address = (u8)clear_byte;
            clear_address--;
        } while ((s32)clear_address >= (s32)output);
    }
    {
        register u32 row_rank __asm__("r4") = 1;
        register u8 *roster_base __asm__("r0");
        register u32 row_offset __asm__("r2");
        register u8 *active_record __asm__("r1");
        register u8 **slot_value __asm__("r6");
        register u8 **display_slot __asm__("r12");
        register u32 record_stride __asm__("r5");
        register s32 countdown __asm__("r3");
        __asm__("" : "+r"(row_rank));
        roster_base = RosterStorage;
        __asm__("" : "+r"(roster_base));
        row_offset = 0;
        __asm__("" : "+r"(row_offset));
        active_record = roster_base;
        __asm__("" : "+r"(active_record));
        active_record += 132;
        __asm__("" : "+r"(active_record));
        slot_value = &RosterDisplay;
        __asm__("" : "+r"(slot_value));
        display_slot = slot_value;
        __asm__("" : "+r"(display_slot));
        record_stride = 264;
        __asm__("" : "+r"(record_stride));
        countdown = 23;
        __asm__("" : "+r"(countdown));
        do {
            if (*active_record != 0) {
                register u8 **reload_slot __asm__("r6") = display_slot;
                register u8 *row_address __asm__("r0");
                register u32 field_offset __asm__("r6");
                __asm__("" : "+r"(reload_slot));
                row_address = *reload_slot;
                __asm__("" : "+r"(row_address));
                row_address += row_offset;
                __asm__("" : "+r"(row_address));
                field_offset = 0x9EF;
                __asm__("" : "+r"(field_offset));
                row_address += field_offset;
                __asm__("" : "+r"(row_address));
                *row_address = (u8)row_rank;
                row_rank++;
            }
            row_offset += 20;
            active_record += record_stride;
            countdown--;
        } while (countdown >= 0);
    }
    switch (({ register u32 selector_mask __asm__("r0") = 127;
               register u32 selector_mode __asm__("r1");
               __asm__("" : "+r"(selector_mask));
               selector_mode = mode_byte;
               __asm__("" : "+r"(selector_mode));
               selector_mask&selector_mode; })-1) {
    case 0:
        KEYED_ORDER(((u32)active[5]<<8)+slot,"r2","r1","r2");
        break;
    case 1:
        KEYED_ORDER(((u32)*(u16 *)(active+22)<<8)+slot,"r2","r1","r2");
        break;
    case 2:
        KEYED_ORDER(((u32)*(u16 *)(active+26)<<8)+slot,"r2","r1","r2");
        break;
    case 3:
        {
            register u32 count __asm__("r2") = 0;
            register s32 slot __asm__("r3") = 0;
            register u8 **root_value __asm__("r6") = &RosterDisplay;
            register u8 **sort_root __asm__("r9");
            register u8 *active __asm__("r5");
            register u8 *base __asm__("r4");
            register u8 *raw_base __asm__("r0");
            register u32 raw_stride __asm__("r0");
            register u32 stride __asm__("r12");
            register u8 **first_count_slot __asm__("r1");
            register u8 **post_count_slot __asm__("r2");
            register u8 **copy_root __asm__("r5");
            register u8 *count_address __asm__("r0");
            register u32 count_field __asm__("r4");
            u32 read_count;
            __asm__("" : "+r"(count), "+r"(slot), "+r"(root_value));
            sort_root = root_value;
            __asm__("" : "+r"(sort_root));
            raw_base = RosterStorage;
            __asm__("" : "+r"(raw_base));
            active = raw_base;
            __asm__("" : "+r"(active));
            active += 132;
            __asm__("" : "+r"(active));
            base = raw_base;
            __asm__("" : "+r"(base));
            raw_stride = 264;
            __asm__("" : "+r"(raw_stride));
            stride = raw_stride;
            __asm__("" : "+r"(stride));
            do {
                if (*active != 0) {
                    register u32 old_count __asm__("r1") = count;
                    register u32 key_index __asm__("r0");
                    register u8 *key_base __asm__("r6");
                    register u8 *key_address __asm__("r2");
                    register u32 key_value __asm__("r0");
                    register u32 incremented __asm__("r0");
                    register u32 payload_index __asm__("r1");
                    register u8 *payload_address __asm__("r0");
                    __asm__("" : "+r"(old_count));
                    key_index = old_count<<3;
                    __asm__("" : "+r"(key_index));
                    key_base = (u8 *)pairs;
                    __asm__("" : "+r"(key_base));
                    key_address = key_base+key_index;
                    __asm__("" : "+r"(key_address));
                    key_value = ((u32)*(u16 *)(base+342)<<8)+slot;
                    __asm__("" : "+r"(key_value));
                    *(s32 *)key_address = key_value;
                    incremented = old_count+1;
                    __asm__("" : "+r"(incremented));
                    incremented <<= 24;
                    __asm__("" : "+r"(incremented));
                    count = incremented>>24;
                    payload_index = old_count<<3;
                    __asm__("" : "+r"(payload_index));
                    payload_address = (u8 *)pairs+4;
                    __asm__("" : "+r"(payload_address));
                    payload_address += payload_index;
                    __asm__("" : "+r"(payload_address));
                    *(s32 *)payload_address = slot;
                }
                active += stride;
                base += stride;
                slot++;
            } while (slot <= 23);
            first_count_slot = sort_root;
            __asm__("" : "+r"(first_count_slot));
            count_address = *first_count_slot;
            __asm__("" : "+r"(count_address));
            count_field = 0x95C;
            __asm__("" : "+r"(count_field));
            count_address += count_field;
            __asm__("" : "+r"(count_address));
            *count_address = (u8)count;
            SortRosterPairs(pairs,0,(s32)count-1,direction);
            slot = 0;
            post_count_slot = sort_root;
            __asm__("" : "+r"(post_count_slot));
            count_address = *post_count_slot;
            __asm__("" : "+r"(count_address));
            count_address += count_field;
            __asm__("" : "+r"(count_address));
            read_count = *count_address;
            __asm__("" : "+r"(read_count));
            if (slot < (s32)read_count) {
                u32 payload_address;
                copy_root = sort_root;
                __asm__("" : "+r"(copy_root));
                payload_address = (u32)pairs+4;
                do {
                    output[slot] = (u8)*(s32 *)payload_address;
                    payload_address += 8;
                    slot++;
                } while (slot < (s32)(*copy_root)[count_field]);
            }
        }
        break;
    case 4:
        KEYED_ORDER(((u32)active[2]<<8)+slot,"r2","r1","r2");
        break;
    case 5:
        KEYED_ORDER((u32)*active,"r1","r2","r6");
        break;
    default:
        {
            u8 written = 0;
            u8 count = 0;
            s32 slot;
            if (direction != 0) {
                {
                    register u8 *count_active __asm__("r1");
                    register u32 count_stride __asm__("r2");
                    register s32 count_remaining __asm__("r3");
                    count_active = ACTIVE_ROSTER_START();
                    __asm__("" : "+r"(count_active));
                    count_stride = 264;
                    __asm__("" : "+r"(count_stride));
                    count_remaining = 23;
                    __asm__("" : "+r"(count_remaining));
                    do {
                        if (*count_active != 0)
                            count++;
                        count_active += count_stride;
                        count_remaining--;
                    } while (count_remaining >= 0);
                }
                count = (u8)(count-1);
                slot = 0;
                active = ACTIVE_ROSTER_START();
                do {
                    if (*active != 0) {
                        u32 old_written = written;
                        written = (u8)(old_written+1);
                        output[old_written] = (u8)(count-slot);
                    }
                    active += 264;
                    slot++;
                } while (slot <= 23);
            } else {
                slot = 0;
                active = ACTIVE_ROSTER_START();
                do {
                    if (*active != 0) {
                        u32 old_written = written;
                        written = (u8)(old_written+1);
                        output[old_written] = (u8)slot;
                    }
                    active += 264;
                    slot++;
                } while (slot <= 23);
            }
        }
        break;
    }
}
