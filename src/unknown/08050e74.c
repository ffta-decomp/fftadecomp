typedef unsigned char u8;
extern unsigned CountMissionTokens(unsigned *);
asm(".global CountMissionTokens\n.thumb_set CountMissionTokens,0x08050c75");
unsigned CoreRegion_00050E74(void){return (u8)CountMissionTokens((unsigned *)0);}
