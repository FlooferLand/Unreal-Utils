#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "AudioUtilCommon.h"
#include "AudioUtil.generated.h"

/** General audio utility functions */
UCLASS()
class UTILITY_API UAudioUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:	
	static void PlaySoundCore(
		UObject* worldCtx, FLatentActionInfo& latentInfo,
		UAudioComponent* audioComp,
		USoundBase* sound
	);
	
public:
	UFUNCTION(BlueprintCallable, meta=(
		Latent, LatentInfo="latentInfo",
		HidePin = "worldCtx", DefaultToSelf = "worldCtx"
	))
	/** Play audio and listen for the audio to finish */
	static void PlaySoundOnComponent(
		/* Async stuff: */
		UObject* worldCtx, FLatentActionInfo latentInfo,
		UAudioComponent* audioComp,
		USoundBase* sound
	);
	
	UFUNCTION(BlueprintCallable, meta=(
		Latent, LatentInfo="latentInfo",
		HidePin = "worldCtx", DefaultToSelf = "worldCtx"
	))
	/** Play audio from a component and listen for the audio to finish */
	static void PlaySoundAttached(
		/* Async stuff: */ UObject* worldCtx, FLatentActionInfo latentInfo,
		USceneComponent* attachComp,
		USoundBase* sound,
		USoundAttenuation* attenuation,
		float volume = 1.0,
		float pitch = 1.0
	);
	
	UFUNCTION(BlueprintCallable, meta=(
		Latent, LatentInfo="latentInfo",
		HidePin = "worldCtx", DefaultToSelf = "worldCtx"
	))
	/** Play audio at a location and listen for the audio to finish */
	static void PlaySoundAtLocation(
		/* Async stuff: */ UObject* worldCtx, FLatentActionInfo latentInfo,
		FVector location,
		USoundBase* sound,
		USoundAttenuation* attenuation,
		float volume = 1.0,
		float pitch = 1.0
	);
};
