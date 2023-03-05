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

libusb_context* ULIBUSBwrapper_init::GetmContext()
{
    return m_ContextObject;
}


bool ULIBUSBwrapper_init::SetmContext(libusb_context* IN_ContextObject)
{
    m_ContextObject = IN_ContextObject;
    return true;
}

