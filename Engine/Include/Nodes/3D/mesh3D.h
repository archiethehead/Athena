#pragma once

#include "Nodes/3D/Node3D.h"

class mesh3D : public node3D {

public:
	glm::vec3* polygonArray = nullptr;
	size_t polygonCount = NULL;

	mesh3D(const char* newNodeName, glm::vec3 newPosition, glm::vec3 newRotation, const char* meshFilepath);
	mesh3D() = default;
	~mesh3D() = default;

};