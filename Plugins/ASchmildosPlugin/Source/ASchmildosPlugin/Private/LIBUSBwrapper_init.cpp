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
    libusb_exit(m_ContextObject);
}

int32 ULIBUSBwrapper_init::ReallyCountConnectedDevices(ULIBUSBwrapper_init*& InContext)
{
    int32 deviceCount = 0;

    // Get the number of connected USB devices
    libusb_device** deviceList;
    deviceCount = libusb_get_device_list( m_ContextObject, &deviceList); //crashed here - must be the context
    if (deviceCount < 0) {
        // handle error
    }

    for (int i = 0; i < deviceCount; i++) {
        libusb_device* device = deviceList[i];
        // do something with the device
    }

    libusb_free_device_list(deviceList, 1);
    //libusb_exit( InContext->m_ContextObject);

    return deviceCount;
}

