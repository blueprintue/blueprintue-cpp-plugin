#pragma once

class SSettings : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SSettings ) {}
		SLATE_ARGUMENT( FString, ApiKey )
		SLATE_ARGUMENT( FString, Hostname )
		SLATE_EVENT(FSimpleDelegate, OnSaveSuccess)
	SLATE_END_ARGS()

	void Construct( const FArguments& InArgs );

private:

	FReply SaveSettingsFromSlate();
	void RemoveSlashFromHostname();

	FString ApiKey;
	FString Hostname;

	TSharedPtr<SEditableTextBox> ApiKeyEditableTextBox;
	TSharedPtr<SEditableTextBox> HostnameEditableTextBox;

	FSimpleDelegate OnSaveSuccess;
};
