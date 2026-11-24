typedef unsigned char u8;
typedef unsigned int u32;
struct WorksetSelectionView {
    u8 unknown_00[8];
    void *selected_record;
    u8 saved_record_value;
    u8 coordinate_first;
    u8 coordinate_second;
};
typedef char SelectedOffset[(u32)&(((struct WorksetSelectionView *)0)->selected_record)==8?1:-1];
typedef char FirstOffset[(u32)&(((struct WorksetSelectionView *)0)->coordinate_first)==13?1:-1];
typedef char SecondOffset[(u32)&(((struct WorksetSelectionView *)0)->coordinate_second)==14?1:-1];
/* Destinations may alias the workset; each store precedes the next read. */
void *ReadWorksetSelection(const struct WorksetSelectionView *workset, u8 *first, u8 *second)
{
    *first = workset->coordinate_first;
    *second = workset->coordinate_second;
    return workset->selected_record;
}
