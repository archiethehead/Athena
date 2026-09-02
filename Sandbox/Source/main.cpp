#include "delta.h"
#include "Engine.h"

#ifdef _WIN32

	#ifndef _DEBUG

		#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

	#endif //ifdef _DEBUG

#endif // ifdef _WIN32


int main() {
	
	CAthenaEngine Engine = CAthenaEngine::GetEngine();

	if (!Engine.Init(540, 480)) return -1;

	while (true) {

		Engine.Update(CDelta::GetDeltaTime());

	}

	return 0;

}