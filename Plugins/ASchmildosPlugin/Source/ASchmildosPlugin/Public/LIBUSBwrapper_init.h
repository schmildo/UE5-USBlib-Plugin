// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "M:\UnrealEngineProjects\USB\Plugins\ASchmildosPlugin\ThirdParty\USBLIB\include\libusb.h"
#include "LIBUSBwrapper_init.generated.h"



    //Deviceand /or Interface Class codes * /
UENUM(BlueprintType)
    enum class UMylibusb_class_code :uint8
{


    /** In the context of a \ref libusb_device_descriptor "device descriptor",
        * this bDeviceClass value indicates that each interface specifies its
        * own class information and all interfaces operate independently.
        */
    LIBUSB_CLASS_PER_INTERFACE = 0x00,

    /** Audio class */
    LIBUSB_CLASS_AUDIO = 0x01,

    /** Communications class */
    LIBUSB_CLASS_COMM = 0x02,

    /** Human Interface Device class */
    LIBUSB_CLASS_HID = 0x03,

    /** Physical */
    LIBUSB_CLASS_PHYSICAL = 0x05,

    /** Image class */
    LIBUSB_CLASS_IMAGE = 0x06,
    LIBUSB_CLASS_PTP = 0x06, /* legacy name from libusb-0.1 usb.h */

    /** Printer class */
    LIBUSB_CLASS_PRINTER = 0x07,

    /** Mass storage class */
    LIBUSB_CLASS_MASS_STORAGE = 0x08,

    /** Hub class */
    LIBUSB_CLASS_HUB = 0x09,

    /** Data class */
    LIBUSB_CLASS_DATA = 0x0a,

    /** Smart Card */
    LIBUSB_CLASS_SMART_CARD = 0x0b,

    /** Content Security */
    LIBUSB_CLASS_CONTENT_SECURITY = 0x0d,

    /** Video */
    LIBUSB_CLASS_VIDEO = 0x0e,

    /** Personal Healthcare */
    LIBUSB_CLASS_PERSONAL_HEALTHCARE = 0x0f,

    /** Diagnostic Device */
    LIBUSB_CLASS_DIAGNOSTIC_DEVICE = 0xdc,

    /** Wireless class */
    LIBUSB_CLASS_WIRELESS = 0xe0,

    /** Miscellaneous class */
    LIBUSB_CLASS_MISCELLANEOUS = 0xef,

    /** Application class */
    LIBUSB_CLASS_APPLICATION = 0xfe,

    /** Class is vendor-specific */
    LIBUSB_CLASS_VENDOR_SPEC = 0xff
};
USTRUCT(BlueprintType)
    struct ASCHMILDOSPLUGIN_API FDeviceVID
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 IntVID;

    UPROPERTY(BlueprintReadOnly)
    FString StringVID;
};




// Declare the class to hold device information
UCLASS(BlueprintType)
class ASCHMILDOSPLUGIN_API UMyLibusbDevice : public UObject
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

    UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Libusb")
        static UMylibusb_device_descriptor* GetDeviceDescriptor(UMyLibusbDevice* IN_Device);

    libusb_device* GetActualD()const;
    libusb_device* m_ThisDevice;
    libusb_context* m_ContextObject;
    libusb_device_descriptor* m_ThisDeviceDescriptor;
    ULIBUSBwrapper_init* m_Wrapper;
};



UCLASS(Blueprintable, BlueprintType)
    class ASCHMILDOSPLUGIN_API UMylibusb_device_descriptor : public UObject
{
    GENERATED_BODY()

    public:
        UMylibusb_device_descriptor();

        // Size of this descriptor (in bytes)
        UPROPERTY(BlueprintReadOnly)
            uint8  bLength;

        // Descriptor type. Will have value
         // \ref libusb_descriptor_type::LIBUSB_DT_DEVICE LIBUSB_DT_DEVICE in this
         // context.
        UPROPERTY(BlueprintReadOnly)
            uint8  bDescriptorType;

        // USB specification release number in binary-coded decimal. A value of
         // 0x0200 indicates USB 2.0, 0x0110 indicates USB 1.1, etc. 
        UPROPERTY(BlueprintReadOnly)
            int32 bcdUSB;

        // USB-IF class code for the device. See \ref libusb_class_code. 
        UPROPERTY(BlueprintReadOnly)
            UMylibusb_class_code bDeviceClass;
            //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
            //TEnumAsByte<UMylibusb_class_code> bDeviceClass;
            //uint8  bDeviceClass;


        //USB-IF subclass code for the device, qualified by the bDeviceClass
         // value 
        UPROPERTY(BlueprintReadOnly)
            uint8  bDeviceSubClass;

        // USB-IF protocol code for the device, qualified by the bDeviceClass and
         // bDeviceSubClass values 
        UPROPERTY(BlueprintReadOnly)
            uint8  bDeviceProtocol;

       //Maximum packet size for endpoint 0
        UPROPERTY(BlueprintReadOnly)
            uint8  bMaxPacketSize0;

       //USB-IF vendor ID
        UPROPERTY(BlueprintReadOnly)
            int32 idVendor;

       //USB-IF product ID
        UPROPERTY(BlueprintReadOnly)
            int32 idProduct;

       //Device release number in binary-coded decimal
        UPROPERTY(BlueprintReadOnly)
            int32 bcdDevice;

       //Index of string descriptor describing manufacturer
        UPROPERTY(BlueprintReadOnly)
            uint8  iManufacturer;

       //Index of string descriptor describing product
        UPROPERTY(BlueprintReadOnly)
            uint8  iProduct;

       //Index of string descriptor containing device serial number
        UPROPERTY(BlueprintReadOnly)
            uint8  iSerialNumber;

       //Number of possible configurations
        UPROPERTY(BlueprintReadOnly)
            uint8  bNumConfigurations;

        UFUNCTION(BlueprintPure, Category = "SchmildosPlugin|Libusb")
            FString getCode();

    private:
    };


// Declare the class to hold devicehandle information
UCLASS(BlueprintType)
class ASCHMILDOSPLUGIN_API UMyLibusbDeviceHandle : public UMyLibusbDevice
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Libusb",meta = (ReturnDisplayName = "DeviceHandle"))
        static UMyLibusbDeviceHandle* OpenThisDevice(UMyLibusbDevice* IN_Device);


private:
    libusb_device_handle* m_DeviceHandle;
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
		UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Libusb",meta = (ReturnDisplayName = "NumDevices"))
			int32 CountDevices();
        UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Libusb", meta = (ReturnDisplayName = "OUT_DeviceList"))
            TArray<UMyLibusbDevice*> GetDeviceList();
        UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin|Libusb")
            static void PrintDeviceList(TArray<UMyLibusbDevice*> IN_DeviceList);
        libusb_context* m_ContextObject;
    private:
	    //libusb_device** m_deviceList;
        TArray<UMyLibusbDevice*> m_DeviceList;
	    
        libusb_device** m_Devices;

};

