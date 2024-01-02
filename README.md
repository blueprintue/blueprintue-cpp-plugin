# BlueprintUE C++ Plugin

This plugin allows you to send your blueprints on blueprintUE.com associated to your account.  
It is necessary to have an account in order to get the API key on your profile page.

Feel free to contribute.

Works on Unreal Engine `4.26` , `4.27` , `5.0` , `5.1` , `5.2` , `5.3` , `5.4`

## How to install it?
1. download zip file: https://github.com/blueprintue/blueprintue-cpp-plugin/archive/refs/heads/master.zip
2. go to your Unreal Project with your files explorer
3. create folder `Plugins` at the same level as your `.uproject`
4. inside folder `Plugins` create folder `BlueprintUe`
5. inside folder `BlueprintUe` extract files from zip
6. now you can open your Unreal Project, it will ask you to recompile the plugin

You can verify if plugin is loaded go to `Edit` > `Plugins` > filter with `blueprintue` > you need to have `Enabled` checked

## How to update UE 5.x Version list?
In file `Source/BlueprintUe/Public/SCreateBlueprint.h` line 107 you change `i` with `4` to have from `5.0` to `5.4`  
```c++
for (int i = 4; i >= 0; --i)
```