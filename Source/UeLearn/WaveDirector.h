// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveDirector.generated.h"

UCLASS()
class UELEARN_API AWaveDirector : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Config")
	TSubclassOf<ACharacter> BossEnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Config")
	AActor* BossSpawnPoint;



	UFUNCTION(BlueprintImplementableEvent, Category = "Director System")
	void OnBossSpawned(ACharacter* SpawnedBoss);

	UPROPERTY(BlueprintReadOnly, Category = "Director System")
	int32 CurrentWave = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Director System")
	int32 ElapsedSeconds = 0;

	// Sets default values for this actor's properties
	AWaveDirector();

	UFUNCTION(BlueprintCallable, Category = "Director System")
	void StartWave(float Duration, float SpawnInterval, int32 SpawnCount, TSubclassOf<AActor> EnemyClass, float SpawnRadius);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	void RoutineSpawn();
	void EndWave();
	void TickClock(); 

	FTimerHandle EliteTimerHandle;
	FTimerHandle SpawnTimerHandle;
	FTimerHandle WaveTimerHandle;
	FTimerHandle ClockTimerHandle;

	// 缓存传入的参数，供 RoutineSpawn 使用
	int32 Cache_SpawnCount;
	TSubclassOf<AActor> Cache_EnemyClass;
	float Cache_SpawnRadius;

};
