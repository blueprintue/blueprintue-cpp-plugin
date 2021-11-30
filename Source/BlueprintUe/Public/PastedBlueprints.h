#pragma once

struct PastedBlueprints
{
	FString Date;
	FString URL;

	PastedBlueprints()
	: Date(""), URL("")
	{}
	
	PastedBlueprints(const FString& InDate, const FString& InURL)
	: Date(InDate), URL(InURL)
	{}
};
