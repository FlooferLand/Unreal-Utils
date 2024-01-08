#pragma once
#include "AudioPlaybackObject.h"
#include "LatentActions.h"

class FAudioPlaybackAction : public FPendingLatentAction {
public:
	// Variables
	TStrongObjectPtr<UAudioPlaybackObject> PlaybackObject = nullptr;

	// Latent variables
	FName ExecutionFunction;
	int32 OutputLink;
	TObjectPtr<UObject> CallbackTarget;
	
	// Construction / functions
	FAudioPlaybackAction(
		FLatentActionInfo& info,
		UAudioComponent* audioComp,
		USoundBase* sound)
	{
		// Creating a new playback object
		PlaybackObject = TStrongObjectPtr(NewObject<UAudioPlaybackObject>());
		PlaybackObject->Initialize(audioComp);
		PlaybackObject->Play(sound);

		// Latent stuff
		ExecutionFunction = info.ExecutionFunction;
		OutputLink = info.Linkage;
		CallbackTarget = info.CallbackTarget;
	}

	virtual void UpdateOperation(FLatentResponse& response) override {
		// TODO: FIX THIS FUCKERY. USE THE OnAudioFinished DELEGATE INSTEAD
		//const bool is_finished = !PlaybackObject->AudioComponent->IsPlaying();
		bool isFinished = PlaybackObject->bIsFinished;
		response.FinishAndTriggerIf(isFinished, ExecutionFunction, OutputLink, CallbackTarget);
	}
};
