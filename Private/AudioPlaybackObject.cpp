#include "AudioPlaybackObject.h"

void UAudioPlaybackObject::Initialize(UAudioComponent* audio_component)
{
	AudioComponent = audio_component;
	AudioComponent->OnAudioFinished.AddDynamic(this, &UAudioPlaybackObject::OnAudioFinished);
}

void UAudioPlaybackObject::Play(USoundBase* sound, float volume, float pitch)
{
	// Safety guard
	if (!IsValid(AudioComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("No audio component set"));
		return;
	}
	
	// Setting up audio
	if (IsValid(sound))
		AudioComponent->SetSound(sound);
	else
		UE_LOG(LogTemp, Error, TEXT("No audio sound clip"));
	AudioComponent->VolumeMultiplier = volume;
	AudioComponent->PitchMultiplier = pitch;
	
	// Playing and hooking audio based on the type
	AudioComponent->Play();
}

// TODO: Fix this getting called immediately sometimes
void UAudioPlaybackObject::OnAudioFinished()
{
	bIsFinished = true;
	// FMessageDialog::Debugf(FText::FromString("OnAudioFinished()"));
}
