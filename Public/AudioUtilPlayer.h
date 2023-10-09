#pragma once
#include "Misc/Optional.h"
#include "CoreMinimal.h"
#include "AudioUtilCommon.h"
#include "Components/AudioComponent.h"
#include "UObject/Object.h"
#include "AudioUtilPlayer.generated.h"

/**  */
UCLASS()
class UTILITY_API UAudioUtilPlayer : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(TSharedPtr<EFinishedBranch> branch, UAudioComponent* component);
	void Play(USoundBase* sound);

	void SetDetails(float volume = 1.0, float pitch = 1.0, USoundAttenuation* attenuation = nullptr);
	float Volume, Pitch;
	UPROPERTY() USoundAttenuation* Attenuation = nullptr;

	UFUNCTION()
	void OnAudioFinished();
private:
	// Variables
	TSharedPtr<EFinishedBranch> Branch = nullptr;
	UPROPERTY()	UAudioComponent* AudioComponent = nullptr;
};
