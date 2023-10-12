#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Components/AudioComponent.h"
#include "AudioPlaybackObject.generated.h"

/** */
UCLASS()
class UTILITY_API UAudioPlaybackObject : public UObject
{
	GENERATED_BODY()

public:
	bool bIsFinished = false;
	UPROPERTY() UAudioComponent* AudioComponent = nullptr;

	void Initialize(UAudioComponent* audio_component);
	void Play(USoundBase* sound, float volume = 1.0, float pitch = 1.0);
	
	UFUNCTION()
	void OnAudioFinished();
};
