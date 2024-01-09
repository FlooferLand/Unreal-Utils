#pragma once
#include "LatentActions.h"

class FAudioPlaybackAction : public FPendingLatentAction {
public:
	// Variables
	bool bIsFinished = false;

	// Latent variables
	FName ExecutionFunction;
	int32 OutputLink;
	TObjectPtr<UObject> CallbackTarget;
	
	// Construction / methods
	FAudioPlaybackAction(FLatentActionInfo& info, UAudioComponent* audioComp, USoundBase* sound);
	virtual void UpdateOperation(FLatentResponse& response) override;
};
