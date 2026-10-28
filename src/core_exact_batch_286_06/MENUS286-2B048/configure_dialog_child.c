typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Neutral physical fields retain the observed configuration/store order. */
void ConfigureDialogChild(u8 *child,u32 status,u32 option,u32 request,u32 value,u32 setting) {
 child[0x797]=status;
 child[0x79b]=option;
 child[0x79a]=request;
 child[0x798]=value;
 *(u16 *)(child+0x794)=setting;
}
