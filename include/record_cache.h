#ifndef FFTA_RECORD_CACHE_H
#define FFTA_RECORD_CACHE_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

/* Two-word entries are cleared or initialized as part of record-bank setup. */
struct RecordPoolPair {
    u32 first;
    u32 second;
};

/* Eight-byte record layout is known; the records' game-level role is not. */
struct Record8 {
    u16 words[4];
};

extern u8 gRecordBankIndex;
extern u8 gRecordSlotUsed[];
extern struct Record8 gRecordEntries[];
extern u32 gRecordPoolHeadA[];
extern u32 gRecordPoolHeadB[];
extern u32 gRecordPoolHeadC[];
extern u32 gRecordPoolHeadD[];
extern struct RecordPoolPair gRecordPool48A[];
extern struct RecordPoolPair gRecordPool32A[];
extern struct RecordPoolPair gRecordPool128A[];
extern struct RecordPoolPair gRecordPool16A[];
extern u8 gRecordPoolUseFlag;

int FindOrInsertRecord8(const volatile struct Record8 *record);
void InitializeRecordBank(void);
void InitializeSecondaryRecordPools(void);

#endif
