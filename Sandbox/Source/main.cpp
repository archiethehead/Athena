#include "delta.h"
#include "Engine.h"

int main() {
	
	CAthenaEngine* PNewEngine = CAthenaEngine::GetEngine();

	while (true) {

		PNewEngine->Update(CDelta::GetDeltaTime());

	}

	return 0;

}