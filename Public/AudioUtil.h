#pragma once
#include "CoreMinimal.h"
#include "AudioUtilPlayer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "AudioUtilCommon.h"
#include "AudioUtil.generated.h"

/** General audio utility functions */
UCLASS()
class UTILITY_API UAudioUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Map to associate each sound with it's own delegate
	// inline static TMap SoundplayerMap = TMap<UAudioComponent*, TWeakObjectPtr<UAudioUtilPlayer>>();
	
	/** Play audio and listen for the audio to finish */
	UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs = "branch"))
	static void PlaySoundOnComponent(
		/* Exec pin */ EFinishedBranch& branch,
		USoundBase* sound,
		UAudioComponent* audio_comp,
		float volume = 1.0,
		float pitch = 1.0
	);
	
	/** Play audio from a component and listen for the audio to finish */
	UFUNCTION(BlueprintCallable, meta=(ExpandEnumAsExecs = "branch"))
	void PlaySoundAttached(
		/* Exec pin */ EFinishedBranch& branch,
		USoundBase* sound,
		USceneComponent* attachComp,
		USoundAttenuation* attenuation,
		float volume = 1.0,
		float pitch = 1.0
	);
};
