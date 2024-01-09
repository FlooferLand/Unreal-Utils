#include "AudioPlaybackAction.h"
#include "Components/AudioComponent.h"

FAudioPlaybackAction::FAudioPlaybackAction(FLatentActionInfo& info, UAudioComponent* audioComp, USoundBase* sound) {
	// Safety guard
	AudioComponent = TStrongObjectPtr(audioComp);
	if (!IsValid(audioComp)) {
		UE_LOG(LogTemp, Error, TEXT("No audio component set"));
		return;
	}

	// Binding
	AudioComponent->OnAudioFinishedNative.AddLambda([this](UAudioComponent* comp) {
		this->bIsFinished = true;
		FMessageDialog::Debugf(FText::FromString("OnAudioFinishedNative"));
	});
	
	// This won't even compile
	/*AudioComponent->OnAudioPlaybackPercentNative.AddLambda([this](USoundWave* sound, float progress) {
		GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Red, FString::SanitizeFloat(progress));
	});*/
	
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
