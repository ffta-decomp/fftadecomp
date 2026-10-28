typedef unsigned char u8;extern void select_content(void*,unsigned);
#define DEST (*(u8 **)0x0200F428+0x1414)
void SceneTaskDependency_00058890(u8 score){if(score<=29){select_content(DEST,159);return;}if(score<=79){select_content(DEST,160);return;}if(score<=99){select_content(DEST,161);return;}select_content(DEST,162);}
__asm__(".thumb_set select_content,0x0802b555");
