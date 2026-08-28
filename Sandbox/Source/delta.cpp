#include "delta.h"

long long  CDelta::s_llLastFrameUnixEpochMilliseconds = 0;

float CDelta::GetDeltaTime() {

	// https://gist.github.com/juniorcesarabreu/3800502afd96707ebffc337cab8d9185
	std::chrono::milliseconds llMilliseconds = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	long long llCurrentUnixEpochMilliseconds = llMilliseconds.count();
	long long llMillisecondsPassed = llCurrentUnixEpochMilliseconds - CDelta::s_llLastFrameUnixEpochMilliseconds;
	float fSecondsPassed = llMillisecondsPassed / MILLISECONDS_IN_SECONDS;

	CDelta::s_llLastFrameUnixEpochMilliseconds = llCurrentUnixEpochMilliseconds;

	return fSecondsPassed;

}