#include "AudioPlaybackAction.h"

#include "BackendUtil.h"
#include "Components/AudioComponent.h"

FAudioPlaybackAction::FAudioPlaybackAction(const FLatentActionInfo& info, UAudioComponent* audioComp, USoundBase* sound) {
	// Safety guard
	AudioComponent = TStrongObjectPtr(audioComp);
	if (!IsValid(audioComp)) {
		BackendUtil::LogError("No audio component passed to AudioPlaybackAction");
		return;
	}
	if (!IsValid(sound)) {
		BackendUtil::LogError("No sound passed to AudioPlaybackAction");
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
