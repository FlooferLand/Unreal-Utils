#include "AudioUtil.h"

#include "AudioPlaybackAction.h"

void UAudioUtil::PlaySoundCore(
	const UObject* worldCtx, const FLatentActionInfo& latentInfo,
	UAudioComponent* audioComp,
	USoundBase* sound,
	float volume, float pitch)
{
	// World stuff
	UWorld* world = worldCtx->GetWorld();
	if (!world) return;
	
	// Spawning the action
	FLatentActionManager& actionManager = world->GetLatentActionManager();
	if (actionManager.FindExistingAction<FPendingLatentAction>(latentInfo.CallbackTarget.Get(), latentInfo.UUID) == nullptr)
	{
		volume = audioComp->VolumeMultiplier * volume;
		pitch  = audioComp->PitchMultiplier * pitch;
		FAudioPlaybackAction* action = new FAudioPlaybackAction(
			latentInfo, audioComp, sound, volume, pitch
		);
		actionManager.AddNewAction(latentInfo.CallbackTarget.Get(), latentInfo.UUID, action);
	}
}

void UAudioUtil::PlaySoundOnComponent(
	UObject* worldCtx, FLatentActionInfo latentInfo,
	UAudioComponent* audioComp,
	USoundBase* sound,
	float volume, float pitch)
{
	if (!IsValid(sound) || !IsValid(audioComp)) return;

	// Play the audio and set up the latent
	PlaySoundCore(worldCtx, latentInfo, audioComp, sound, volume, pitch);
}

// TODO: Make this not as messy as it currently is
void UAudioUtil::PlaySoundAttached(
	UObject* worldCtx, FLatentActionInfo latentInfo,
	USceneComponent* attachComp,
	USoundBase* sound,
	USoundAttenuation* attenuation,
	float volume, float pitch)
{
	if (!IsValid(sound)) return;
	
	UAudioComponent* audioComp = UGameplayStatics::SpawnSoundAttached(
		sound, attachComp,
		NAME_None, FVector::Zero(), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false,
		1.0, 1.0, 0, attenuation
	);

	// Play the audio and set up the latent
	PlaySoundCore(worldCtx, latentInfo, audioComp, sound, volume, pitch);
}

void UAudioUtil::PlaySoundAtLocation(
	UObject* worldCtx, FLatentActionInfo latentInfo,
	FVector location,
	USoundBase* sound,
	USoundAttenuation* attenuation,
	float volume, float pitch)
{
	if (!IsValid(sound)) return;
	
	UAudioComponent* audioComp = UGameplayStatics::SpawnSoundAtLocation(
		worldCtx, sound, location, FRotator::ZeroRotator,
		1.0, 1.0, 0, attenuation
	);
	
	// Play the audio and set up the latent
	PlaySoundCore(worldCtx, latentInfo, audioComp, sound, volume, pitch);
}
