#pragma once
#include "LatentActions.h"

class FAudioPlaybackAction final : public FPendingLatentAction {
public:
	// Variables
	TStrongObjectPtr<UAudioComponent> AudioComponent = nullptr;
	bool bIsFinished = false;

	// Latent variables
	FName ExecutionFunction;
	int32 OutputLink;
	TObjectPtr<UObject> CallbackTarget;
	
	// Construction / methods
	FAudioPlaybackAction(const FLatentActionInfo& info, UAudioComponent* audioComp, USoundBase* sound);
	virtual void UpdateOperation(FLatentResponse& response) override;
};
