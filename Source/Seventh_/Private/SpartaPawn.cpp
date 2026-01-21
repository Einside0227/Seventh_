// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPawn.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASpartaPawn::ASpartaPawn()
{
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SceneRoot"));
    SetRootComponent(CapsuleComponent);

    SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMeshComp->SetupAttachment(CapsuleComponent);
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Resources/Characters/Meshes/SKM_Manny.SKM_Manny"));
    if (MeshAsset.Succeeded())
    {
        SkeletalMeshComp->SetSkeletalMesh(MeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset0(TEXT("/Game/Resources/Characters/Materials/Instances/Manny/MI_Manny_02.MI_Manny_02"));
    if (MaterialAsset0.Succeeded())
    {
        SkeletalMeshComp->SetMaterial(0, MaterialAsset0.Object);
    }
    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset1(TEXT("/Game/Resources/Characters/Materials/Instances/Manny/MI_Manny_01.MI_Manny_01"));
    if (MaterialAsset1.Succeeded())
    {
        SkeletalMeshComp->SetMaterial(1, MaterialAsset1.Object);
    }

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 300.0f;
    SpringArmComp->bUsePawnControlRotation = true;
    bUseControllerRotationYaw = true;
    bUseControllerRotationPitch = true;


    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    CameraComp->bUsePawnControlRotation = false;

    CapsuleComponent->SetSimulatePhysics(false);
    SkeletalMeshComp->SetSimulatePhysics(false);
}

void ASpartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)){
        if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController())){
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &ASpartaPawn::Move
                );
            }

            if (PlayerController->LookAction){
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &ASpartaPawn::Look
                );
            }
        }
    }
}

void ASpartaPawn::Move(const FInputActionValue& value) {
    if (!Controller) return;

    const FVector2D MoveInput = value.Get<FVector2D>();
    const float DT = GetWorld()->GetDeltaSeconds();

    if (!FMath::IsNearlyZero(MoveInput.X))
    {
        const FVector Delta = FVector(MoveInput.X * MoveSpeed * DT, 0.f, 0.f);
        AddActorLocalOffset(Delta, true);
    }

    if (!FMath::IsNearlyZero(MoveInput.Y))
    {
        const FVector Delta = FVector(0.f, MoveInput.Y * MoveSpeed * DT, 0.f);
        AddActorLocalOffset(Delta, true);
    }
}

void ASpartaPawn::Look(const FInputActionValue& value) {
    if (!Controller) return;

    const FVector2D LookAxis = value.Get<FVector2D>();

    const float YawSpeed = 150.f;
    const float PitchSpeed = 120.f;

    const float DT = GetWorld() ? GetWorld()->GetDeltaSeconds() : 0.f;

    FRotator ControlRot = Controller->GetControlRotation();

    ControlRot.Yaw += LookAxis.X * YawSpeed * DT;
    ControlRot.Pitch -= LookAxis.Y * PitchSpeed * DT;

    ControlRot.Pitch = FMath::ClampAngle(ControlRot.Pitch, -80.f, 80.f);

    Controller->SetControlRotation(ControlRot);

    SetActorRotation(FRotator(0.f, ControlRot.Yaw, 0.f));
}
