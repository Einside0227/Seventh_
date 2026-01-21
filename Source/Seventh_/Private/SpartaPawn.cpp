// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPawn.h"
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

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    CameraComp->bUsePawnControlRotation = false;
}


// Called to bind functionality to input
void ASpartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

