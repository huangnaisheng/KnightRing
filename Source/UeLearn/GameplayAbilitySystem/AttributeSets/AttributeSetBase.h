 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 


UCLASS()
class UELEARN_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:

	UAttributeSetBase();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health; // 血量
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth; // 最大血量
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;  // 耐力
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Stamina)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;  // 最大耐力         
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxStamina) 

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Posture = 0.f; // 架势条
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Posture)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxPosture; // 最大架势条
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxPosture)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData EstusCount; // 元素瓶数量
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, EstusCount)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxEstusCount; // 最大元素瓶数量
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxEstusCount)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData EXP;			// 经验值
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, EXP)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxEXP;		// 最大经验值
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxEXP)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Level;		// 等级
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Level)

private:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;

public:
	UFUNCTION(BlueprintCallable)
	void Copy(UAttributeSet* OtherAttributeSet);
};
