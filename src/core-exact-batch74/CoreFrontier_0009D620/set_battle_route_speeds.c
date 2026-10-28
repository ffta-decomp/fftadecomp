typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleRouteSpeedRecord {
    u8 unaccessed_prefix[28];
    u16 current_speed;
    u16 default_speed;
    u16 speed_for_next_phase;
    u16 speed_for_commands_four_five;
    u16 speed_for_commands_two_three_six_seven;
};
void SetBattleRouteSpeeds(struct BattleRouteSpeedRecord *record, u16 default_speed,
    u32 next_phase_speed, u32 branch_speed, u32 remaining_command_speed)
{
    record->default_speed = default_speed;
    record->speed_for_next_phase = next_phase_speed;
    record->speed_for_commands_four_five = branch_speed;
    record->speed_for_commands_two_three_six_seven = remaining_command_speed;
    record->current_speed = default_speed;
}
