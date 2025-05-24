#pragma once

// Platform data gathered at compile time

#define SDW_COMPILER_NAME "Unknown"
#define SDW_OS_NAME "Unkown"

#define SDW_OS_LINUX 0
#define SDW_OS_WINDOWS 0

#if defined (__clang__)
#	undef SDW_COMPILER_NAME
#	define SDW_COMPILER_NAME "Clang"
#elif defined (__GNUC__)
#	undef SDW_COMPILER_NAME
#	define SDW_COMPILER_NAME "GNU GCC"
#endif

#if defined (__linux__)
#	undef SDW_OS_NAME
#	define SDW_OS_NAME "Linux"
#	undef SDW_OS_LINUX
#	define SDW_OS_LINUX 1
#elif defined (__WIN32) || defined (__WIN64)
#	undef SDW_OS_NAME
#	define SDW_OS_NAME "Windows"
#	undef SDW_OS_WINDOWS
#	define SDW_OS_WINDOWS 1
#endif

namespace Shadow::Utils {

inline const char* getOSName() { return SDW_OS_NAME; }
inline const char* getCompilerName() { return SDW_COMPILER_NAME; }

}