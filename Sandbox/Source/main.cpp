#include <chrono>
#include <..\..\Engine\Include\Engine.h>

constexpr float g_fMillisecondsInSeconds = 1000.0f;

float g_fDelta = 0.0f;
long long g_llUnixEpochMilliseconds = 0;

int main() {

	std::chrono::milliseconds llMilliseconds = duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	);
	g_llUnixEpochMilliseconds = llMilliseconds.count();
	
	CAthenaEngine NewEngine = CAthenaEngine();

	while (true) {
	
		std::chrono::milliseconds llMilliseconds = duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);

		long long llTimePassed = llMilliseconds.count();

		llTimePassed = llTimePassed - g_llUnixEpochMilliseconds;
		float fSecondsPassed = llTimePassed / g_fMillisecondsInSeconds;

		NewEngine.Update(fSecondsPassed);

		g_llUnixEpochMilliseconds = llMilliseconds.count();

	}

	return 0;

}