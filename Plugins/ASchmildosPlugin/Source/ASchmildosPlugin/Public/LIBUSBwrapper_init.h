// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "M:\UnrealEngineProjects\USB\Plugins\ASchmildosPlugin\ThirdParty\USBLIB\include\libusb.h"
#include "LIBUSBwrapper_init.generated.h"


// Declare the struct to hold device information
USTRUCT(BlueprintType)
struct FMyLibusbDevice {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 DeviceId;

    UPROPERTY(BlueprintReadOnly)
    FString DeviceName;

    // Other properties as needed
};


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ASCHMILDOSPLUGIN_API ULIBUSBwrapper_init : public UObject
{
	GENERATED_BODY()
	public:
        ULIBUSBwrapper_init();
		libusb_context* GetmContext();
		bool SetmContext(libusb_context* IN_ContextObject);




		bool initialize();
        UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Init")
			void Exit();



		UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|count",meta = (ReturnDisplayName = "NumDevices"))
			int32 ReallyCountConnectedDevices();
	    /**
         * Returns a list of connected Libusb devices.
         * @return A list of FMyLibusbDevice structs representing the connected devices.
         */
        UFUNCTION(BlueprintCallable, Category = "MyPlugin|Libusb")
        static TArray<FMyLibusbDevice> GetDeviceList();
		

private:
	libusb_device** m_deviceList;
	libusb_context* m_ContextObject;

};






/*
* USTRUCT(BlueprintType)
struct FDeviceList
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LibUSB")
    TArray<FString> DeviceNames;
};

UFUNCTION(BlueprintCallable, Category = "LibUSB")
static FDeviceList GetDeviceList();
*/