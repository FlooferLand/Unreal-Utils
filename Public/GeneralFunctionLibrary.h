#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralFunctionLibrary.generated.h"

/// A bunch of general Blueprint utils
UCLASS()
class UTILITY_API UGeneralFunctionLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void Billboard(USceneComponent* target);
	
	UFUNCTION(BlueprintCallable)
	static void Joeboard(USceneComponent* target);
	
	UFUNCTION(BlueprintCallable)
	static void GoofyAhhBoard(USceneComponent* target);
};
