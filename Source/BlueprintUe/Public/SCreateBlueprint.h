#pragma once

#include <iomanip>

#include "Dom/JsonObject.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

class SCreateBlueprint : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SCreateBlueprint ) {}
		SLATE_ARGUMENT(TFunction<void(const FString& InDate, const FString& InURL)>, OnSuccess)
	SLATE_END_ARGS()

	void Construct( const FArguments& InArgs );
private:
	TFunction<void(const FString& InDate, const FString& InURL)> OnSuccess;
	
	// region title
	FString Title;
	TSharedPtr<SEditableTextBox> TitleEditableTextBox;
	// endregion

	// region exposure
	FString Exposure;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> ExposureComboBox;
	TArray<TSharedPtr<FString>> ExposureOptions;
    TSharedPtr<FString> CurrentExposure;
	TSharedRef<SWidget> HandleExposureComboBoxGenerateWidget(const TSharedPtr<FString> InItem) const
	{
		return SNew(STextBlock).Text(FText::FromString(*InItem));
	}
	void HandleExposureSelectionChanged(const TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
	{
		CurrentExposure = NewSelection;
		Exposure = *CurrentExposure;
	}
	FText GetSelectedExposure() const
	{
		return FText::FromString(*CurrentExposure);
	}
	void InitExposure()
	{
		Exposure = "Public";
		ExposureOptions.Empty();
		ExposureOptions.Add(MakeShareable(new FString("Public")));
		ExposureOptions.Add(MakeShareable(new FString("Unlisted")));
		ExposureOptions.Add(MakeShareable(new FString("Private")));
		CurrentExposure = ExposureOptions[0];
	}
	// endregion

	// region expiration
	FString Expiration;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> ExpirationComboBox;
	TArray<TSharedPtr<FString>> ExpirationOptions;
	TSharedPtr<FString> CurrentExpiration;
	TSharedRef<SWidget> HandleExpirationComboBoxGenerateWidget(const TSharedPtr<FString> InItem) const
	{
		return SNew(STextBlock).Text(FText::FromString(*InItem));
	}
	void HandleExpirationSelectionChanged(const TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
	{
		CurrentExpiration = NewSelection;
		Expiration = *CurrentExpiration;
	}
	FText GetSelectedExpiration() const
	{
		return FText::FromString(*CurrentExpiration);
	}
	void InitExpiration()
	{
		Expiration = "Never";
		ExpirationOptions.Empty();
		ExpirationOptions.Add(MakeShareable(new FString("Never")));
		ExpirationOptions.Add(MakeShareable(new FString("1 hour")));
		ExpirationOptions.Add(MakeShareable(new FString("1 day")));
		ExpirationOptions.Add(MakeShareable(new FString("1 week")));
		CurrentExpiration = ExpirationOptions[0];
	}
	// endregion

	// region version
	FString UEVersion;
	TSharedPtr<SEditableTextBox> VersionEditableTextBox;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> UEVersionComboBox;
	TArray<TSharedPtr<FString>> UEVersionOptions;
	TSharedPtr<FString> CurrentUEVersion;
	TSharedRef<SWidget> HandleUEVersionComboBoxGenerateWidget(const TSharedPtr<FString> InItem) const
	{
		return SNew(STextBlock).Text(FText::FromString(*InItem));
	}
	void HandleUEVersionSelectionChanged(const TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
	{
		CurrentUEVersion = NewSelection;
		UEVersion = *CurrentUEVersion;
	}
	FText GetSelectedUEVersion() const
	{
		return FText::FromString(*CurrentUEVersion);
	}
	void InitUEVersion()
	{
		UEVersion = VERSION_STRINGIFY(ENGINE_MAJOR_VERSION) VERSION_TEXT(".") VERSION_STRINGIFY(ENGINE_MINOR_VERSION);
		UEVersionOptions.Empty();
		int currentUEVersionIndex = 0;
		for (int i = 0; i >= 0; --i)
		{
			FString tmpUEVersion = FString::Printf(TEXT("5.%d"), i);
			UEVersionOptions.Add(MakeShareable(new FString(tmpUEVersion)));

			if (tmpUEVersion == UEVersion)
			{
				currentUEVersionIndex = UEVersionOptions.Num() - 1;	
			}
		}
		for (int i = 27; i >= 0; --i)
		{
			FString tmpUEVersion = FString::Printf(TEXT("4.%d"), i);
			UEVersionOptions.Add(MakeShareable(new FString(tmpUEVersion)));

			if (tmpUEVersion == UEVersion)
			{
				currentUEVersionIndex = UEVersionOptions.Num() - 1;	
			}
		}
		CurrentUEVersion = UEVersionOptions[currentUEVersionIndex];
	}
	// endregion

	// region blueprint
	FString Blueprint;
	TSharedPtr<SMultiLineEditableTextBox> BlueprintMultiLineEditableTextBox;
	// endregion

	// region button + form
	TSharedPtr<SButton> CreateButton;
	FReply CreateFromSlate();
	FString CurrentError;
	FText GetErrorMessage() const
	{
		return FText::FromString(*CurrentError);
	}
	TFunction<void(FString, TSharedPtr<FJsonObject>)> OnAPISuccess = [&](FString hostname, TSharedPtr<FJsonObject> JSONObject)
	{
		FString key = JSONObject->GetStringField("key");

		TitleEditableTextBox->SetText(FText());
		BlueprintMultiLineEditableTextBox->SetText(FText());
		CreateButton->SetEnabled(true);

		FString date = FDateTime::Now().ToString(TEXT("%d-%m-%Y %H:%M:%S"));
		FString url = hostname + "/blueprint/" + key + "/";

		OnSuccess(date, url);
	};
	TFunction<void(FString)> OnAPIError = [&](FString errorMessage)
	{
		FString tmp = "An error occured: ";
		if (errorMessage == "api_key_empty")
		{
			tmp = tmp + " API Key is empty.";
		}
		else if (errorMessage == "api_key_incorrect")
		{
			tmp = tmp + " API Key is not recognized.";
		}
		else if (errorMessage == "required_title")
		{
			tmp = tmp + " title is required.";
		}
		else if (errorMessage == "invalid_blueprint")
		{
			tmp = tmp + " blueprint is invalid.";
		}
		else if (errorMessage == "invalid_exposure")
		{
			tmp = tmp + " exposure is invalid.";
		}
		else if (errorMessage == "invalid_expiration")
		{
			tmp = tmp + " expiration is invalid.";
		}
		else if (errorMessage == "invalid_version")
		{
			tmp = tmp + " version is invalid.";
		}
		else
		{
			tmp = tmp + " unknowed error message: " + errorMessage;
		}
		CurrentError = tmp;
		CreateButton->SetEnabled(true);
	};
	// endregion
};
