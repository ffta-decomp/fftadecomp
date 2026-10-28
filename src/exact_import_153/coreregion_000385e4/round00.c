#include "interfaces.h"
int CoreRegion_000385E4(u16 requested_type)
{
    int available=0,index;
    for(index=0;index<64;++index) {
        if(gMissionBankState.records[index].type==requested_type && gMissionBankState.records[index].mission==0)
            ++available;
    }
    return available;
}
