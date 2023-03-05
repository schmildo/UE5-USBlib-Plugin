// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "M:\UnrealEngineProjects\USB\Plugins\ASchmildosPlugin\ThirdParty\USBLIB\include\libusb.h"
#include "LIBUSBwrapper_init.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ASCHMILDOSPLUGIN_API ULIBUSBwrapper_init : public UObject
{
	GENERATED_BODY()
	public:
        ULIBUSBwrapper_init();
	    //UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Init")
		bool initialize();
        UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Init") //, meta = (HidePin = "InContext") -- ,meta = (CustomThunk)
        //static void Exit(UPARAM(ref) ULIBUSBwrapper_init*& IN_Context);
			void Exit();

		/*
		UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Init") 
		static void Exit(UPARAM(ref) ULIBUSBwrapper_init*& IN_Context);
		*/

		UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|count",meta = (ReturnDisplayName = "NumDevices"))
		int32 ReallyCountConnectedDevices();
		//UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|getsetstuff")
			libusb_context* GetmContext();
			//UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|getsetstuff")
			bool SetmContext(libusb_context* IN_ContextObject);

private:
	libusb_device** m_deviceList;
	libusb_context* m_ContextObject;

};


