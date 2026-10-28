#include "interfaces.h"
s32 CoreRegion30_00060544(void *unused,s32 incoming_index)
{
 s32 index=(s16)incoming_index,adjusted_index;struct SelectionContext *context;struct Record *record;
 if(index>1)return 2;
 context=gSelection;
 adjusted_index=index-2;adjusted_index+=context->record_count;
 record=context->records[adjusted_index];
 if(!record || !record->identity)return -2;
 return index;
}
