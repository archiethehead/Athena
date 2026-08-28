#include "delta.h"

long long  CDelta::s_llUnixEpochMilliseconds = 0;

float CDelta::GetDeltaTime() {

	std::chrono::milliseconds llMilliseconds = duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	);

	long long llCurrentUnixTime = llMilliseconds.count();

	long long llTimePassed = llCurrentUnixTime - CDelta::s_llUnixEpochMilliseconds;
	float fSecondsPassed = llTimePassed / MILLISECONDS_IN_SECONDS;

	CDelta::s_llUnixEpochMilliseconds = llCurrentUnixTime;

	return fSecondsPassed;

}