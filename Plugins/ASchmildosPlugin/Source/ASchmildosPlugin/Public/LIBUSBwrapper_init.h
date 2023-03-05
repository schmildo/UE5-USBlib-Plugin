// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Misc/Variant.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "M:\UnrealEngineProjects\USB\Plugins\ASchmildosPlugin\ThirdParty\USBLIB\include\libusb.h"
#include "LIBUSBwrapper_init.generated.h"



    USTRUCT(BlueprintType)
    struct FDeviceVID
    {
        GENERATED_BODY()

        UPROPERTY(BlueprintReadOnly)
        int32 IntVID;

        UPROPERTY(BlueprintReadOnly)
        FString StringVID;
    };

// Declare the class to hold device information
UCLASS(BlueprintType)
class UMyLibusbDevice : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    int32 DeviceId;

    UPROPERTY(BlueprintReadOnly)
    int32 VendorId;

    UPROPERTY(BlueprintReadOnly)
    int32 ProductId;

    UPROPERTY(BlueprintReadOnly)
    FString DeviceName;

    // Other properties as needed



    UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Libusb")
    FDeviceVID GetDeviceVID() const;
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
    /**
     * Returns a list of connected Libusb devices.
     * @return A list of FMyLibusbDevice structs representing the connected devices.
     */
    UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Libusb")
    static TArray<UMyLibusbDevice*> GetDeviceList();
		

private:
	libusb_device** m_deviceList;
	libusb_context* m_ContextObject;

};


FDeviceVID UMyLibusbDevice::GetDeviceVID() const
{
    FString VIDString = TEXT("0x") + FString::Printf(TEXT("%04x"), this->VendorId);
    FDeviceVID VID;
    VID.IntVID = this->VendorId;
    VID.StringVID = VIDString;
    return VID;
}


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