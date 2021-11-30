#include "SSettings.h"

#include "BlueprintUeSettings.h"
#include "Widgets/Layout/SScrollBox.h"

void SSettings::Construct( const FArguments& InArgs )
{
	// values from settings
	ApiKey = InArgs._ApiKey;
	Hostname = InArgs._Hostname;
	OnSaveSuccess = InArgs._OnSaveSuccess;

	if (Hostname == "")
	{
		Hostname = "https://blueprintue.com";
	}

	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			SNew(SVerticalBox)
			// region title
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				 SNew(STextBlock)
				 .Text(FText::FromString("Settings"))
				 .Font(FCoreStyle::GetDefaultFontStyle("Regular", 14))
			]
			// endregion
			// region description
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Top)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString("You can retrieve your API key in your profile on blueprintUE.com or your private instance."))
				.AutoWrapText(true)
			]
			// endregion
			// region api
			+ SVerticalBox::Slot().HAlign(HAlign_Fill)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::FromString("API Key"))
					.MinDesiredWidth(70)
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(1.0f)
				[
					SAssignNew(ApiKeyEditableTextBox, SEditableTextBox)
					.Text(FText::FromString(ApiKey))
					.IsPassword(true)
					.OnTextCommitted_Lambda([this](const FText& Text, ETextCommit::Type CommitType)
					{
						ApiKey = Text.ToString();
						if (ApiKey.Len() < 1)
						{
							ApiKeyEditableTextBox->SetError("ApiKey is required");
						}
						else
						{
							ApiKeyEditableTextBox->SetError(FString());
							ApiKey = Text.ToString();
						}
					})
					.OnTextChanged_Lambda([this](const FText& Text)
					{
						ApiKey = Text.ToString();
						if (ApiKey.Len() < 1)
						{
							ApiKeyEditableTextBox->SetError("ApiKey is required");
						}
						else
						{
							ApiKeyEditableTextBox->SetError(FString());
							ApiKey = Text.ToString();
						}
					})
				]
			]
			// endregion
			// region hostname
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Hostname"))
					.MinDesiredWidth(70)
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(1.0f)
				[
					SAssignNew(HostnameEditableTextBox, SEditableTextBox)
					.Text(FText::FromString(Hostname))
					.OnTextCommitted_Lambda([this](const FText& Text, ETextCommit::Type CommitType)
					{
						Hostname = Text.ToString();
						if (Hostname.Len() < 1)
						{
							HostnameEditableTextBox->SetError("Hostname is required");
						}
						else
						{
							HostnameEditableTextBox->SetError(FString());
							Hostname = Text.ToString();
						}
					})
					.OnTextChanged_Lambda([this](const FText& Text)
					{
						Hostname = Text.ToString();
						if (Hostname.Len() < 1)
						{
							HostnameEditableTextBox->SetError("Hostname is required");
						}
						else
						{
							HostnameEditableTextBox->SetError(FString());
							Hostname = Text.ToString();
						}
					})
				]
			]
			// endregion
			// region button
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Center)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				SNew(SButton)
				.HAlign(HAlign_Center)
				.Text(FText::FromString("Save"))
				.OnClicked(this, &SSettings::SaveSettingsFromSlate)
			]
			// endregion
		]
	];
}

FReply SSettings::SaveSettingsFromSlate()
{
	ApiKey = ApiKey.TrimStartAndEnd();
	Hostname = Hostname.TrimStartAndEnd();

	ApiKeyEditableTextBox->SetText(FText::FromString(ApiKey));
	HostnameEditableTextBox->SetText(FText::FromString(Hostname));
	
	if (ApiKey.Len() < 1 || Hostname.Len() < 1) {
		if (ApiKey.Len() < 1)
		{
			ApiKeyEditableTextBox->SetError("ApiKey is required");	
		}
		if (Hostname.Len() < 1)
		{
			HostnameEditableTextBox->SetError("Hostname is required");	
		}

		return FReply::Handled();
	}

	RemoveSlashFromHostname();

	if (Hostname.Len() < 1)
	{
		HostnameEditableTextBox->SetError("Hostname is required");
		return FReply::Handled();
	}

	UBlueprintUeSettings* Settings = GetMutableDefault<UBlueprintUeSettings>();
	Settings->ApiKey = ApiKey;
	Settings->Hostname = Hostname;
	Settings->SaveConfig();

	OnSaveSuccess.ExecuteIfBound();

	return FReply::Handled();
}

void SSettings::RemoveSlashFromHostname()
{
	FString lastChar = Hostname.Right(1);
	if (lastChar == "/")
	{
		Hostname = Hostname.LeftChop(1);
		HostnameEditableTextBox->SetText(FText::FromString(Hostname));

		RemoveSlashFromHostname();
	}
}