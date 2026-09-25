#include "WaveDirector.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AWaveDirector::AWaveDirector()
{
	PrimaryActorTick.bCanEverTick = false; // 省性能
}

void AWaveDirector::StartWave(float Duration, float SpawnInterval, int32 SpawnCount, TSubclassOf<AActor> EnemyClass, float SpawnRadius)
{
	if (!EnemyClass) return; // 如果没传怪物类型，直接拦截

	// 缓存参数
	Cache_SpawnCount = SpawnCount;
	Cache_EnemyClass = EnemyClass;
	Cache_SpawnRadius = SpawnRadius;
	ElapsedSeconds = 0;
	CurrentWave = 0;

	// 启动定时器
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AWaveDirector::RoutineSpawn, SpawnInterval, true);
	GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &AWaveDirector::EndWave, Duration, false);
	GetWorld()->GetTimerManager().SetTimer(ClockTimerHandle, this, &AWaveDirector::TickClock, 1.0f, true);

}

void AWaveDirector::BeginPlay()
{
	Super::BeginPlay();
}

void AWaveDirector::RoutineSpawn()
{
	CurrentWave++;

	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(this, 0);

	FVector PlayerLocation = PlayerChar->GetActorLocation();
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	for (int32 i = 0; i < Cache_SpawnCount; ++i)
	{
		FNavLocation RandomLocation;

		if (NavSystem->GetRandomReachablePointInRadius(PlayerLocation, Cache_SpawnRadius, RandomLocation))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			FVector SafeSpawnLocation = RandomLocation.Location;
			SafeSpawnLocation.Z += 150.0f;

			// 执行生成
			AActor* SpawnedEnemy = GetWorld()->SpawnActor<AActor>(Cache_EnemyClass, SafeSpawnLocation, FRotator::ZeroRotator, SpawnParams);

		}
	}
}

void AWaveDirector::EndWave()
{
	// 掐断刷怪循环
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	// 掐断秒表
	GetWorld()->GetTimerManager().ClearTimer(ClockTimerHandle);
	
	// 召唤Boss
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Player && BossEnemyClass)
	{
		FVector SpawnLocation;
		FRotator SpawnRotation = FRotator::ZeroRotator;

		if (BossSpawnPoint)
		{
			// 如果指定了固定出生点，直接读取它的绝对坐标和朝向
			SpawnLocation = BossSpawnPoint->GetActorLocation();
			SpawnRotation = BossSpawnPoint->GetActorRotation();
		}

		else if(Player)
		{
		// 如果没有配置出生点，就在玩家周围 1000 的距离随机找个点
		FVector PlayerLocation = Player->GetActorLocation();
		FVector RandomDirection = FMath::VRand();
		RandomDirection.Z = 0;
		SpawnLocation = PlayerLocation + (RandomDirection * 1000.0f);
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ACharacter* Boss = GetWorld()->SpawnActor<ACharacter>(BossEnemyClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

		// 呼叫蓝图
		if (Boss)
		{
			OnBossSpawned(Boss);
		}
	}

}

void AWaveDirector::TickClock()
{
	ElapsedSeconds++;
}

