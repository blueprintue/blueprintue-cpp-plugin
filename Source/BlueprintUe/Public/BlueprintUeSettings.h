#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BlueprintUeSettings.generated.h"

UCLASS(config = BlueprintUE, defaultconfig)
class UBlueprintUeSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, GlobalConfig, Category = "blueprintUE parameters")
	FString ApiKey;

	UPROPERTY(EditAnywhere, GlobalConfig, Category = "blueprintUE parameters")
	FString Hostname;

	UBlueprintUeSettings()
	{
		Hostname="https://blueprintue.com";
	}
};