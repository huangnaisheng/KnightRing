// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegate);

USTRUCT(BlueprintType)
struct FMyStruct {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int a;
	UPROPERTY(BlueprintReadWrite)
	bool b;
	UPROPERTY(BlueprintReadOnly)
	FString c;
	UPROPERTY(BlueprintReadWrite)
	TArray<float> d;
};

UENUM(BlueprintType)
enum class EMyEnum : uint8 {
	Zero UMETA(DisplayName = "0"),
	One UMETA(DisplayName = "1"),
	Two UMETA(DisplayName = "2"),
	Three UMETA(DisplayName = "3"),
};

UCLASS()
class UELEARN_API AMyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

private:
	// Input functions
	void Move(const struct FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

protected:
	UFUNCTION(BlueprintCallable, CallInEditor)
	void TestFunction();

	UFUNCTION()
	void Print();

	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Test")
	FTestDelegate TestDelegate;

};
