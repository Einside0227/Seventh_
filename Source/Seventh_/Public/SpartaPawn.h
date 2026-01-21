// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpartaPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SEVENTH__API ASpartaPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpartaPawn();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test|Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test|Components")
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
