// Fill out your copyright notice in the Description page of Project Settings.


#include "LIBUSBwrapper_CountUSB.h"
/*
int32 ULIBUSBwrapper_CountUSB::SumConnectedDevices(ULIBUSBwrapper_init*& InContext)
{
    libusb_context* tmp_context = InContext->GetmContext();
    int32 deviceCount = 0;

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

    libusb_free_device_list(deviceList, 1);
    libusb_exit(tmp_context);

    return deviceCount;
}
*/