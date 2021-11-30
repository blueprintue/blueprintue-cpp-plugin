#pragma once

#include "BlueprintUeSettings.h"
#include "HttpModule.h"

class Api
{
public:
	Api(){
		Settings = GetMutableDefault<UBlueprintUeSettings>();
	}
	void CreateBlueprint(TFunction<void(FString, TSharedPtr<FJsonObject>)> OnSuccess, TFunction<void(FString)> OnError, FString Title, FString Exposure, FString Expiration, FString UEVersion, FString Blueprint);

private:
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	void OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	TFunction<void(FString, TSharedPtr<FJsonObject>)> OnSuccess;
	TFunction<void(FString)> OnError;
	const UBlueprintUeSettings* Settings;
};
