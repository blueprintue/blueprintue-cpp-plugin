#include "SLastBlueprintsPasted.h"

#include "Widgets/Layout/SScrollBox.h"

void SLastBlueprintsPasted::Construct( const FArguments& InArgs )
{
	InitList();

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
				.Text(FText::FromString("Last Blueprints Pasted"))
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 14))
			]
			// endregion
			// region liste
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			.AutoHeight()
			.Padding(0.0f, 4.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.FillWidth(1.0f)
				[
					SNew(SListView<TSharedRef<struct PastedBlueprints>>)
					.ListItemsSource(&ListLastBlueprintsPasted)
					.SelectionMode(ESelectionMode::None)
					.OnGenerateRow(this, &SLastBlueprintsPasted::MakeListViewWidget)
				]
			]
			// endregion
		]
	];
}