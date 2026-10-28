/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08145990.c
 * Original SHA-256: 70acd18d51f821d16449ad4ed7c44d7e7a4b449ab316a665e8bfa4da7dfc7396
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x50];
} MusicPlayerTrack;

typedef struct {
    void *song;
    u32 status;
    u8 track_count;
    u8 unknown_09[0x23];
    MusicPlayerTrack *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer;

extern void func_08144D94(MusicPlayer *player, MusicPlayerTrack *track);

/* Complete [0x08145990, 0x081459D0): 64 bytes, 29 instructions. */
void func_08145990(MusicPlayer *player)
{
    s32 count;
    MusicPlayerTrack *track;

    if (player->signature != 0x68736D53)
        return;

    player->signature++;
    player->status |= 0x80000000;
    count = player->track_count;
    track = player->tracks;
    while (count > 0) {
        func_08144D94(player, track);
        count--;
        track++;
    }
    player->signature = 0x68736D53;
}
