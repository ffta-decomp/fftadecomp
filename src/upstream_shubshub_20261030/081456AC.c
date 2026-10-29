/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/081456AC.c
 * Original SHA-256: fd5e1083af8bb832bb735b894079a42727198746d0a7558eda5364b606bd1c25
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 status;
    u8 unknown_01[0x3F];
} SoundChannel;

typedef struct {
    u32 signature;
    u8 unknown_04;
    u8 reverb;
    u8 channel_count;
    u8 master_volume;
    u8 unknown_08[0x48];
    SoundChannel channels[12];
} SoundState;

extern SoundState *data_03007FF0;
/* High byte of GBA SOUNDBIAS: bits 6-7 select PWM resolution. */
extern u8 data_04000089;
extern void func_08145798(void);
extern void func_08145608(u32 frequency);

/* Complete [0x081456AC, 0x08145744): 152 bytes, including literal pools. */
void func_081456AC(u32 mode)
{
    SoundState *sound = data_03007FF0;
    u32 value;
    SoundChannel *channel;

    if (sound->signature != 0x68736D53)
        return;
    sound->signature++;
    value = mode & 0xFF;
    if (value)
        sound->reverb = value & 0x7F;
    value = mode & 0xF00;
    if (value) {
        sound->channel_count = value >> 8;
        value = 12;
        channel = sound->channels;
        do {
            channel->status = 0;
            value--;
            channel++;
        } while (value);
    }
    value = mode & 0xF000;
    if (value)
        sound->master_volume = value >> 12;
    value = mode & 0xB00000;
    if (value) {
        value = (value & 0x300000) >> 14;
        data_04000089 = (data_04000089 & 0x3F) | value;
    }
    value = mode & 0xF0000;
    if (value) {
        func_08145798();
        func_08145608(value);
    }
    sound->signature = 0x68736D53;
}
