#include "AudioPlaybackAction.h"
#include "Components/AudioComponent.h"

FAudioPlaybackAction::FAudioPlaybackAction(FLatentActionInfo& info, UAudioComponent* audioComp, USoundBase* sound) {
	AudioComponent = TStrongObjectPtr(audioComp);
	AudioComponent->OnAudioFinishedNative.AddLambda([this](UAudioComponent* comp) {
		this->bIsFinished = true;
		FMessageDialog::Debugf(FText::FromString("OnAudioFinishedNative"));
	});
	
	Play(sound);

	// Latent stuff
	ExecutionFunction = info.ExecutionFunction;
	OutputLink = info.Linkage;
	CallbackTarget = info.CallbackTarget;
}

void FAudioPlaybackAction::Play(USoundBase* sound) {
	// Safety guard
	if (!AudioComponent) {
		UE_LOG(LogTemp, Error, TEXT("No audio component set"));
		return;
	}
	
	// Playing the audio
	if (IsValid(sound)) {
		AudioComponent->SetSound(sound);
		AudioComponent->Play();
	} else {
		UE_LOG(LogTemp, Error, TEXT("No audio sound clip"));
	}
}

void FAudioPlaybackAction::UpdateOperation(FLatentResponse& response) {
	response.FinishAndTriggerIf(bIsFinished, ExecutionFunction, OutputLink, CallbackTarget);
}
