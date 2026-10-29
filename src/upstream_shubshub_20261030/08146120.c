/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08146120.c
 * Original SHA-256: 66e99a75af10b3ba55695210b198919a6b9db2a9088c6e07db200e4f42a4084f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x12];
    u8 volume;
    u8 unknown_14[0x3C];
} PlayerTrack;

typedef struct {
    u8 unknown_00[8];
    u8 track_count;
    u8 unknown_09[0x23];
    PlayerTrack *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer;

/* Complete [0x08146120, 0x08146188): 104 bytes, 50 instructions. */
void func_08146120(MusicPlayer *player, u16 selected_tracks, u16 volume)
{
    PlayerTrack *track;
    s32 remaining;
    u32 bit;

    if (player->signature != 0x68736D53)
        return;

    player->signature++;
    remaining = player->track_count;
    track = player->tracks;
    bit = 1;
    while (remaining > 0) {
        if ((selected_tracks & bit) && (track->flags & 0x80)) {
            track->volume = volume >> 2;
            track->flags |= 3;
        }
        remaining--;
        track++;
        bit <<= 1;
    }
    player->signature = 0x68736D53;
}
