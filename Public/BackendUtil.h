#pragma once

class BackendUtil {
protected:
	static void LogCore(const FString& message, const FString& mark, const ELogVerbosity::Type verbosity, FColor color) {
		const FString errorMessage = mark + ": " + message;
		GLog->Logf(verbosity, TEXT("%s"), *errorMessage);
		GEngine->AddOnScreenDebugMessage(-1, 5.0, color, errorMessage);
	}
public:
	static void LogInfo(const FString& message) {
		LogCore(message, "INFO", ELogVerbosity::All, FColor::White);
	}
	static void LogWarn(const FString& message) {
		LogCore(message, "WARNING", ELogVerbosity::Warning, FColor::Yellow);
	}
	static void LogError(const FString& message) {
		LogCore(message, "ERROR", ELogVerbosity::Error, FColor::Red);
	}
};
