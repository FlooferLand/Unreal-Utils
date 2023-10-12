#pragma once
#include "AudioPlaybackObject.h"
#include "LatentActions.h"
#include "Components/AudioComponent.h"

class FAudioPlaybackAction : public FPendingLatentAction
{
public:
	// Variables
	TStrongObjectPtr<UAudioPlaybackObject> PlaybackObject = nullptr;

	// Latent variables
	FName ExecutionFunction;
	int32 OutputLink;
	TObjectPtr<UObject> CallbackTarget;
	
	// Construction / functions
	FAudioPlaybackAction(
		const FLatentActionInfo& info,
		UAudioComponent* audio_comp,
		USoundBase* sound,
		float volume, float pitch)
	{
		// Creating a new playback object
		PlaybackObject = TStrongObjectPtr(NewObject<UAudioPlaybackObject>());
		PlaybackObject->Initialize(audio_comp);
		PlaybackObject->Play(sound, volume, pitch);

		// Latent stuff
		ExecutionFunction = info.ExecutionFunction;
		OutputLink = info.Linkage;
		CallbackTarget = info.CallbackTarget;
	}

	virtual void UpdateOperation(FLatentResponse& response) override
	{
		// TODO: FIX THIS FUCKERY. USE THE OnAudioFinished DELEGATE INSTEAD
		//const bool is_finished = !PlaybackObject->AudioComponent->IsPlaying();
		bool is_finished = PlaybackObject->bIsFinished;
		response.FinishAndTriggerIf(is_finished, ExecutionFunction, OutputLink, CallbackTarget);
	}
};
