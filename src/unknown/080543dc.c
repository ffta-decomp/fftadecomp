typedef unsigned char u8;
typedef unsigned short u16;
void SetMenuCursorRow(u8 *cursor,u8 row) {
 cursor[17]=row;
 *(u16 *)(cursor+14)=row*24;
}
