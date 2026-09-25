// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "MyDownloader.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FDownloadDelegate, int32, HttpResponseCode, int32, ContentLength, const FString&, SavePath, int32, BytesReceived);

UCLASS()
class UELEARN_API UMyDownloader : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Download", meta = (BlueprintInternalUseOnly = "true"))
	static UMyDownloader* Download(const FString& Url, const FString& SavePath);

	UPROPERTY(BlueprintAssignable)
	FDownloadDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDownloadDelegate OnFailure;

	UPROPERTY(BlueprintAssignable)
	FDownloadDelegate OnProgress;

protected:
	void StartDownload(const FString& Url, const FString& SavePath);

private:
	void HandleDownloadProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived);
	void HandleDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	FString FilePath;
};
