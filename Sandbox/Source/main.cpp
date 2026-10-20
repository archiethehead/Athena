#include "delta.h"
#include "Engine.h"
#include "Nodes/3D/Node3D.h"
#include "glm.hpp"
#include <cstdio>

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
	node3D newNode = node3D("New Node", glm::vec3(1.0f,2.0f,3.45644f), glm::vec3(1.0f, 1.0f, 1.0f));
	printf("Name: %s \nX: %f \nY: %f \nZ: %f \nID: %llu", newNode.name, newNode.position.x, newNode.position.y, newNode.position.z, newNode.uid);

	if (!engine.init(540, 480)) return -1;

	while (true) {

		engine.update(CDelta::GetDeltaTime());

	}

	return 0;

}