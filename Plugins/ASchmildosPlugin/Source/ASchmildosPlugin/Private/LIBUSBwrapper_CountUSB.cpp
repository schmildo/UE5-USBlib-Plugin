// Fill out your copyright notice in the Description page of Project Settings.


#include "LIBUSBwrapper_CountUSB.h"
#include "M:\UnrealEngineProjects\USB\Plugins\ASchmildosPlugin\ThirdParty\USBLIB\include\libusb.h"

int32 ULIBUSBwrapper_CountUSB::CountConnectedUSBDevices()
{
    libusb_context* tmp_context = nullptr;
    int32 deviceCount = 0;

    // Initialize libusb
    int32 result = libusb_init(&tmp_context);
    if (result < 0)
    {
        // Error initializing libusb
        return 0;
    }

    // Get the number of connected USB devices
    libusb_device** deviceList;
    deviceCount = libusb_get_device_list(tmp_context, &deviceList);
    if (deviceCount < 0) {

        // handle error
    }

    for (int i = 0; i < deviceCount; i++) {
        libusb_device* device = deviceList[i];
        // do something with the device
    }

    







    //deviceCount = libusb_get_device_list(tmp_context, nullptr);
    libusb_free_device_list(deviceList, 1);
    libusb_exit(tmp_context);
//    deviceCount = 42;
    return deviceCount;
}