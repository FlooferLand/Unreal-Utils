#include "AudioUtil.h"
#include "AudioPlaybackAction.h"
#include "BackendUtil.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void UAudioUtil::PlaySoundCore(
	const UObject* worldCtx, const FLatentActionInfo& latentInfo,
	UAudioComponent* audioComp,
	USoundBase* sound)
{
	// World stuff
	if (!IsValid(worldCtx) || !IsValid(audioComp) || !IsValid(sound)) {
		BackendUtil::LogError("Safety guard in UAudioUtil::PlaySoundAttached failed");
		return;
	}
	audioComp->bAutoDestroy = false;
	
	// Spawning the action
	UWorld* world = worldCtx->GetWorld();
	if (!IsValid(world)) {
		BackendUtil::LogError("Invalid world in PlaySoundCore");
		return;
	}
	FLatentActionManager& actionManager = world->GetLatentActionManager();
	if (actionManager.FindExistingAction<FPendingLatentAction>(latentInfo.CallbackTarget.Get(), latentInfo.UUID) == nullptr) {
		FAudioPlaybackAction* action = new FAudioPlaybackAction(latentInfo, audioComp, sound);
		actionManager.AddNewAction(latentInfo.CallbackTarget, latentInfo.UUID, action);
	}
}

// TODO: Maybe make it copy the settings of the component and spawn a sound attached so we can have pitch/volume settings
void UAudioUtil::PlaySoundOnComponent(
	UObject* worldCtx, FLatentActionInfo latentInfo,
	UAudioComponent* audioComp,
	USoundBase* sound)
{
	// Play the audio and set up the latent
	PlaySoundCore(worldCtx, latentInfo, audioComp, sound);
}

// TODO: Make this not as messy as it currently is
void UAudioUtil::PlaySoundAttached(
	UObject* worldCtx, FLatentActionInfo latentInfo,
	USceneComponent* attachComp,
	USoundBase* sound,
	USoundAttenuation* attenuation,
	float volume, float pitch)
{
	if (!IsValid(sound) || !IsValid(attachComp)) {
		BackendUtil::LogError("Safety guard in UAudioUtil::PlaySoundAttached failed");
		return;
	}
	
	UAudioComponent* audioComp = UGameplayStatics::SpawnSoundAttached(
		sound, attachComp,
		NAME_None, FVector::Zero(), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false,
		volume, pitch, 0, attenuation
	);

	// Play the audio and set up the latent
	PlaySoundCore(worldCtx, latentInfo, audioComp, sound);
}

void UAudioUtil::PlaySoundAtLocation(
	UObject* worldCtx, FLatentActionInfo latentInfo,
	FVector location,
	USoundBase* sound,
	USoundAttenuation* attenuation,
	float volume, float pitch)
{
	if (!IsValid(worldCtx) && !IsValid(sound) && !IsValid(attenuation)) {
		BackendUtil::LogError("Safety guard in UAudioUtil::PlaySoundAtLocation failed");
		return;
	}
	
	UAudioComponent* audioComp = UGameplayStatics::SpawnSoundAtLocation(
		worldCtx, sound, location, FRotator::ZeroRotator,
		volume, pitch, 0, attenuation
	);
	
	// Play the audio and set up the latent
	PlaySoundCore(worldCtx, latentInfo, audioComp, sound);
}
