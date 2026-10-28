typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MappedRuleView { u32 descriptor; u8 unknown04[12]; } __attribute__((packed));
typedef char MappedRuleSizeCheck[sizeof(struct MappedRuleView)==16?1:-1];
extern u32 RetailCall_080ccad8(u32);
asm(".global RetailCall_080ccad8\n.thumb_set RetailCall_080ccad8,0x080ccad9");

void CoreFrontier_000C9208(u32 incoming_job_id,u8 *destination)
{
    u16 job_id=incoming_job_id;
    register u8 *output __asm__("r5")=destination;
    int index;
    u8 *cursor;
    /* The initialized root stays distinct from the advancing cursor. */
    asm("" : "+r"(output));
    output[0]=output[1]=output[2]=255;
    switch(job_id) {
    case 202: output[0]=0; output[1]=1; break;
    case 203: output[0]=2; output[1]=3; output[2]=4; break;
    case 204: output[0]=5; output[1]=6; break;
    case 205: output[0]=7; output[1]=8; output[2]=9; break;
    case 206: output[0]=10; output[1]=11; break;
    case 207: output[0]=12; output[1]=13; break;
    case 208: output[0]=14; output[1]=15; break;
    case 209: output[0]=16; output[1]=17; break;
    case 210: output[0]=18; output[1]=19; break;
    }
    index=0;
    cursor=output;
    do {
        u8 *zero_slot=output+index;
        u32 mapped_id;
        u32 selected;
        if(*cursor==255) {
            *zero_slot=0;
            return;
        }
        mapped_id=*cursor;
        selected=((const struct MappedRuleView *)0x02002e78)[mapped_id].descriptor;
        if(selected != 0)
            selected=RetailCall_080ccad8(mapped_id);
        *cursor=selected;
        cursor++;
        index++;
    } while(index<3);
}
