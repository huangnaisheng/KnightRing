// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNetCharacterBase.h"

// Sets default values
AMyNetCharacterBase::AMyNetCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyNetCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyNetCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyNetCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyNetCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	OnPlayerStateReplicate();
}

