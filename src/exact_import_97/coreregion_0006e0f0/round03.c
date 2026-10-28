#include "interfaces.h"
void SelectItemAffordabilityContinuation(u8 *request_state) __asm__("CoreRegion_0006E0F0");
void SelectItemAffordabilityContinuation(u8 *request_state)
{
    PlayChoiceFeedbackSound(100);
    *request_state = 60;
    {
        const struct ItemPriceDefinition *definitions = gChoicePriceDefinitions;
        const struct ItemPriceDefinition *definition =
            &definitions[gChoiceEconomyState.item_choices[gItemChoiceController->selected_choice]];
        u8 price_class = definition->price_class;
        u32 price = gChoicePriceRows[price_class].base_price * 200;
        if (price <= gChoiceEconomyState.currency)
            gItemChoiceController->next_state = 100;
        else
            gItemChoiceController->next_state = 80;
    }
}
