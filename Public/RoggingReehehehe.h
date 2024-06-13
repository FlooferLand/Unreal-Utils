#pragma once

/**
 * Scooby-doo approved logging struct
 */
struct FRoggingReehehehe {
protected:
	template<typename T>
	static FString LogCore(const T&& content, const FString& mark, const ELogVerbosity::Type verbosity, FColor color);
	
public:
	template<typename T>
	static void Info(T&& content);
	
	template<typename T>
	static void Warn(T&& content);
	
	template<typename T>
	static void Error(T&& content);
	
	template<typename T>
	static void ShitTheBed(T&& content);
};
