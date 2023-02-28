// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "M:\UnrealEngineProjects\USB\Plugins\ASchmildosPlugin\ThirdParty\USBLIB\include\libusb.h"
#include "LIBUSBwrapper_CountUSB.generated.h"


UCLASS()
class ASCHMILDOSPLUGIN_API ULIBUSBwrapper_CountUSB : public UObject
{
	GENERATED_BODY()
public:
	    UFUNCTION(BlueprintCallable, Category = "SchmildosPlugin")
		static int32 CountConnectedUSBDevices();
private:

};
