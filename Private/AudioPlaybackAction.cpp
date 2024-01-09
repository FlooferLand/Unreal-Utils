#include "AudioPlaybackAction.h"
#include "Components/AudioComponent.h"

FAudioPlaybackAction::FAudioPlaybackAction(const FLatentActionInfo& info, UAudioComponent* audioComp, USoundBase* sound) {
	// Safety guard
	AudioComponent = TStrongObjectPtr(audioComp);
	if (!IsValid(audioComp)) {
		UE_LOG(LogTemp, Error, TEXT("No audio component set"));
		return;
	}

	// Binding
	AudioComponent->OnAudioFinishedNative.AddLambda([this](UAudioComponent* comp) {
		this->bIsFinished = true;
	});
	
	// Playing the audio
	if (IsValid(sound)) {
		AudioComponent->SetSound(sound);
		AudioComponent->Play();
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
