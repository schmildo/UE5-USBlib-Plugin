// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "M:\UnrealEngineProjects\USB\Plugins\ASchmildosPlugin\ThirdParty\USBLIB\include\libusb.h"
#include "LIBUSBwrapper_CountUSB.h"
#include "LIBUSBwrapper_init.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ASchmildosPluginBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/


UCLASS()
class UASchmildosPluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	public:


	UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin", meta = (ReturnDisplayName = "Number of USB Devices"))
		int32 CountConnectedUSBDevices(ULIBUSBwrapper_init*& InContext);
	UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin")
	//	static bool InitializeLibUsbContext(ULIBUSBwrapper_init*& OutContext);
		static ULIBUSBwrapper_init* InitializeLibUsbContext();

	UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin", meta = (ReturnDisplayName = "bContextExited"))
		static void ExitLibUsbContext(ULIBUSBwrapper_init*& InContext);


	//	UFUNCTION(BlueprintCallable, Category = "MyPlugin")
	//static ULibUsbContext* InitializeLibUsbContext();

	private:
	
};
