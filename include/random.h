#ifndef FFTA_RANDOM_H
#define FFTA_RANDOM_H

typedef unsigned int u32;

/* Advances the global generator and returns its next 15-bit value. */
u32 NextRandom15(void);

/* Replaces the global generator state. */
void SeedRandom(u32 seed);

/* Returns the address of the generator state used by game code. */
volatile u32 *GetRandomSeedAddress(void);

#endif
