#include "RoggingReehehehe.h"

template <typename T>
FString FRoggingReehehehe::LogCore(const T&& content, const FString& mark, const ELogVerbosity::Type verbosity, FColor color) {
	const FString message = FormatArg(Forward<T>(content));
	GLog->Logf(verbosity, TEXT("%s"), *message);
	return message;
}

template <typename T>
void FRoggingReehehehe::Info(T&& content) {
	LogCore(content, "INFO", ELogVerbosity::Log, FColor::White);
}

template <typename T>
void FRoggingReehehehe::Warn(T&& content) {
	const FString message = LogCore(content, "WARN", ELogVerbosity::Warning, FColor::Yellow);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message);
	}
}

template <typename T>
void FRoggingReehehehe::Error(T&& content) {
	const FString message = LogCore(content, "ERR", ELogVerbosity::Error, FColor::Red);
#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Red, message);
#else
	FMessageDialog::Open(EAppMsgCategory::Error, EAppMsgType::Type::Ok, FText::FromString(message));
#endif
}

template <typename T>
void FRoggingReehehehe::ShitTheBed(T&& content) {
	const FString message = LogCore(content, "FAT_ERR", ELogVerbosity::Error, FColor::Red);
	UE_LOG(LogTemp, Fatal, TEXT("%s"), *message);
	FMessageDialog::Open(EAppMsgCategory::Error, EAppMsgType::Type::Ok, FText::FromString(message));
}
