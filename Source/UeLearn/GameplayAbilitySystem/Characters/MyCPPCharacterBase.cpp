// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCPPCharacterBase.h"  
#include "AbilitySystemComponent.h"
#include "UeLearn/GameplayAbilitySystem/AttributeSets/AttributeSetBase.h"


// Sets default values
AMyCPPCharacterBase::AMyCPPCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// AbilitySystem
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true); // 允许网络复制
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);// 设置复制模式

	AttributeSetBase = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSetBase"));
}

// Called when the game starts or when spawned
void AMyCPPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCPPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCPPCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCPPCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AMyCPPCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this); 
	}
}



