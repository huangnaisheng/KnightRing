// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建对象							类型                     命名
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//       设置层级结构      父节点            插槽
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// 一些基本设置
	bUseControllerRotationYaw = false;	// 不 让角色跟随控制器左右旋转
	SpringArm->bUsePawnControlRotation = true; // 让弹簧臂跟随控制器旋转
	 
	// 移动组件设置
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->bOrientRotationToMovement = true; // 让角色朝向移动方向旋转
	MovementComponent->RotationRate = FRotator(0.f, 500.f, 0.f); // 旋转速度

}

// Called when the game starts or when spawned
void AMyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	//// 通过路径查找骨骼网格资源	读取对象           对象的类型                父对象                  路径
	//UObject* SkeletalMesh = StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/Templates/ThirdPerson/Characters/Mannequins/Meshes/SKM_Quinn"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, SkeletalMesh ? TEXT("SkeletalMesh Found!") : TEXT("SkeletalMesh Not Found!"));
	//// 设置角色的骨骼网格		   类型转换 目标类型
	//GetMesh()->SetSkeletalMesh(Cast<USkeletalMesh>(SkeletalMesh));

	//     绑定委托    绑定函数的所属对象     要绑定的函数
	//TestDelegate.BindUObject(this, &AMyCharacterBase::Print);
	//TestDelegate.BindLambda([] { GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, "LambdaTest"); });

	//TestDelegate.AddUObject(this, &AMyCharacterBase::Print);
	//TestDelegate.AddLambda([] { GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, "LambdaTest"); });

	TestDelegate.AddDynamic(this, &AMyCharacterBase::Print);
}

// Called every frame
void AMyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// 添加输入映射
	// 获取玩家控制器 为了下面获取本地玩家 本地玩家可以获取子系统
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		// 从本地玩家子系统获取增强输入子系统
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//能进入到这里 说明已经成功获取到增强输入子系统了
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// 绑定回调
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacterBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacterBase::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}


void AMyCharacterBase::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();
	// 使用指针之前 一定要判空 如果用到了空指针 引擎直接崩溃
	if (Controller)
	{
		// 获得控制器旋转
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		// 前方向
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// 右方向  
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// 添加移动输入
		AddMovementInput(ForwardDirection, InputValue.Y);
		AddMovementInput(RightDirection, InputValue.X);
	}
}

void AMyCharacterBase::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (Controller)
	{
		// 添加视角输入
		AddControllerYawInput(InputValue.X);
		AddControllerPitchInput(InputValue.Y);
	}
}

void AMyCharacterBase::TestFunction()
{
	// TestDelegate.ExecuteIfBound();
	TestDelegate.Broadcast();
}

void AMyCharacterBase::Print()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Print"));
}

