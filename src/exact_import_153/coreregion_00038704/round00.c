#include "interfaces.h"
int CoreRegion_00038704(u16 requested_id)
{
    int count=0,index;
    for(index=0;index<20;++index)
        if(gCategoryBankState.entries[index]==requested_id) ++count;
    return count;
}
