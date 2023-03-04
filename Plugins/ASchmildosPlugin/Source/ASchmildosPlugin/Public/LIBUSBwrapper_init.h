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
        //UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Init")
        void Exit();

		UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|count")
		int32 ReallyCountConnectedDevices(ULIBUSBwrapper_init*& InContext);

		libusb_context* m_ContextObject;
private:
    

};


