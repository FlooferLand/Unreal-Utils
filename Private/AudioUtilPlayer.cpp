#include "AudioUtilPlayer.h"
#include "Kismet/GameplayStatics.h"

void UAudioUtilPlayer::Initialize(TSharedPtr<EFinishedBranch> branch, UAudioComponent* component)
{
	if (!branch.IsValid() || !component) return;
	
	Branch = branch;	
	AudioComponent = component;
}

void UAudioUtilPlayer::Play(USoundBase* sound)
{
	// Safety guard
	if (!AudioComponent) return;
	
	// Playing and hooking audio based on the type
	AudioComponent->SetSound(sound);
	AudioComponent->Play();
	AudioComponent->OnAudioFinished.AddDynamic(this, &UAudioUtilPlayer::OnAudioFinished);
}

void UAudioUtilPlayer::SetDetails(float volume, float pitch, USoundAttenuation* attenuation)
{
	Volume = volume;
	Pitch = pitch;
	Attenuation = attenuation;
}

void UAudioUtilPlayer::OnAudioFinished()
{
#define THE_TEST(a) FString(Branch == nullptr ? "nullptr" : "[IT IS SET]")
	
	// DEBUG/TEST
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.0,
			FColor::Cyan,
			TEXT("[is_branch_set] Before: ") + THE_TEST(Branch)
		);
	}
	
	// Triggering the exec
	Branch = MakeShared<EFinishedBranch>(EFinishedBranch::Finished);

	// DEBUG/TEST
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.0,
			FColor::Cyan,
			TEXT("[is_branch_set] After: ") + THE_TEST(Branch)
		);
	}
	
	// Removing the sound after playback
	// TODO: Should maybe restore it, or not do this at all?
	if (AudioComponent)
		AudioComponent->SetSound(nullptr);

	// DEBUG
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Cyan, TEXT("AudioFinished"));
}
