/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
u8 ReadSaveByte(u16 index) __asm__("ReadSaveByte");
void WriteSaveByte(u16 index, u8 value) __asm__("WriteSaveByte");


u32 ConsumeSaveMode12State(u32 *word_to_clear, u16 *halfword_to_clear)
{
    /* Retain separate accessor calls and their observed order. */
    if ((u8)ReadSaveByte(12) == 3) {
        *halfword_to_clear = 0;
        goto clear_word;
    }
    if ((u8)ReadSaveByte(12) == 2) {
        *halfword_to_clear = 0;
        goto clear_save_byte;
    }
    if ((u8)ReadSaveByte(12) != 1)
        return 0;
clear_word:
    *word_to_clear = 0;
clear_save_byte:
    WriteSaveByte(12, 0);
    return 1;
}
