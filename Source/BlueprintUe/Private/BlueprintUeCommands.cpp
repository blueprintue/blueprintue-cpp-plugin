#include "BlueprintUeCommands.h"

#define LOCTEXT_NAMESPACE "FBlueprintUeModule"

void FBlueprintUeCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "blueprintUE", "Open blueprintUE", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
