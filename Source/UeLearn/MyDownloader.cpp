// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDownloader.h"
#include "HttpModule.h"

UMyDownloader::UMyDownloader(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		AddToRoot();
	}
}

UMyDownloader* UMyDownloader::Download(const FString& Url, const FString& SavePath)
{
	UMyDownloader* DownloadTask = NewObject<UMyDownloader>();
	DownloadTask->StartDownload(Url, SavePath);
	return DownloadTask;
}

void UMyDownloader::StartDownload(const FString& Url, const FString& SavePath)
{
	FilePath = SavePath;

	if (SavePath.Len() > 1 && FPaths::GetCleanFilename(SavePath).Len() == 0)
	{
		const FString FileName = FPaths::GetCleanFilename(Url);
		if (FileName.Len() > 0)
		{
			FilePath = FPaths::Combine(SavePath, FileName);
		}
	}

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->OnRequestProgress().BindUObject(this, &UMyDownloader::HandleDownloadProgress);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UMyDownloader::HandleDownloadComplete);
	HttpRequest->SetURL(Url);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->ProcessRequest();
}

void UMyDownloader::HandleDownloadProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
{
	if (Request.IsValid())
	{
		OnProgress.Broadcast(0, 0, TEXT(""), BytesReceived);
	}
}

void UMyDownloader::HandleDownloadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	RemoveFromRoot();

	int32 HttpResponseCode = 0;

	if (Request.IsValid())
	{
		HttpResponseCode = Response->GetResponseCode();
	}

	if (bWasSuccessful && Response.IsValid() && Response->GetContentLength() > 0)
	{
		if (FFileHelper::SaveArrayToFile(Response->GetContent(), *FilePath))
		{
			OnSuccess.Broadcast(HttpResponseCode, Response->GetContentLength(), FilePath, 0);
			return;
		}
	}

	OnFailure.Broadcast(HttpResponseCode, 0, TEXT(""), 0);
}
