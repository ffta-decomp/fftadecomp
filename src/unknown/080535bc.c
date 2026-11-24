typedef unsigned char u8;
struct OfferSelectionScene { u8 unaccessed_prefix[0x1d48]; u8 selected[20]; };
extern struct OfferSelectionScene *volatile gOfferSelectionScene;
/* Reload the current scene for each original byte store. */
void CoreClosure31_000535BC(void)
{
    u8 index = 0;
    do {
        gOfferSelectionScene->selected[index] = 0;
        index++;
    } while (index <= 19);
}
asm(".global gOfferSelectionScene\n.set gOfferSelectionScene,0x0200F428\n");
