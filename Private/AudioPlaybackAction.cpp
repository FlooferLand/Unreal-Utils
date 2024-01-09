#include "AudioPlaybackAction.h"
#include "Components/AudioComponent.h"

FAudioPlaybackAction::FAudioPlaybackAction(FLatentActionInfo& info, UAudioComponent* audioComp, USoundBase* sound) {
	// Creating a new playback object
	AudioComponent = TStrongObjectPtr(audioComp);
	AudioComponent->OnAudioFinishedNative.AddLambda([this] {
		OnAudioFinished();
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

// TODO: Fix this getting called immediately sometimes
void FAudioPlaybackAction::OnAudioFinished() {
	bIsFinished = true;
	FMessageDialog::Debugf(FText::FromString("UAudioPlaybackObject::OnAudioFinished()"));
}

void FAudioPlaybackAction::UpdateOperation(FLatentResponse& response) {	
	// TODO: FIX THIS FUCKERY. USE THE OnAudioFinished DELEGATE INSTEAD
	/*if (isFinished) {
		FMessageDialog::Debugf(FText::FromString("UAudioPlaybackAction->PlayBackObject->bIsFinished"));
	}*/
	response.FinishAndTriggerIf(bIsFinished, ExecutionFunction, OutputLink, CallbackTarget);
}
