#include "BlueprintUe.h"
#include "BlueprintUeStyle.h"
#include "BlueprintUeCommands.h"
#include "BlueprintUeSettings.h"
#include "LevelEditor.h"
#include "SMain.h"
#include "Settings/Public/ISettingsModule.h"
#include "Settings/Public/ISettingsContainer.h"
#include "Settings/Public/ISettingsSection.h"
#include "Widgets/Docking/SDockTab.h"
#include "ToolMenus.h"

static const FName BlueprintUeTabName("blueprintUE");

#define LOCTEXT_NAMESPACE "FBlueprintUeModule"

void FBlueprintUeModule::StartupModule()
{
	FBlueprintUeStyle::Initialize();
	FBlueprintUeStyle::ReloadTextures();

	FBlueprintUeCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FBlueprintUeCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FBlueprintUeModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBlueprintUeModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(BlueprintUeTabName, FOnSpawnTab::CreateRaw(this, &FBlueprintUeModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FBlueprintUeTabTitle", "blueprintUE"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	RegisterSettings();
}

void FBlueprintUeModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FBlueprintUeStyle::Shutdown();

	FBlueprintUeCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(BlueprintUeTabName);

	if (UObjectInitialized())
	{
		UnregisterSettings();
	}
}

void FBlueprintUeModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(BlueprintUeTabName);
}

void FBlueprintUeModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	// region LevelEditor
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FBlueprintUeCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBlueprintUeCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
	// endregion

	// region AssetEditor -> BlueprintEditor
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("AssetEditor.BlueprintEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("BlueprintEditor");
			Section.AddMenuEntryWithCommandList(FBlueprintUeCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("AssetEditor.BlueprintEditor.ToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Debugging");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBlueprintUeCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
	// endregion

	// region AssetEditor -> MaterialEditor
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("AssetEditor.MaterialEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("MaterialEditor");
			Section.AddMenuEntryWithCommandList(FBlueprintUeCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("AssetEditor.MaterialEditor.ToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Graph");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBlueprintUeCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
	// endregion
}

TSharedRef<SDockTab> FBlueprintUeModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
	.TabRole(ETabRole::NomadTab)
	[
		SNew(SMain)
	];
}

void FBlueprintUeModule::RegisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("blueprintUE",
			LOCTEXT("RuntimeWDCategoryName", "blueprintUE"),
			LOCTEXT("RuntimeWDCategoryDescription", "blueprintUE Category"));

		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "blueprintUE",
			LOCTEXT("RuntimeGeneralSettingsName", "blueprintUE"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Configure the blueprintUE plugin."),
			GetMutableDefault<UBlueprintUeSettings>()
		);

		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FBlueprintUeModule::HandleSettingsSaved);
		}
	}
}

void FBlueprintUeModule::UnregisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "blueprintUE");
	}
}

bool FBlueprintUeModule::HandleSettingsSaved()
{
	UBlueprintUeSettings* Settings = GetMutableDefault<UBlueprintUeSettings>();
	bool ResaveSettings = false;

	Settings->SaveConfig();

	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBlueprintUeModule, BlueprintUe)