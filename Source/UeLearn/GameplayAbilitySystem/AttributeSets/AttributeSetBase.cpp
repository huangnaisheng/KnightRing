// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"

UAttributeSetBase::UAttributeSetBase()
{

	InitEXP(0.0f);         // 初始经验为 0
	InitMaxEXP(100.0f);    // 第一级需要 100 经验
	InitLevel(1.0f);       // 出生就是 1 级
}


void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		bool bOutOfHealth = false;


		if (GetHealth() <= 0.f && GetMaxHealth() > 0.f && !bOutOfHealth)
		{
			// 获取拥有这个属性的角色
			AActor* TargetActor = Data.Target.GetAvatarActor();
			IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(TargetActor);

			if (ASI)
			{
				UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();


				FGameplayTag DeadTag = FGameplayTag::RequestGameplayTag(FName("Status.Dead"));
				//Data.Target.AddLooseGameplayTag(DeadTag);
				bOutOfHealth = ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(DeadTag));

			}
		}

	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}

	else if (Data.EvaluatedData.Attribute == GetEstusCountAttribute())
	{
		SetEstusCount(FMath::Clamp(GetEstusCount(), 0.f, GetMaxEstusCount()));
	}

	else if (Data.EvaluatedData.Attribute == GetPostureAttribute())
	{
		SetPosture(FMath::Clamp(GetPosture(), 0.f, GetMaxPosture()));

		if (GetPosture() > 0.f && GetPosture() >= (GetMaxPosture() - 0.01f))
		{
			// 获取拥有这个属性的角色
			AActor* TargetActor = Data.Target.GetAvatarActor();
			IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(TargetActor);
			//UE_LOG(LogTemp, Warning, TEXT("Posture Full! Attempting to Stun: %s"), *TargetActor->GetName());

			if (ASI)
			{
				UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();


				FGameplayTag StunTag = FGameplayTag::RequestGameplayTag(FName("Status.Stun"));
				/*UE_LOG(LogTemp, Error, TEXT("STUN TRIGGERED! Current Posture is %f"), GetPosture());*/
				//Data.Target.AddLooseGameplayTag(StunTag);
				bool bSuccess = ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(StunTag));

				SetPosture(0.0f);
			}
		}
	}


	else if (Data.EvaluatedData.Attribute == GetEXPAttribute())
	{

		AActor* TargetActor = Data.Target.GetAvatarActor();
		IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(TargetActor);
		if (ASI)
		{
			UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
			// 如果当前经验 >= 升级所需经验
			if (GetEXP() >= GetMaxEXP())
			{
				// 经验溢出保留（比如差10点升级，吃了个50点的球，升完级还剩40点）
				float LeftoverEXP = GetEXP() - GetMaxEXP();
				SetEXP(LeftoverEXP);

				// 等级 + 1
				SetLevel(GetLevel() + 1.0f);

				// 提高下一级的经验阈值
				SetMaxEXP(GetMaxEXP() + 50.0f);

				// 触发升级事件，通知蓝图弹出“3选1”界面
				FGameplayEventData Payload;
				Payload.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.LevelUp"));
				ASC->HandleGameplayEvent(Payload.EventTag, &Payload);
				//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Level UP! Current Level: %f"), GetLevel()));
			}
		}
	}
}

void UAttributeSetBase::Copy(UAttributeSet* OtherAttributeSet)
{
	if(UAttributeSetBase* OtherAttributeSetBase = Cast<UAttributeSetBase>(OtherAttributeSet))
	{
	Health = OtherAttributeSetBase->Health;
	}
}
