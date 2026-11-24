typedef unsigned char u8;
extern void ApplyMenuContent(unsigned,unsigned);
extern void SetMenuContentClass(unsigned);
__asm__(".global ApplyMenuContent\n.thumb_set ApplyMenuContent,0x08011b31\n.global SetMenuContentClass\n.thumb_set SetMenuContentClass,0x0801339d");
void ApplyClassifiedMenuContent(u8 content) {
 ApplyMenuContent(4,content);
 switch(content) {
 case 64:
 case 67:
 case 68:
 case 76:
 case 82:
 case 83:
 case 85:
 case 86:
  SetMenuContentClass(2);break;
 case 65:
 case 66:
 case 69:
 case 70:
 case 71:
 case 72:
 case 73:
 case 74:
 case 75:
 case 77:
 case 78:
 case 79:
 case 80:
 case 81:
 case 84:
  break;
 default:break;
 }
}
