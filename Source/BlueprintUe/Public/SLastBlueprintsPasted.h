#pragma once

#include "PastedBlueprints.h"
#include "SCreateBlueprint.h"

class SLastBlueprintsPasted : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SLastBlueprintsPasted ) {}
	SLATE_END_ARGS()

	void Construct( const FArguments& InArgs );
	void AddPastedBlueprints(const FString& InDate, const FString& InURL)
	{
		ListLastBlueprintsPasted.Add(MakeShareable(new PastedBlueprints(InDate, InURL)));
	}

private:
	TArray< TSharedRef< PastedBlueprints > > ListLastBlueprintsPasted;
	void InitList()
	{
		ListLastBlueprintsPasted.Empty();
	}
	TSharedRef<ITableRow> MakeListViewWidget(TSharedRef<PastedBlueprints> Item, const TSharedRef<STableViewBase>& OwnerTable)
	{
		return
			SNew(STableRow< TSharedRef<PastedBlueprints> >, OwnerTable)
			.Padding(4.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.AutoWidth()
				.Padding(4.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString(Item.Get().Date))
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				.FillWidth(1.0f)
				.Padding(4.0f, 0.0f)
				[
					SNew(SEditableTextBox)
					.Padding(4.0f)
					.IsReadOnly(true)
					.Text(FText::FromString(Item.Get().URL))
				]
			];
	}
};
