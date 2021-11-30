#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BlueprintUeStyle.h"

class FBlueprintUeCommands : public TCommands<FBlueprintUeCommands>
{
public:

	FBlueprintUeCommands()
		: TCommands<FBlueprintUeCommands>(TEXT("BlueprintUe"), NSLOCTEXT("Contexts", "BlueprintUe", "BlueprintUe Plugin"), NAME_None, FBlueprintUeStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
