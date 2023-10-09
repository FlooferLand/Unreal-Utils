#include "AudioUtil.h"

void UAudioUtil::PlaySoundOnComponent(
	EFinishedBranch& branch,
	USoundBase* sound,
	UAudioComponent* audio_comp,
	float volume, float pitch
) {
	if (!(sound && audio_comp)) return;

	// Getting a smart reference to the branch
	// FIXME: Doesn't work!! Can't convert the ref to a TSharedPtr without it copying the value
	TSharedPtr<EFinishedBranch> branch_ptr(&branch, [](EFinishedBranch*) {});
	// TSharedPtr<EFinishedBranch> branch_ptr = MakeShareable(&branch);
	
	// Make a new playback handler
	UAudioUtilPlayer* playbackHandler = NewObject<UAudioUtilPlayer>();
	playbackHandler->Initialize(branch_ptr, audio_comp);
	playbackHandler->SetDetails(volume, pitch);

	// Playing the audio
	playbackHandler->Play(sound);	
}

void UAudioUtil::PlaySoundAttached(
	EFinishedBranch& branch,
	USoundBase* sound,
	USceneComponent* attach_comp,
	USoundAttenuation* attenuation,
	float volume, float pitch
) {
	if (!(sound && attach_comp)) return;

	// TODO: Set attenuation on the audio component
	UAudioComponent* audio_comp = UGameplayStatics::SpawnSoundAttached(sound, attach_comp);
	PlaySoundOnComponent(branch, sound, audio_comp, volume, pitch);
}
