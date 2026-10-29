#include "interfaces.h"
asm(".global gGame\n.set gGame,0x02000000\n.global GetFrame\n.thumb_set GetFrame,0x80a88ed\n.global GetFrameHeader\n.thumb_set GetFrameHeader,0x80a880d\n.global GetFrameRelation\n.thumb_set GetFrameRelation,0x80a8811\n.global GetRelationCount\n.thumb_set GetRelationCount,0x80a8831\n.global GetRelationFlag\n.thumb_set GetRelationFlag,0x80a8859\n.global GetFrameCount\n.thumb_set GetFrameCount,0x80a88e1\n.global HasEligibleFrame\n.thumb_set HasEligibleFrame,0x81352cd\n.global UnitHasExclusionFlag\n.thumb_set UnitHasExclusionFlag,0x80c8281");

static inline struct WeightedEntry *FindOrAppend(struct WeightedList *list,struct Record *record)
{
    register struct Record *sought asm("r5")=record;
    register int index asm("r2")=0;
    register u8 *count_address asm("r0");
    register int count asm("r1");
    register u8 *saved_count_address asm("r4");
    register struct WeightedEntry *cursor asm("r1");
    asm("" : "+r"(sought), "+r"(index));
    count_address=&list->count;
    count=*count_address;
    asm("" : "+r"(count) : "r"(count_address));
    saved_count_address=count_address;
    asm("" : : "r"(saved_count_address), "r"(count));
    if (index<count) {
        int retained_bound=count;
        cursor=list->entries;
        do {
            if (cursor->record==sought) goto found;
            ++cursor;
            ++index;
        } while (index<retained_bound);
    }
    cursor=0;
found:
    asm("" : "+r"(cursor));
    if (!cursor) {
        register u32 old_count asm("r0")=*saved_count_address;
        asm("" : "+r"(old_count));
        *saved_count_address=old_count+1;
        old_count=(u32)(u8)old_count*8;
        asm("" : "+r"(old_count));
        {
            register u8 *append_base asm("r2")=(u8 *)list;
            asm("" : : "r"(append_base), "r"(old_count));
            cursor=(struct WeightedEntry *)(append_base+old_count);
        }
    }
    return cursor;
}

void CoreFrontier_000BB5C4(struct WeightedList *list,void *frames,u8 exclude_first,u8 mode)
{
    int frame_count,index;
    struct Record *ignored;
    register void *frame asm("r5");
    register void *produced_frame asm("r0");
    struct Header *header;
    if (gGame.blocked==1) return;
    ignored=0;
    if (exclude_first) {
        register struct Record *loaded_ignored asm("r1");
        produced_frame=GetFrame(frames,0);
        frame=produced_frame;
        asm("" : : "r"(frame), "r"(produced_frame));
        loaded_ignored=GetFrameHeader(produced_frame)->record;
        asm("" : "+r"(loaded_ignored));
        ignored=loaded_ignored;
    } else {
        u8 allowed;
        if (mode) allowed=HasEligibleFrame(frames,0,1);
        else allowed=HasEligibleFrame(frames,0,0);
        if (allowed) {
            u32 weight=1;
            register struct WeightedEntry *entry asm("r1");
            produced_frame=GetFrame(frames,0);
        frame=produced_frame;
        asm("" : : "r"(frame), "r"(produced_frame));
            header=GetFrameHeader(produced_frame);
            entry=FindOrAppend(list,header->record);
            asm("" : "+r"(entry));
            if (entry->record) {
                register u32 old_weight asm("r0")=entry->weight;
                asm("" : "+r"(old_weight));
                if (old_weight>=weight) weight=old_weight;
            }
            entry->record=header->record;
            entry->weight=weight;
        }
    }
    frame_count=GetFrameCount(frames);
    for (index=0;index<frame_count;++index) {
        produced_frame=GetFrame(frames,index);
        frame=produced_frame;
        asm("" : : "r"(frame), "r"(produced_frame));
        header=GetFrameHeader(produced_frame);
        if (header->record && header->record!=ignored &&
            !(u8)UnitHasExclusionFlag(header->record->unit)) {
            int best=0;
            int relations=GetRelationCount(frame);
            struct Header *current=GetFrameHeader(frame);
            int relation;
            for (relation=0;relation<relations;++relation) {
                struct Relation *candidate=GetFrameRelation(frame,relation);
                register int weight asm("r0");
                if (!current->record || current->record==candidate->record ||
                    !(u8)GetRelationFlag(candidate,3)) {
                    weight=0;
                    asm("" : "+r"(weight));
                } else if (current->operation==184) {
                    weight=10;
                    asm("" : "+r"(weight));
                } else {
                    weight=1;
                    asm("" : "+r"(weight));
                }
                if (weight>best) best=weight;
            }
            {
                /* Native post-relation copy: signed max becomes the unsigned
                 * selected byte weight, separate from the signed accumulator. */
                register u32 selected_weight asm("r6")=(u32)best;
                asm("" : "+r"(selected_weight));
                if (selected_weight) {
                    register struct WeightedEntry *entry asm("r1")=FindOrAppend(list,header->record);
                    asm("" : "+r"(entry));
                    if (!entry->record || (u32)entry->weight<selected_weight) {
                        entry->record=header->record;
                        entry->weight=selected_weight;
                    }
                }
            }
        }
    }
    if (gGame.flags&128) list->limit=12;
}
