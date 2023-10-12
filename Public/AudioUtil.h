#pragma once
#include "CoreMinimal.h"
#include "AudioPlaybackObject.h"
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

protected:
	static void PlaySoundCore(
		UObject* world_ctx, FLatentActionInfo latent_info,
		UAudioComponent* audio_comp,
		USoundBase* sound,
		float volume = 1.0, float pitch = 1.0
	);
	
public:
	UFUNCTION(BlueprintCallable, meta=(
		Latent, LatentInfo="latent_info",
		HidePin = "world_ctx", DefaultToSelf = "world_ctx"
	))
	/** Play audio and listen for the audio to finish */
	static void PlaySoundOnComponent(
		/* Async stuff: */ UObject* world_ctx, FLatentActionInfo latent_info,
		UAudioComponent* audio_comp,
		USoundBase* sound,
		float volume = 1.0,
		float pitch = 1.0
		);
	
	UFUNCTION(BlueprintCallable, meta=(
		Latent, LatentInfo="latent_info",
		HidePin = "world_ctx", DefaultToSelf = "world_ctx"
	))
	/** Play audio from a component and listen for the audio to finish */
	static void PlaySoundAttached(
		/* Async stuff: */ UObject* world_ctx, FLatentActionInfo latent_info,
		USceneComponent* attach_comp,
		USoundBase* sound,
		USoundAttenuation* attenuation,
		float volume = 1.0,
		float pitch = 1.0
	);
	
	UFUNCTION(BlueprintCallable, meta=(
		Latent, LatentInfo="latent_info",
		HidePin = "world_ctx", DefaultToSelf = "world_ctx"
	))
	/** Play audio at a location and listen for the audio to finish */
	static void PlaySoundAtLocation(
		/* Async stuff: */ UObject* world_ctx, FLatentActionInfo latent_info,
		FVector location,
		USoundBase* sound,
		USoundAttenuation* attenuation,
		float volume = 1.0,
		float pitch = 1.0
	);
};
