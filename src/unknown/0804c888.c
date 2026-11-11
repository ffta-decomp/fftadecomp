typedef unsigned char u8;
extern void InitMenu(void);extern void TeardownMenu(void);extern unsigned MenuComplete(void);
asm(".global InitMenu\n.thumb_set InitMenu,0x0804c8c5\n.global TeardownMenu\n.thumb_set TeardownMenu,0x0804c97d\n.global MenuComplete\n.thumb_set MenuComplete,0x0804c9e5");
void CoreGlobal36_0004C888(unsigned unused,u8 *state){switch(*state){case 0:InitMenu();*state=1;break;case 2:TeardownMenu();*state=3;break;case 1:if(MenuComplete())*state=2;break;}}
