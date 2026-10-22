#include "Nodes/3D/mesh3D.h"
#include <cstdio>

mesh3D::mesh3D(const char* newNodeName, glm::vec3 newPosition, glm::vec3 newRotation, const char* meshFilepath) : node3D(newNodeName, newPosition, newRotation) {

	FILE* meshFileptr;
	fopen_s(&meshFileptr, meshFilepath, "rb");

}