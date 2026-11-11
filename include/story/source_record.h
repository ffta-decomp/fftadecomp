#ifndef SCENE_SOURCE_RECORD_H
#define SCENE_SOURCE_RECORD_H

typedef unsigned char u8;
typedef unsigned int u32;

/* Only the two coordinate bytes and record stride are currently identified. */
typedef struct SceneSourceRecord {
    u8 x;
    u8 y;
    u8 unknown[18];
} SceneSourceRecord;

typedef struct SceneStateSourcePrefix {
    u8 unknown[0x67c];
    SceneSourceRecord *source_records;
} SceneStateSourcePrefix;

#define SCENE_STATE_SOURCE_POINTER ((SceneStateSourcePrefix **)0x03002810)

#endif
