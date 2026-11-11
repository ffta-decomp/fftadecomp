#ifndef FFTA_RAM_MEMORY_H
#define FFTA_RAM_MEMORY_H

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

/* Relocatable byte operations copied into IWRAM at startup. */
void ClearBytes(u8 *destination, s32 byte_count);
void FillBytes(u8 *destination, s32 byte_count, u32 value);
void CopyBytes(u8 *destination, const u8 *source, s32 byte_count);

#endif
