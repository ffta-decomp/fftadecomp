#include "interfaces.h"
int CoreRegion_000384F0(u16 requested_type)
{
    int index;
    for(index=0;index<64;++index) {
        if(gMissionBankState.records[index].type==0) {
            gMissionBankState.records[index].type=requested_type;
            return 1;
        }
    }
    return 0;
}
