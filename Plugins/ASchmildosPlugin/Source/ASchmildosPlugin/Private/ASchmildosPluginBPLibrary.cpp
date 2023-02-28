// Copyright Epic Games, Inc. All Rights Reserved.

#include "ASchmildosPluginBPLibrary.h"

UASchmildosPluginBPLibrary::UASchmildosPluginBPLibrary(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{

}

int32 UASchmildosPluginBPLibrary::CountConnectedUSBDevices()
{
	ULIBUSBwrapper_CountUSB usbContext;
	int32 numDevices = usbContext.CountConnectedUSBDevices();
	return numDevices;
}









/*

FString UASchmildosPluginBPLibrary::LibUSB_GetVersion()
{
	FString str_ReturnValue;

	UE_LOG(LogTemp, Warning, TEXT("Plugin directory: %s"), *FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("ASchmildosPlugin"))));
		FString Major = Convert_uint16_to_String(libusb_get_version()->major);
		FString Minor = Convert_uint16_to_String(libusb_get_version()->minor);
		FString Micro = Convert_uint16_to_String(libusb_get_version()->micro);
		str_ReturnValue = Major+"."+Minor+"."+Micro;
	return str_ReturnValue;
}
*/

/*
FString UASchmildosPluginBPLibrary::Convert_uint16_to_String(uint16_t input)
{
	return FString::FromInt(int(input));
}

*/