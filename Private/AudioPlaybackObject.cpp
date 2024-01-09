#include "AudioPlaybackObject.h"

void UAudioPlaybackObject::Initialize(UAudioComponent* audioComponent) {
	AudioComponent = audioComponent;
	AudioComponent->OnAudioFinished.AddDynamic(this, &UAudioPlaybackObject::OnAudioFinished);
}

void UAudioPlaybackObject::Play(USoundBase* sound) const {
	// Safety guard
	if (!IsValid(AudioComponent)) {
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
void UAudioPlaybackObject::OnAudioFinished() {
	bIsFinished = true;
	FMessageDialog::Debugf(FText::FromString("UAudioPlaybackObject::OnAudioFinished()"));
}
