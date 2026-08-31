#include "delta.h"
#include "Engine.h"

int main() {
	
	CAthenaEngine Engine = CAthenaEngine::GetEngine();

	if (!Engine.Init(540, 480)) return -1;

	while (true) {

		Engine.Update(CDelta::GetDeltaTime());

	}

	return 0;

}