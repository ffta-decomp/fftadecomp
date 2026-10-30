/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08146188.c
 * Original SHA-256: b84d168745065b538961f130f62c93d755683f20c44f25d0390c0e2b4ed3a16b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x0a];
    s8 key_shift;
    u8 unknown_0c;
    u8 pitch;
    u8 unknown_0e[0x42];
} PlayerTrack;

typedef struct {
    u8 unknown_00[8];
    u8 track_count;
    u8 unknown_09[0x23];
    PlayerTrack *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer;

/* Target: complete [0x08146188, 0x081461FC), 116 bytes, 56 instructions. */
void func_08146188(MusicPlayer *player, u16 selected_tracks, u16 pitch)
{
    PlayerTrack *track;
    s32 remaining;
    u32 bit;

    if (player->signature != 0x68736d53)
        return;

    player->signature++;
    remaining = player->track_count;
    track = player->tracks;
    bit = 1;
    while (remaining > 0) {
        if ((selected_tracks & bit) && (track->flags & 0x80)) {
            track->key_shift = (s16)pitch >> 8;
            track->pitch = pitch;
            track->flags |= 0x0c;
        }
        remaining--;
        track++;
        bit <<= 1;
    }
    player->signature = 0x68736d53;
}
