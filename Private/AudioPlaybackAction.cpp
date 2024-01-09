﻿#include "AudioPlaybackAction.h"
#include "Components/AudioComponent.h"

FAudioPlaybackAction::FAudioPlaybackAction(FLatentActionInfo& info, UAudioComponent* audioComp, USoundBase* sound) {
	// Safety guard
	if (!IsValid(audioComp)) {
		UE_LOG(LogTemp, Error, TEXT("No audio component set"));
		return;
	}

	// Binding
	audioComp->OnAudioFinishedNative.AddLambda([this](UAudioComponent* comp) {
		this->bIsFinished = true;
		FMessageDialog::Debugf(FText::FromString("OnAudioFinishedNative"));
	});
	
	// Playing the audio
	if (IsValid(sound)) {
		audioComp->SetSound(sound);
		audioComp->Play();
	} else {
		UE_LOG(LogTemp, Error, TEXT("No audio sound clip"));
	}

	// Latent stuff
	ExecutionFunction = info.ExecutionFunction;
	OutputLink = info.Linkage;
	CallbackTarget = info.CallbackTarget;
}

void FAudioPlaybackAction::UpdateOperation(FLatentResponse& response) {
	response.FinishAndTriggerIf(bIsFinished, ExecutionFunction, OutputLink, CallbackTarget);
}
