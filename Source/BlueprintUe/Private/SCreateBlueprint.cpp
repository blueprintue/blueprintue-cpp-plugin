#include "SCreateBlueprint.h"

#include "Api.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "BlueprintUe.h"

void SCreateBlueprint::Construct( const FArguments& InArgs )
{
	// values from settings
	OnSuccess = InArgs._OnSuccess;
	
	InitExposure();
	InitExpiration();
	InitUEVersion();

	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			SNew(SVerticalBox)
			// region header
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				 SNew(STextBlock)
				 .Text(FText::FromString("Create Blueprint"))
				 .Font(FCoreStyle::GetDefaultFontStyle("Regular", 14))
			]
			// endregion
			// region title
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
					.Text(FText::FromString("Title"))
					.MinDesiredWidth(70)
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(1.0f)
				[
					SAssignNew(TitleEditableTextBox, SEditableTextBox)
					.OnTextCommitted_Lambda([this](const FText& Text, ETextCommit::Type CommitType)
					{
						Title = Text.ToString();
						if (Title.Len() < 1)
						{
							TitleEditableTextBox->SetError("Title is required");
						}
						else
						{
							TitleEditableTextBox->SetError(FString());
							Title = Text.ToString();
						}
					})
					.OnTextChanged_Lambda([this](const FText& Text)
					{
						Title = Text.ToString();
						if (Title.Len() < 1)
						{
							TitleEditableTextBox->SetError("Title is required");
						}
						else
						{
							TitleEditableTextBox->SetError(FString());
							Title = Text.ToString();
						}
					})
				]
			]
			// endregion
			// region exposure
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
					.Text(FText::FromString("Exposure"))
					.MinDesiredWidth(70)
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(1.0f)
				[
					SAssignNew(ExposureComboBox, SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&ExposureOptions)
					.InitiallySelectedItem(CurrentExposure)
					.OnGenerateWidget(this, &SCreateBlueprint::HandleExposureComboBoxGenerateWidget)
					.OnSelectionChanged(this, &SCreateBlueprint::HandleExposureSelectionChanged)
					[
						SNew(STextBlock)
						.Text(this, &SCreateBlueprint::GetSelectedExposure)
					]
				]
			]
			// endregion
			// region expiration
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
					.Text(FText::FromString("Expiration"))
					.MinDesiredWidth(70)
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(1.0f)
				[
					SAssignNew(ExpirationComboBox, SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&ExpirationOptions)
					.InitiallySelectedItem(CurrentExpiration)
					.OnGenerateWidget(this, &SCreateBlueprint::HandleExpirationComboBoxGenerateWidget)
					.OnSelectionChanged(this, &SCreateBlueprint::HandleExpirationSelectionChanged)
					[
						SNew(STextBlock)
						.Text(this, &SCreateBlueprint::GetSelectedExpiration)
					]
				]
			]
			// endregion
			// region expiration
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
					.Text(FText::FromString("UE Version"))
					.MinDesiredWidth(70)
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(1.0f)
				[
					SAssignNew(UEVersionComboBox, SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&UEVersionOptions)
					.InitiallySelectedItem(CurrentUEVersion)
					.OnGenerateWidget(this, &SCreateBlueprint::HandleUEVersionComboBoxGenerateWidget)
					.OnSelectionChanged(this, &SCreateBlueprint::HandleUEVersionSelectionChanged)
					[
						SNew(STextBlock)
						.Text(this, &SCreateBlueprint::GetSelectedUEVersion)
					]
				]
			]
			// endregion
			// region blueprint
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.MaxHeight(150.0f)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoWidth()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Blueprint"))
					.MinDesiredWidth(70)
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(1.0f)
				[
					SAssignNew(BlueprintMultiLineEditableTextBox, SMultiLineEditableTextBox)
					.AllowMultiLine(true)
					.OnTextCommitted_Lambda([this](const FText& Text, ETextCommit::Type CommitType)
					{
						Blueprint = Text.ToString();
						if (Blueprint.Len() < 1)
						{
							BlueprintMultiLineEditableTextBox->SetError("Blueprint is required");
						}
						else
						{
							BlueprintMultiLineEditableTextBox->SetError(FString());
							Blueprint = Text.ToString();
						}
					})
					.OnTextChanged_Lambda([this](const FText& Text)
					{
						Blueprint = Text.ToString();
						if (Blueprint.Len() < 1)
						{
							BlueprintMultiLineEditableTextBox->SetError("Blueprint is required");
						}
						else
						{
							BlueprintMultiLineEditableTextBox->SetError(FString());
							Blueprint = Text.ToString();
						}
					})
				]
			]
			// endregion
			// region header
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				SNew(STextBlock)
				.Text(this, &SCreateBlueprint::GetErrorMessage)
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 14))
				.ColorAndOpacity(FLinearColor( 1.0f, 0.0f, 0.0f ))
			]
			// endregion
			// region button
			+ SVerticalBox::Slot()
			.VAlign(VAlign_Center)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				SAssignNew(CreateButton, SButton)
				.HAlign(HAlign_Center)
				.Text(FText::FromString("Create"))
				.OnClicked(this, &SCreateBlueprint::CreateFromSlate)
			]
			// endregion
		]
	];
}

FReply SCreateBlueprint::CreateFromSlate()
{
	Title = Title.TrimStartAndEnd();
	Blueprint = Blueprint.TrimStartAndEnd();

	TitleEditableTextBox->SetText(FText::FromString(Title));
	BlueprintMultiLineEditableTextBox->SetText(FText::FromString(Blueprint));
	
	if (Title.Len() < 1 || Blueprint.Len() < 1) {
		if (Title.Len() < 1)
		{
			TitleEditableTextBox->SetError("Title is required");	
		}
		if (Blueprint.Len() < 1)
		{
			BlueprintMultiLineEditableTextBox->SetError("Blueprint is required");	
		}

		return FReply::Handled();
	}

	CurrentError = "";
	CreateButton->SetEnabled(false);

	Api& Api = FBlueprintUeModule::Get().GetApi();
	Api.CreateBlueprint(OnAPISuccess, OnAPIError, Title, *CurrentExposure, *CurrentExpiration, *CurrentUEVersion, Blueprint);

	return FReply::Handled();
}
