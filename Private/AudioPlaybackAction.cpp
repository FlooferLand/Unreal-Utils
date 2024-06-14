#include "AudioPlaybackAction.h"

#include "RoggingReehehehe.h"
#include "Components/AudioComponent.h"

FAudioPlaybackAction::FAudioPlaybackAction(const FLatentActionInfo& info, UAudioComponent* audioComp, USoundBase* sound) {
	// Safety guard
	AudioComponent = TStrongObjectPtr(audioComp);
	if (!IsValid(audioComp)) {
		FRoggingReehehehe::Error("No audio component passed to AudioPlaybackAction");
		return;
	}
	if (!IsValid(sound)) {
		FRoggingReehehehe::Error("No sound passed to AudioPlaybackAction");
		return;
	}

	// Binding
	AudioComponent->OnAudioFinishedNative.AddLambda([this](UAudioComponent* _) {
		this->bIsFinished = true;
	});
	
	// Playing the audio
	AudioComponent->SetSound(sound);
	AudioComponent->Play();

	// Latent stuff
	ExecutionFunction = info.ExecutionFunction;
	OutputLink = info.Linkage;
	CallbackTarget = info.CallbackTarget;
}

void FAudioPlaybackAction::UpdateOperation(FLatentResponse& response) {
	response.FinishAndTriggerIf(bIsFinished, ExecutionFunction, OutputLink, CallbackTarget);
}
