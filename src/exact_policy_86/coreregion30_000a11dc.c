/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef signed short s16;
struct Actor { void *unit; };
struct CoordinatePair { u32 x,y; };
struct CandidateChoice {
    struct Actor *actor, *current;
    union { struct Actor *entries[0]; u8 unknown[8]; } candidates;
    union { struct CoordinatePair entries[0]; u8 unknown[16]; } coordinates;
    union { s32 entries[0]; u8 unknown[40]; } search_results;
    s16 count,index,cursor,selected;
};
typedef char ChoiceIndexOffset[(u32)&((struct CandidateChoice*)0)->index==74?1:-1];
typedef char ChoiceResultOffset[(u32)&((struct CandidateChoice*)0)->search_results==32?1:-1];
typedef char CoordinateSize[sizeof(struct CoordinatePair)==8?1:-1];
extern s32 SearchCandidate(struct CandidateChoice *,struct Actor *,s32,s32,struct Actor **,struct CoordinatePair *,u32);
extern u32 HasUnitStatus15(const void *);
extern u32 NextRandom15(void);
__asm__(".global SearchCandidate\n.thumb_set SearchCandidate,0x080a0ded\n.global HasUnitStatus15\n.thumb_set HasUnitStatus15,0x080c8241\n.global NextRandom15\n.thumb_set NextRandom15,0x08002805");

u32 AdvanceBattleCandidateSelection(struct CandidateChoice *choice,s32 search_limit);
u32 AdvanceBattleCandidateSelection(struct CandidateChoice *choice,s32 search_limit)
{
    s32 result=SearchCandidate(choice,choice->actor,choice->index,search_limit,
        &choice->candidates.entries[choice->index],
        &choice->coordinates.entries[choice->index],0);
    if (result<0) return 1;
    choice->cursor=0;
    choice->search_results.entries[choice->index]=result;
    choice->index++;
    if (choice->index>=choice->count) {
        s32 selected=0;
        if (choice->count>0) {
            struct Actor *first=choice->candidates.entries[0];
            struct Actor *second;
            if (first) {
                second=choice->candidates.entries[1];
                if (second) goto choose_between;
                selected=(u8)(HasUnitStatus15(choice->current->unit)^
                    HasUnitStatus15(choice->candidates.entries[0]->unit))!=0;
                goto selection_done;
            }
            second=choice->candidates.entries[1];
            if (!second) goto selection_done;
            if ((u8)HasUnitStatus15(choice->current->unit)!=
                (u8)HasUnitStatus15(choice->candidates.entries[1]->unit)) goto selection_done;
select_second:
            selected=1;
            goto selection_done;
choose_between:
            if (first==second) goto selection_done;
            if (choice->current==first) goto selection_done;
            if (choice->current==second) goto select_second;
            if ((u8)HasUnitStatus15(choice->current->unit)==
                (u8)HasUnitStatus15(choice->candidates.entries[0]->unit)) goto selection_done;
            if ((u8)HasUnitStatus15(choice->current->unit)==
                (u8)HasUnitStatus15(choice->candidates.entries[1]->unit)) goto select_second;
            selected=(s16)NextRandom15()%2;
        }
selection_done:
        choice->selected=selected;
    }
    return 0;
}
