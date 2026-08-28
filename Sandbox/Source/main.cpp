#include "delta.h"
#include <..\..\Engine\Include\Engine.h>

int main() {
	
	CAthenaEngine NewEngine = CAthenaEngine();

	while (true) {

		NewEngine.Update(CDelta::GetDeltaTime());

	}

	return 0;

}