#include "interfaces.h"
/* Rotate the progression-sensitive valuation categories; retain native retry rules. */
void CoreDependency29_000CC198(void)
{
    gCategoryState.active_a=gCategoryState.upcoming_a;
    gCategoryState.active_b=gCategoryState.upcoming_b;
    do {
        gCategoryState.upcoming_a=(s16)NRandom()%9+1;
    } while(gCategoryState.upcoming_a==3 || gCategoryState.upcoming_a==5);
    {
        u8 *first=gUpcomingPair;
        u8 *second=first+1;
        do {
            *second=(s16)NRandom()%9+1;
        } while(*second==*first || *second==3 || *second==5);
    }
}
