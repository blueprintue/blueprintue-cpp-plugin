#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Api.h"

class FToolBarBuilder;
class FMenuBuilder;

class FBlueprintUeModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	void PluginButtonClicked();

	Api& GetApi() { return Api; }

	static FBlueprintUeModule& Get()
	{
		static const FName ModuleName = "BlueprintUe";
		return FModuleManager::LoadModuleChecked<FBlueprintUeModule>(ModuleName);
	}
private:
	void RegisterMenus();
	void RegisterSettings();
	void UnregisterSettings();
	bool HandleSettingsSaved();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedPtr<class FUICommandList> PluginCommands;
	Api Api;
};
