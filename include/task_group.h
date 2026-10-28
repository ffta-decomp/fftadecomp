#ifndef FFTA_TASK_GROUP_H
#define FFTA_TASK_GROUP_H

typedef unsigned char TaskU8;
typedef unsigned short TaskU16;
typedef unsigned int TaskU32;

/* A task group stores callback pointers separately from per-slot state bytes. */
typedef void (*TaskCallback)(TaskU8 slot, TaskU8 *state);

/* Offsets are grounded in retail loads/stores; semantic names remain inferred. */
struct TaskGroup {
    TaskU16 unknown_00;
    TaskU8 configured_slots;
    TaskU8 current_slot;
    TaskU8 processed_count;
    TaskU8 run_mode;
    TaskU16 unknown_06;
    TaskCallback *callbacks;
    TaskU8 *slot_state;
};

#endif
