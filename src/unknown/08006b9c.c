typedef unsigned char u8;
typedef unsigned int u32;
typedef struct {
    u8 unknown_00[3];
    u8 slot;
    u32 unknown_04;
    u32 *entries;
} RegistrationBinding;

void sub_08006B9C(RegistrationBinding *binding)
{
    if (binding->slot != 255)
        binding->entries[binding->slot] = 0;
}
