#pragma once

#include "SCreateBlueprint.h"
#include "SLastBlueprintsPasted.h"

class SMain : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SMain ) {}
	SLATE_END_ARGS()
	
	void Construct( const FArguments& InArgs );

private:
	void MainMenu();

	int32 TabIndex = 0;
 
	int32 GetCurrentTabIndex() const
	{
		return TabIndex;
	}
	
	TSharedPtr<SCreateBlueprint> SlateCreateBlueprint;
	TSharedPtr<SLastBlueprintsPasted> SlateLastBlueprintsPasted;
};
