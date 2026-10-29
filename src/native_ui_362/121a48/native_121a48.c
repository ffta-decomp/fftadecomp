#include "interfaces.h"

extern u8 SceneSaveImage[];
asm(".set SceneSaveImage,0x02000000");

void CoreRegion_00121A48(void)
{
    u8 *state_owner;
    u8 mode;
    u16 flags;
    u8 copied_byte;
    u32 context;

    {
    register u8 *mode_owner asm("r0") = *(u8 **)0x020159cc;
    asm("" : "+r"(mode_owner));
    mode = mode_owner[12];
    }
    switch (mode) {
    case 13:
        SetGameFlag(68, 1);
        goto publish_eighteen;
    case 2:
        EnterSceneMode();
        *(u8 *)0x0200f390 = 9;
        break;
    case 4:
        {
        register u8 *status_base asm("r4");
        register u16 *flags_address asm("r3");
        register u32 old_flags asm("r1");
        register u32 masked_flags asm("r0");
        register u32 clear_value asm("r2");
        BeginSceneAction(0);
        status_base = (u8 *)0x0200f390;
        asm("" : "+r"(status_base));
        flags_address = (u16 *)(status_base + 148);
        asm("" : "+r"(flags_address));
        old_flags = *flags_address;
        asm("" : "+r"(old_flags));
        masked_flags = old_flags & 0xfffe;
        clear_value = 0;
        asm("" : "+r"(masked_flags), "+r"(clear_value));
        masked_flags |= 4;
        *flags_address = masked_flags;
        status_base[0] = clear_value;
        break;
        }
    case 8:
        context = ReadBattleContext();
        context = ConfigureSceneAction(context, 1);
        ContinueSceneMode(context);
        /* Original call sequence falls through to the mode1 status write. */
    case 1:
        *(u8 *)0x0200f390 = 0;
        break;
    case 5:
    case 7:
        {
        register u8 *save_base asm("r0") = SceneSaveImage;
        register u32 source_offset asm("r2") = 0x2190;
        asm("" : "+r"(save_base), "+r"(source_offset));
        {
        register u8 *source_address asm("r1") = save_base + source_offset;
        asm("" : "+r"(source_address));
        copied_byte = *source_address;
        }
        {
        register u32 destination_offset asm("r3") = 0x2191;
        asm("" : "+r"(destination_offset));
        save_base[destination_offset] = copied_byte;
        }
        }
publish_eighteen:
        *(u8 *)0x0200f390 = 18;
        break;
    case 12:
        WriteSceneControl(8, 1);
        PrepareEffect();
        NotifySceneCode(162);
        CompleteSceneTransition();
        {
        register u8 *transition_base asm("r0") = (u8 *)0x0200f390;
        u16 *transition_flags;
        register u32 prior_flags asm("r2");
        register u32 effect_mask asm("r3");
        register u32 working_flags asm("r1");
        asm("" : "+r"(transition_base));
        transition_flags = (u16 *)(transition_base + 148);
        prior_flags = *transition_flags;
        asm("" : "+r"(prior_flags));
        effect_mask = 0x100;
        asm("" : "+r"(effect_mask));
        working_flags = effect_mask;
        asm("" : "+r"(working_flags));
        working_flags |= prior_flags;
        *transition_flags = working_flags;
        }
        break;
    default:
        break;
    }
    state_owner = *(u8 **)0x020159cc;
    state_owner[12] = 0;
}
