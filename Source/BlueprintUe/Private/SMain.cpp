#include "SMain.h"

#include "BlueprintUeSettings.h"
#include "SCreateBlueprint.h"
#include "SLastBlueprintsPasted.h"
#include "SSettings.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SWidgetSwitcher.h"

void SMain::Construct( const FArguments& InArgs )
{
	const UBlueprintUeSettings* Settings = GetMutableDefault<UBlueprintUeSettings>();

	if (Settings->ApiKey.Len() == 0 || Settings->Hostname.Len() == 0)
	{
		ChildSlot
		[
			SNew(SSettings)
			.ApiKey(Settings->ApiKey)
			.Hostname(Settings->Hostname)
			.OnSaveSuccess_Lambda([this]
			{
				ChildSlot.DetachWidget();

				MainMenu();
			})
		];
	}
	else
	{
		MainMenu();
	}
}

void SMain::MainMenu()
{
	ChildSlot
	[
		SNew(SVerticalBox)
		// region header
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Top)
		.AutoHeight()
		.Padding(0.0f, 4.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				SNew(SButton)
				.Text(FText::FromString("Create"))
				.HAlign(HAlign_Center)
				.OnClicked_Lambda([this]()
				{
					TabIndex = 0;
					return FReply::Handled();
				})
			]
			+ SHorizontalBox::Slot()
			[
				SNew(SButton)
				.Text(FText::FromString("Last Blueprints Pasted"))
				.HAlign(HAlign_Center)
				.OnClicked_Lambda([this]()
				{
					TabIndex = 1;
					return FReply::Handled();
				})
			]
		]
		// endregion
		// region widgets
		+ SVerticalBox::Slot()
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.AutoHeight()
				.Padding(0.0f, 4.0f)
				[
					SNew(SWidgetSwitcher)
					.WidgetIndex(this, &SMain::GetCurrentTabIndex)
					+ SWidgetSwitcher::Slot()
					[
						SAssignNew(SlateCreateBlueprint, SCreateBlueprint)
						.OnSuccess([&](const FString& InDate, const FString& InURL)
						{
							TabIndex = 1;
							SlateLastBlueprintsPasted->AddPastedBlueprints(InDate, InURL);
						})
					]
					+ SWidgetSwitcher::Slot()
					[
						SAssignNew(SlateLastBlueprintsPasted, SLastBlueprintsPasted)
					]
				]
			]
		]
		// endregion
	];
}
