#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"

class FToolBarBuilder;
class FMenuBuilder;

class FBlueprintUeModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	void PluginButtonClicked();
	
private:

	void RegisterMenus();
	void RegisterSettings();
	void UnregisterSettings();
	bool HandleSettingsSaved();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedPtr<class FUICommandList> PluginCommands;
};
