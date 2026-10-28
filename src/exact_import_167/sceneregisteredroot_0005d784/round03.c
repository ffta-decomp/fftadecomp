#include "interfaces.h"
u8 UpdateEligibleDefinitionSelection(void) __asm__("SceneRegisteredRoot_0005D784");
u8 UpdateEligibleDefinitionSelection(void)
{
    s32 phase = gDefinitionChoiceContext->phase;
    switch (phase) {
    case 0: {
        u8 previous_count;
        const struct ContentRule **output;
        ResetDefinitionWindow(0, 0, 0, 0);
        ConfigureDefinitionWindow(gDefinitionDisplay, 0, 0, 20, 17, phase);
        previous_count = gDefinitionChoiceContext->rule_count;
        output = gDefinitionChoiceContext->rules;
        gDefinitionChoiceContext->rule_count = CollectEligibleContentRules(output, 64,
            (u8)ResolveCurrentSceneSelector(gDefinitionChoiceSave.scene_selector));
        if (previous_count != gDefinitionChoiceContext->rule_count)
            ResetDefinitionChooser(2, 0);
        InitializeDefinitionChooser(2);
        CopyDefinitionChoices(gDefinitionChoiceContext->rules, gDefinitionChoiceContext->rule_count);
        gDefinitionChoiceContext->selected_rule = (const struct ContentRule *)phase;
        gDefinitionChoiceContext->phase = 1;
        break;
    }
    case 1:
        if (PollDefinitionChooser() != 0) {
            u8 result = ReadDefinitionChoiceResult();
            switch (result) {
            case 1: case 2:
                return (u8)CancelDefinitionChoice();
            case 3: case 4: {
                u16 selected_index = (u16)ReadDefinitionSelectedIndex();
                const struct ContentRule *selected;
                struct DefinitionChoiceContext *context = gDefinitionChoiceContext;
                context->selected_rule = selected = context->rules[selected_index];
                OpenDefinitionDialog(context, 8, (u16)(selected->definition_code - 1),
                    gDefinitionDisplay, gDefinitionSecondaryDisplay, 2, phase, 24, 16, 448);
                gDefinitionChoiceContext->phase = 2;
                break;
            }
            }
        }
        break;
    case 2:
        if ((u16)PollDefinitionDialog() != 0) {
            UnlockDefinitionProgressFlag((const u8 *)gDefinitionChoiceContext->selected_rule);
            gDefinitionChoiceContext->phase = 0;
        }
        break;
    }
    return 3;
}
