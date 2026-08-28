#pragma once

#include <chrono>

constexpr float MILLISECONDS_IN_SECONDS = 1000.0f;

class CDelta {

private:
	static long long s_llUnixEpochMilliseconds;

public:
	static float GetDeltaTime();

};