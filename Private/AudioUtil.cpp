#include "AudioUtil.h"

#include "AudioPlaybackAction.h"

void UAudioUtil::PlaySoundCore(
	UObject* world_ctx, FLatentActionInfo latent_info,
	UAudioComponent* audio_comp,
	USoundBase* sound,
	float volume, float pitch)
{
	// World stuff
	UWorld* world = world_ctx->GetWorld();
	if (!world) return;
	
	// Spawning the action
	FLatentActionManager& action_manager = world->GetLatentActionManager();
	if (action_manager.FindExistingAction<FPendingLatentAction>(latent_info.CallbackTarget.Get(), latent_info.UUID) == nullptr)
	{
		FAudioPlaybackAction* action = new FAudioPlaybackAction(
			latent_info, audio_comp, sound, volume, pitch
		);
		action_manager.AddNewAction(latent_info.CallbackTarget.Get(), latent_info.UUID, action);
	}
}

void UAudioUtil::PlaySoundOnComponent(
	UObject* world_ctx, FLatentActionInfo latent_info,
	UAudioComponent* audio_comp,
	USoundBase* sound,
	float volume, float pitch)
{
	if (!IsValid(sound) || !IsValid(audio_comp)) return;

	// Play the audio and set up the latent
	PlaySoundCore(world_ctx, latent_info, audio_comp, sound, volume, pitch);
}

// TODO: Make this not as messy as it currently is
void UAudioUtil::PlaySoundAttached(
	UObject* world_ctx, FLatentActionInfo latent_info,
	USceneComponent* attach_comp,
	USoundBase* sound,
	USoundAttenuation* attenuation,
	float volume, float pitch)
{
	UAudioComponent* audio_comp = UGameplayStatics::SpawnSoundAttached(
		sound, attach_comp,
		NAME_None, FVector::Zero(), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false,
		volume, pitch, 0, attenuation
	);

	// Play the audio and set up the latent
	PlaySoundOnComponent(world_ctx, latent_info, audio_comp, sound, volume, pitch);
}

void UAudioUtil::PlaySoundAtLocation(
	UObject* world_ctx, FLatentActionInfo latent_info,
	FVector location,
	USoundBase* sound,
	USoundAttenuation* attenuation,
	float volume, float pitch)
{
	UAudioComponent* audio_comp = UGameplayStatics::SpawnSoundAtLocation(
		world_ctx, sound, location, FRotator::ZeroRotator,
		volume, pitch, 0, attenuation
	);
	
	// Play the audio and set up the latent
	PlaySoundOnComponent(world_ctx, latent_info, audio_comp, sound, volume, pitch);
}
