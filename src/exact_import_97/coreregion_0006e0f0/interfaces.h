typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ChoiceEconomyState {
    u8 unknown00[0x1f30]; u16 item_choices[5]; u8 unknown1f3a[0x2a]; u32 currency;
};
struct ItemPriceDefinition { u8 unknown00[24]; u8 price_class; u8 unknown19[7]; };
struct ItemPriceRow { u16 unknown00, base_price; };
struct ItemChoiceController {
    u8 unknown00[0x446c]; u8 next_state; u8 unknown446d[0x82]; u8 selected_choice;
};
typedef char DefinitionSize[sizeof(struct ItemPriceDefinition)==32?1:-1];
typedef char PriceRowSize[sizeof(struct ItemPriceRow)==4?1:-1];
typedef char MoneyOffset[(u32)&((struct ChoiceEconomyState*)0)->currency==0x1f64?1:-1];
typedef char ChoiceOffset[(u32)&((struct ItemChoiceController*)0)->selected_choice==0x44ef?1:-1];
typedef char StateOffset[(u32)&((struct ItemChoiceController*)0)->next_state==0x446c?1:-1];
extern struct ChoiceEconomyState gChoiceEconomyState;
extern const struct ItemPriceDefinition gChoicePriceDefinitions[];
extern const struct ItemPriceRow gChoicePriceRows[];
extern struct ItemChoiceController *gItemChoiceController;
/* Existing retail sound entry consumes low16 of a full caller register. */
extern void PlayChoiceFeedbackSound(u32);
__asm__(".global gChoiceEconomyState\n.set gChoiceEconomyState,0x02000000");
__asm__(".global gChoicePriceDefinitions\n.set gChoicePriceDefinitions,0x0851d180");
__asm__(".global gChoicePriceRows\n.set gChoicePriceRows,0x08528968");
__asm__(".global gItemChoiceController\n.set gItemChoiceController,0x0200f428");
__asm__(".global PlayChoiceFeedbackSound\n.thumb_set PlayChoiceFeedbackSound,0x08141541");
