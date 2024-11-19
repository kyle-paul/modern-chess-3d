#include "Core/Debug/Logging.h"
#include <csignal>

#define DEBUG

#ifdef DEBUG
	#define ENABLE_ASSERTS
#endif

#ifdef ENABLE_ASSERTS
    #ifdef _MSC_VER
        #define DEBUG_BREAK() __debugbreak()
    #else
        #define DEBUG_BREAK() raise(SIGTRAP)
    #endif

    #define ASSERT_NO_MESSAGE(condition) { if(!(condition)) { ERROR("Assertion Failed!"); DEBUG_BREAK(); } }
	#define ASSERT_MESSAGE(condition, ...) { if(!(condition)) { ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK(); } }

	#define ASSERT_RESOLVE(arg1, arg2, macro, ...) macro

	#define ASSERT(...) ASSERT_RESOLVE(__VA_ARGS__, ASSERT_MESSAGE, ASSERT_NO_MESSAGE)(__VA_ARGS__)
	#define CORE_ASSERT(...) ASSERT_RESOLVE(__VA_ARGS__, ASSERT_MESSAGE, ASSERT_NO_MESSAGE)(__VA_ARGS__)

#else
    #define ASSERT(x, ...)
    #define CORE_ASSERT(x, ...)
#endif