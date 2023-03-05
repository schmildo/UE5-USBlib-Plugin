// Fill out your copyright notice in the Description page of Project Settings.


#include "LIBUSBwrapper_init.h"



ULIBUSBwrapper_init::ULIBUSBwrapper_init()
{
    m_ContextObject = nullptr;
}

bool ULIBUSBwrapper_init::initialize()
{
    int result = libusb_init(&m_ContextObject);
    if (result != LIBUSB_SUCCESS)
    {
        return false;
    }

    return true;
}




void ULIBUSBwrapper_init::Exit()
{
    if (m_ContextObject!=nullptr)
    {
        libusb_exit(m_ContextObject);
        m_ContextObject = nullptr;
    }
}

int32 ULIBUSBwrapper_init::ReallyCountConnectedDevices()
{
    int32 deviceCount = 0;

    // Get the number of connected USB devices
    m_deviceList = nullptr;
    deviceCount = libusb_get_device_list(m_ContextObject, &m_deviceList);
    //deviceCount = 42;
    if (deviceCount < 0) {
        // handle error
    }

    for (int i = 0; i < deviceCount; i++) {
        libusb_device* device = m_deviceList[i];
        // do something with the device
    }

    libusb_free_device_list(m_deviceList, 1);
    //libusb_exit( InContext->m_ContextObject);

    return deviceCount;
}

TArray<FMyLibusbDevice> ULIBUSBwrapper_init::GetDeviceList()
{

  
        TArray<FMyLibusbDevice> DeviceList;

        // Initialize Libusb context
        libusb_context* Context;
        if (libusb_init(&Context) != 0)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to initialize Libusb context"));
            return DeviceList;
        }

        // Get list of devices
        libusb_device** Devices;
        ssize_t Count = libusb_get_device_list(Context, &Devices);
        if (Count < 0)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get list of Libusb devices"));
            libusb_exit(Context);
            return DeviceList;
        }

        // Iterate over devices and populate device list
        for (int32 i = 0; i < Count; ++i)
        {
            libusb_device* Device = Devices[i];

            // Get device descriptor
            libusb_device_descriptor Descriptor;
            if (libusb_get_device_descriptor(Device, &Descriptor) != 0)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to get descriptor for Libusb device"));
                continue;
            }

            // Populate device info struct
            FMyLibusbDevice DeviceInfo;
            DeviceInfo.DeviceId = Descriptor.idVendor * 0x10000 + Descriptor.idProduct;
            DeviceInfo.DeviceName = FString::Printf(TEXT("Vendor ID: %04x, Product ID: %04x"), Descriptor.idVendor, Descriptor.idProduct);

            // Add device info to list
            DeviceList.Add(DeviceInfo);
        }

        // Free list of devices
        libusb_free_device_list(Devices, 1);

        // Exit Libusb context
        libusb_exit(Context);

        return DeviceList;
    
}

libusb_context* ULIBUSBwrapper_init::GetmContext()
{
    return m_ContextObject;
}


bool ULIBUSBwrapper_init::SetmContext(libusb_context* IN_ContextObject)
{
    m_ContextObject = IN_ContextObject;
    return true;
}
