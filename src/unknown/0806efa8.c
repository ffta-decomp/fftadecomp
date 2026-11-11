typedef unsigned char u8;
typedef unsigned short u16;
extern void RefreshSelector(void *);
void NavigateSelector(u8 *selector,u16 key) {
 switch(key) {
 case 32: if(selector[0]==0) selector[0]=selector[7]-1; else selector[0]--; break;
 case 16: if(selector[0]==selector[7]-1) selector[0]=0; else selector[0]++; break;
 }
 RefreshSelector(selector);
}
asm(".global RefreshSelector\n.thumb_set RefreshSelector,0x0806ee99");
