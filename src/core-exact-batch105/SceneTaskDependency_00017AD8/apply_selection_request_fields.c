typedef unsigned char u8;
typedef unsigned short u16;
typedef struct SelectionFieldRequest {
    u8 unknown[21];
    u8 byte21;
    u16 unknown22, unknown24;
    u16 half26;
} SelectionFieldRequest;
extern void ApplySelectionByte_08017618(SelectionFieldRequest *request, u8 value);
extern void ApplySelectionHalfword_08017734(SelectionFieldRequest *request, u16 value);
__asm__(".global ApplySelectionByte_08017618\n.thumb_set ApplySelectionByte_08017618, 0x08017619\n.global ApplySelectionHalfword_08017734\n.thumb_set ApplySelectionHalfword_08017734, 0x08017735");
void ApplySelectionRequestFields(SelectionFieldRequest *request) __asm__("SceneTaskDependency_00017AD8");
void ApplySelectionRequestFields(SelectionFieldRequest *request)
{
    ApplySelectionByte_08017618(request, request->byte21);
    ApplySelectionHalfword_08017734(request, (u16)(request->half26 * 2));
}
