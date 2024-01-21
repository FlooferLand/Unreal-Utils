#pragma once

class BackendUtil {
public:
	static void LogInfo(const FString& message) {
		const FString debugMessage = "INFO: " + message;
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::White, debugMessage);
	}
	static void LogError(const FString& message) {
		const FString debugMessage = "ERROR: " + message;
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, debugMessage);

		// Make the UE log work
		// UE_LOG(LogTemp, Error, debugMessage.GetCharArray());
	}
};
