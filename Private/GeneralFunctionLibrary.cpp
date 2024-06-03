#include "GeneralFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UGeneralFunctionLibrary::Billboard(USceneComponent* target) {
	if (target == nullptr) return;
	
	// Getting stuff
	const APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(target->GetWorld(), 0);
	const FRotator cameraRotation = cameraManager->GetTransformComponent()->GetComponentRotation();
	const FRotator targetRotation = target->GetComponentRotation();

	// Applying the rotation
	const FRotator newRotation = UKismetMathLibrary::MakeRotator(
		targetRotation.Roll,
		targetRotation.Pitch,
		cameraRotation.Yaw + 180
	);
	target->SetWorldRotation(newRotation);
}

void UGeneralFunctionLibrary::Joeboard(USceneComponent* target) {
	if (target == nullptr) return;
	
	// Getting stuff
	const APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(target->GetWorld(), 0);
	const FVector targetLocation = target->GetComponentLocation();
	const FVector cameraLocation = cameraManager->GetCameraLocation();
	const FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(targetLocation, cameraLocation);

	FVector yAxis = FVector();
	FVector unused = FVector(); // TODO: Might want to write my own type if i use GetAxes a lot. Like an "FRotatorVector"
	UKismetMathLibrary::GetAxes(lookAtRotation, unused, yAxis, unused);

	const FRotator newRotation = UKismetMathLibrary::ComposeRotators(
		yAxis.ToOrientationRotator(),
		FRotator(0, 0, -90)
	);
	
	// Applying the rotation
	target->SetWorldRotation(newRotation);
}

void UGeneralFunctionLibrary::GoofyAhhBoard(USceneComponent* target) {
	if (target == nullptr) return;
	
	// Getting stuff
	const APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(target->GetWorld(), 0);
	const FRotator cameraRotation = cameraManager->GetTransformComponent()->GetComponentRotation();

	// Applying the rotation
	const FRotator newRotation = UKismetMathLibrary::MakeRotator(
		-cameraRotation.Roll * 0.5,
		-cameraRotation.Pitch,
		cameraRotation.Yaw + 180
	);
	target->SetWorldRotation(newRotation);
}
