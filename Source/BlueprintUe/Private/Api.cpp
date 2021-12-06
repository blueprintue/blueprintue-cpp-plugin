#include "Api.h"

#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Windows/WindowsPlatformHttp.h"

void Api::CreateBlueprint(TFunction<void(FString, TSharedPtr<FJsonObject>)> OnSuccessDelegate, TFunction<void(FString)> OnErrorDelegate, FString Title, FString Exposure, FString Expiration, FString UEVersion, FString Blueprint)
{
	OnSuccess = OnSuccessDelegate;
	OnError = OnErrorDelegate;

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &Api::OnProcessRequestComplete);
	HttpRequest->SetURL(Settings->Hostname + "/api/upload");
	HttpRequest->SetVerb("POST");
	HttpRequest->SetTimeout(1000);
	HttpRequest->SetHeader("X-Token",Settings->ApiKey);
	HttpRequest->SetHeader("Content-Type","application/x-www-form-urlencoded");

	Exposure = Exposure.ToLower();
	if (Expiration == "Never")
	{
		Expiration = "never";
	}
	else if (Expiration == "1 hour")
	{
		Expiration = "3600";
	}
	else if (Expiration == "1 day")
	{
		Expiration = "86400";
	}
	else if (Expiration == "1 week")
	{
		Expiration = "604800";
	}
	
	const FString PostContent = FString::Printf(TEXT("title=%s&exposure=%s&expiration=%s&version=%s&blueprint=%s"),
		*FPlatformHttp::UrlEncode(Title),
		*FPlatformHttp::UrlEncode(Exposure),
		*FPlatformHttp::UrlEncode(Expiration),
		*FPlatformHttp::UrlEncode(UEVersion),
		*FPlatformHttp::UrlEncode(Blueprint)
	);
	HttpRequest->SetContentAsString(PostContent);
	
	HttpRequest->ProcessRequest();
}

void Api::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		OnError("error");
		return;
	}
	
	TSharedPtr<FJsonObject> JSONObject;
	const TSharedRef<TJsonReader<>> JSONReader = TJsonReaderFactory<>::Create(*Response->GetContentAsString());
	FJsonSerializer::Deserialize(JSONReader, JSONObject);
	
	if (Response->GetResponseCode() >= 400)
	{
		if (JSONObject)
		{
			FString errorMessage = JSONObject->GetStringField(TEXT("error"));
			OnError(errorMessage);
		}
		else
		{
			OnError("error");
		}

		return;
	}

	OnSuccess(Settings->Hostname, JSONObject);
}
