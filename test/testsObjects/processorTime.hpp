#pragma once

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

inline unsigned long long get_processor_time(){
	return __rdtsc();
}