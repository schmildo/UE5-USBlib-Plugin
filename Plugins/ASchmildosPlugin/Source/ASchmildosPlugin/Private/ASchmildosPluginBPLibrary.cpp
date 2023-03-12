// Copyright Epic Games, Inc. All Rights Reserved.

#include "ASchmildosPluginBPLibrary.h"

UASchmildosPluginBPLibrary::UASchmildosPluginBPLibrary(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	
}



ULIBUSBwrapper_init* UASchmildosPluginBPLibrary::InitializeLibUsbContext()
{
	libusb_context* tmp_context = nullptr;

	int result = libusb_init(&tmp_context);

	if (result != LIBUSB_SUCCESS)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize libusb_context: %s"), ANSI_TO_TCHAR(libusb_error_name(result)));
		return nullptr;
	}

	UE_LOG(LogTemp, Display, TEXT("libusb_context initialized"));

	ULIBUSBwrapper_init* Context = NewObject<ULIBUSBwrapper_init>();
	Context->SetmContext(tmp_context);

	return Context;
}





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



FString UASchmildosPluginBPLibrary::Convert_uint16_to_String(uint16_t input)
{
	return FString::FromInt(int(input));
}

