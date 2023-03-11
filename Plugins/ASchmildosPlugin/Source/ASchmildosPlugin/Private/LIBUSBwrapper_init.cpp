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

int32 ULIBUSBwrapper_init::CountDevices()
{
    int32 deviceCount = 0;

    // Get the number of connected USB devices
    //m_deviceList = nullptr;
    
    deviceCount = libusb_get_device_list(m_ContextObject, &m_Devices);
    //deviceCount = 42;
    if (deviceCount < 0) {
        // handle error
    }

    for (int i = 0; i < deviceCount; i++) {
        libusb_device* device = m_Devices[i];
        // do something with the device
    }

    //libusb_free_device_list(m_Devices, 1);
    //libusb_exit( InContext->m_ContextObject);

    return deviceCount;
}

TArray<UMyLibusbDevice*> ULIBUSBwrapper_init::GetDeviceList()
{
    //TArray<UMyLibusbDevice*> DeviceList;

    // Initialize Libusb context
    //libusb_context* Context;
    if (libusb_init(&m_ContextObject) != 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize Libusb context"));
        return m_DeviceList;
    }

    // Get list of devices
    //libusb_device** Devices;
    ssize_t Count = libusb_get_device_list(m_ContextObject, &m_Devices);
    if (Count < 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get list of Libusb devices"));
      //  libusb_exit(m_ContextObject);
        return m_DeviceList;
    }

    // Iterate over devices and populate device list
    for (int32 i = 0; i < Count; ++i)
    {
        libusb_device* Device = m_Devices[i];

        // Get device descriptor
        libusb_device_descriptor Descriptor;
        if (libusb_get_device_descriptor(Device, &Descriptor) != 0)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get descriptor for Libusb device"));
            continue;
        }

        // Populate device info struct
        UMyLibusbDevice* DeviceInfo = NewObject<UMyLibusbDevice>();
        DeviceInfo->m_ThisDevice = Device;
        DeviceInfo->DeviceId = Descriptor.idVendor * 0x10000 + Descriptor.idProduct;
        DeviceInfo->VendorId = Descriptor.idVendor;
        DeviceInfo->ProductId = Descriptor.idProduct;
        DeviceInfo->DeviceName = FString::Printf(TEXT("Vendor ID: %04x, Product ID: %04x"), Descriptor.idVendor, Descriptor.idProduct);
        DeviceInfo->m_ContextObject = this->m_ContextObject;
        DeviceInfo->m_Wrapper = this;

        // Add device info to list
        m_DeviceList.Add(DeviceInfo);
    }

    // Free list of devices
   // libusb_free_device_list(Devices, 1);

    // Exit Libusb context
  //  libusb_exit(m_ContextObject);

    return m_DeviceList;
}

void ULIBUSBwrapper_init::PrintDeviceList(TArray<UMyLibusbDevice*> IN_DeviceList)
{
    
    int Count = IN_DeviceList.Num();
    UE_LOG(LogTemp, Warning, TEXT("SHIT BEIGN PRINTED"));
    if (Count < 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get list of Libusb devices"));
        //  libusb_exit(m_ContextObject);
        //return IN_DeviceList;
    }

    for (int32 i = 0; i < Count; ++i)
    {
        UE_LOG(LogTemp, Warning, TEXT("abc"));
    }
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



libusb_device* UMyLibusbDevice::GetActualD() const
{
    return m_ThisDevice;
}

FDeviceVID UMyLibusbDevice::GetDeviceVID() const
{
    FString VIDString = TEXT("0x") + FString::Printf(TEXT("%04x"), this->VendorId);
    FDeviceVID VID;
    VID.IntVID = this->VendorId;
    VID.StringVID = VIDString;
    return VID;
}

FString UMyLibusbDevice::GetDeviceVID_AsString() const
{
    return TEXT("0x") + FString::Printf(TEXT("%04x"), this->VendorId);
}

UMylibusb_device_descriptor::UMylibusb_device_descriptor()
{

}

FString UMylibusb_device_descriptor::getCode()
{
    //this->bDeviceClass
    return StaticEnum<UMylibusb_class_code>()->GetValueAsString(this->bDeviceClass);
}



/*
libusb_device_handle *TIM_GetDeviceHandlePointer(libusb_context* USB_Context, uint16_t IDVendor = 0x0802, uint16_t IDProduct = 0x0005)
{
    libusb_device_handle *returnValue;
    returnValue = libusb_open_device_with_vid_pid(USB_Context, IDVendor, 0x0005);
    if (returnValue != nullptr)
    {
        std::cout << "Found handle.." << std::endl;
    }
    else
    {
        std::cout << "Did not find handle.. device probably not plugged in. Exiting safely." << std::endl;
        exit(0);
    }
    return returnValue;
}
*/





UMyLibusbDeviceHandle* UMyLibusbDeviceHandle::OpenThisDevice(UMyLibusbDevice* IN_Device)
{
    UE_LOG(LogTemp, Warning, TEXT("im inside um... TIM_open_device_with_vid_pid"));
    UMyLibusbDeviceHandle* Handle = NewObject<UMyLibusbDeviceHandle>();
    Handle->m_DeviceHandle = libusb_open_device_with_vid_pid(IN_Device->m_ContextObject, IN_Device->VendorId, IN_Device->ProductId);
    return Handle;
}



// OMG rewrite thsi. so bad. Using unreliable memory and stuff. god.

UMylibusb_device_descriptor* UMyLibusbDevice::GetDeviceDescriptor(UMyLibusbDevice* IN_Device)
{
    //ULIBUSBwrapper_init* Context = NewObject<ULIBUSBwrapper_init>();
    UMylibusb_device_descriptor* MyDD = NewObject<UMylibusb_device_descriptor>();
    libusb_device_descriptor* tmp_DD = new libusb_device_descriptor;

    libusb_get_device_descriptor(IN_Device->GetActualD(), tmp_DD);
    MyDD->bcdDevice = tmp_DD->bcdDevice;
    MyDD->bcdUSB = tmp_DD->bcdUSB;
    MyDD->bDescriptorType = tmp_DD->bDescriptorType;
    MyDD->bDeviceClass = static_cast<UMylibusb_class_code>(tmp_DD->bDeviceClass);
    MyDD->bDeviceProtocol = tmp_DD->bDeviceProtocol;
    MyDD->bDeviceSubClass = tmp_DD->bDeviceSubClass;
    MyDD->bLength = tmp_DD->bLength;
    MyDD->bMaxPacketSize0 = tmp_DD->bMaxPacketSize0;
    MyDD->bNumConfigurations = tmp_DD->bNumConfigurations;
    MyDD->idProduct = tmp_DD->idProduct;
    MyDD->idVendor = tmp_DD->idVendor;
    MyDD->iManufacturer = tmp_DD->iManufacturer;
    MyDD->iProduct = tmp_DD->iProduct;
    MyDD->iSerialNumber = tmp_DD->iSerialNumber;
    delete tmp_DD;
    return MyDD;
}