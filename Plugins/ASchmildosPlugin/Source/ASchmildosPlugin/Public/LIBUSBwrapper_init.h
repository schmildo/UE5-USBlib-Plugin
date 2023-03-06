// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

    USTRUCT(BlueprintType)
    struct FMylibusb_device_descriptor {

        GENERATED_BODY()

        /** Size of this descriptor (in bytes) */
        UPROPERTY(BlueprintReadOnly)
        uint8  bLength;

        /** Descriptor type. Will have value
         * \ref libusb_descriptor_type::LIBUSB_DT_DEVICE LIBUSB_DT_DEVICE in this
         * context. */
        UPROPERTY(BlueprintReadOnly)
        uint8  bDescriptorType;

        /** USB specification release number in binary-coded decimal. A value of
         * 0x0200 indicates USB 2.0, 0x0110 indicates USB 1.1, etc. */
        UPROPERTY(BlueprintReadOnly)
        int32 bcdUSB;

        /** USB-IF class code for the device. See \ref libusb_class_code. */
        UPROPERTY(BlueprintReadOnly)
        uint8  bDeviceClass;

        /** USB-IF subclass code for the device, qualified by the bDeviceClass
         * value */
        UPROPERTY(BlueprintReadOnly)
        uint8  bDeviceSubClass;

        /** USB-IF protocol code for the device, qualified by the bDeviceClass and
         * bDeviceSubClass values */
        UPROPERTY(BlueprintReadOnly)
        uint8  bDeviceProtocol;

        /** Maximum packet size for endpoint 0 */
        UPROPERTY(BlueprintReadOnly)
        uint8  bMaxPacketSize0;

        /** USB-IF vendor ID */
        UPROPERTY(BlueprintReadOnly)
        int32 idVendor;

        /** USB-IF product ID */
        UPROPERTY(BlueprintReadOnly)
        int32 idProduct;

        /** Device release number in binary-coded decimal */
        UPROPERTY(BlueprintReadOnly)
        int32 bcdDevice;

        /** Index of string descriptor describing manufacturer */
        UPROPERTY(BlueprintReadOnly)
        uint8  iManufacturer;

        /** Index of string descriptor describing product */
        UPROPERTY(BlueprintReadOnly)
        uint8  iProduct;

        /** Index of string descriptor containing device serial number */
        UPROPERTY(BlueprintReadOnly)
        uint8  iSerialNumber;

        /** Number of possible configurations */
        UPROPERTY(BlueprintReadOnly)
        uint8  bNumConfigurations;
    };


    /*
    USTRUCT(BlueprintType)
    struct Flibusb_config_descriptor
    {
        GENERATED_BODY()

        UPROPERTY(BlueprintReadOnly)
        int32 someshit;

        UPROPERTY(BlueprintReadOnly)
        FString othershit;
    };

    */

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

    UFUNCTION(BlueprintPure, Category = "SchmildosPlugin|Libusb")
        FDeviceVID GetDeviceVID() const;
    UFUNCTION(BlueprintPure, Category = "SchmildosPlugin|Libusb")
        FString GetDeviceVID_AsString() const;
    UFUNCTION(BlueprintPure, Category = "SchmildosPlugin|Libusb")
    FMylibusb_device_descriptor GetDeviceDescriptor() const;

    libusb_device* GetActualD()const;
    libusb_device* m_ThisDevice;
};


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

    UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Libusb")
    static TArray<UMyLibusbDevice*> GetDeviceList();
		

private:
	libusb_device** m_deviceList;
	libusb_context* m_ContextObject;

};

