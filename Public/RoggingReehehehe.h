#pragma once

/**
 * Scooby-doo approved logging struct
 */
struct FRoggingReehehehe {
protected:
	static FString LogCore(const FString& content, const FString& mark, const ELogVerbosity::Type verbosity, FColor color) {
		GLog->Logf(verbosity, TEXT("%s"), *content);
		return content;
	}
	
public:
	template <typename T>
	static void Info(T&& content) {
		LogCore(content, "INFO", ELogVerbosity::Log, FColor::White);
	}

	static void Warn(const FString& content) {
		const FString message = LogCore(content, "WARN", ELogVerbosity::Warning, FColor::Yellow);
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message);
		}
	}

	static void Error(const FString& content) {
		const FString message = LogCore(content, "ERR", ELogVerbosity::Error, FColor::Red);
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Red, message);
#else
		FMessageDialog::Open(EAppMsgCategory::Error, EAppMsgType::Type::Ok, FText::FromString(message));
#endif
	}

	template <typename T>
	static void ShitTheBed(const FString& content) {
		const FString message = LogCore(content, "FAT_ERR", ELogVerbosity::Error, FColor::Red);
		UE_LOG(LogTemp, Fatal, TEXT("%s"), *message);
		FMessageDialog::Open(EAppMsgCategory::Error, EAppMsgType::Type::Ok, FText::FromString(message));
	}
};
