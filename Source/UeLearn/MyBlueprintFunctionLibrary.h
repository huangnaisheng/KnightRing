// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

 
UCLASS()
class UELEARN_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static bool ReadTxt(FString Path, FString& Txt, FString Extension = ".txt");

	UFUNCTION(BlueprintCallable)
	static bool WriteTxt(FString Path, FString Txt, FString Extension = ".txt");

	UFUNCTION(BlueprintCallable, Category = "Combat|Effects", meta = (WorldContext = "WorldContextObject"))
	static void ApplyHitStop(const UObject* WorldContextObject, AActor* TargetActor, float Duration, float DilationValue = 0.001f);
};
