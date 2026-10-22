#include "delta.h"
#include "Engine.h"

#ifdef _WIN32

	#ifndef _DEBUG

		#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

	#endif //ifdef _DEBUG

#endif // ifdef _WIN32

void crash() {

	exit(EXIT_FAILURE);

}


int main() {
	
	athenaEngine engine = athenaEngine::GetEngine();
	engine.setCrashCallback(crash);

	if (!engine.init(540, 480)) return -1;

	while (true) {

		engine.update(CDelta::GetDeltaTime());

	}

	return 0;

}