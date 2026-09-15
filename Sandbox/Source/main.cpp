#include "delta.h"
#include "Engine.h"

#ifdef _WIN32

	#ifndef _DEBUG

		#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

	#endif //ifdef _DEBUG

#endif // ifdef _WIN32

void Crash(const char* SCrashMessage) {

	printf("%s", SCrashMessage);
	exit(EXIT_FAILURE);

}


int main() {
	
	CAthenaEngine Engine = CAthenaEngine::GetEngine();
	Engine.SetCrashCallback(Crash);

	if (!Engine.Init(540, 480)) return -1;

	while (true) {

		Engine.Update(CDelta::GetDeltaTime());

	}

	return 0;

}