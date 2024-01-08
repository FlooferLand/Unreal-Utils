#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Components/AudioComponent.h"
#include "AudioPlaybackObject.generated.h"

/** */
UCLASS()
class UTILITY_API UAudioPlaybackObject : public UObject {
	GENERATED_BODY()
public:
	bool bIsFinished = false;
	UPROPERTY() UAudioComponent* AudioComponent = nullptr;

	void Initialize(UAudioComponent* audioComponent);
	void Play(USoundBase* sound) const;
	
	UFUNCTION()
	void OnAudioFinished();
};
