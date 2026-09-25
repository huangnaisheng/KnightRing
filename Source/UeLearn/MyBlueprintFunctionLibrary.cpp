// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

bool UMyBlueprintFunctionLibrary::ReadTxt(FString Path, FString& Txt, FString Extension)
{

	return FFileHelper::LoadFileToString(Txt, *(Path + Extension));
}

bool UMyBlueprintFunctionLibrary::WriteTxt(FString Path, FString Txt, FString Extension)
{
	return FFileHelper::SaveStringToFile(Txt, *(Path + Extension));
}

void UMyBlueprintFunctionLibrary::ApplyHitStop(const UObject* WorldContextObject, AActor* TargetActor, float Duration, float DilationValue)
{
	//安全检查：如果 Actor 已经死了或不存在，直接返回
	// 防止在短时间内触发两次顿帧导致卡死
	if (!TargetActor || !WorldContextObject || Duration <= 0.f) return;
	if (TargetActor->CustomTimeDilation <= 0.01f) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;


	//记录当前的时间膨胀值（防止干扰原本的慢动作效果）
	const float OriginalDilation = TargetActor->CustomTimeDilation;


	// 实施顿帧
	TargetActor->CustomTimeDilation = DilationValue;

	//创建定时器委托(使用 Lambda 捕获)
	FTimerDelegate TimerDel;

	// 将这两个变量“抓”进延时逻辑里
	TimerDel.BindLambda([TargetActor, OriginalDilation]()
		{
			// 延时结束后执行的代码：
			if (IsValid(TargetActor))
			{
				TargetActor->CustomTimeDilation = OriginalDilation;
			}
		});
	// 启动定时器
	 FTimerHandle TimerHandle;

	 // 使用 Duration 后的回调，bLoop 设为 false
	 World->GetTimerManager().SetTimer(TimerHandle, TimerDel, Duration, false);
}
 