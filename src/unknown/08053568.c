typedef unsigned char u8;
typedef unsigned short u16;
struct OfferSelectionScene { u8 unaccessed_prefix[0x1d48]; u8 selected[20]; };
extern struct OfferSelectionScene *volatile gOfferSelectionScene;
extern u16 gPendingOfferIds[20];
extern unsigned int ReadOfferNominalValue(u16 item_id);
/* Totals wrap on byte stores. Outputs may alias and helpers may change scene. */
void CoreClosure31_00053568(u8 *selected_count, u8 *nominal_total)
{
    u8 index;
    u16 *ids;
    *selected_count = 0;
    *nominal_total = 0;
    index = 0;
    ids = gPendingOfferIds;
    do {
        if (gOfferSelectionScene->selected[index] == 1) {
            unsigned int nominal = ReadOfferNominalValue(ids[index]);
            nominal += *nominal_total;
            *nominal_total = nominal;
            *selected_count = *selected_count + 1;
        }
        index++;
    } while (index <= 19);
}
asm(".global gOfferSelectionScene\n.set gOfferSelectionScene,0x0200F428\n"
    ".global gPendingOfferIds\n.set gPendingOfferIds,0x02001F3C\n"
    ".global ReadOfferNominalValue\n.thumb_set ReadOfferNominalValue,0x080CCA21\n");
