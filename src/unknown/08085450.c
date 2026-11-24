typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { unsigned char prefix[8];u16 content_index;unsigned char suffix[10]; } MenuContentRow;
typedef struct { int count;const u32 *content;unsigned char reserved[16];MenuContentRow *rows; } MenuContentDefinition;
void BuildPanelContentList(u32 ordinal,u32 *output,const MenuContentDefinition *definition,u32 mode)
{
 u16 index=0;
 if(index<definition->count) {
  const MenuContentRow *rows=definition->rows;
  const u32 *content=definition->content;
  do {
   *output++=content[rows[index].content_index];
   ++index;
  } while(index<definition->count);
 }
}
