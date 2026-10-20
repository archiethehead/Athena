#include "Nodes/3D/Node3D.h"

node3D::node3D(const char* newNodeName, glm::vec3 newPosition, glm::vec3 newRotation) : node(newNodeName) {

	memcpy_s(&position, sizeof(position), &newPosition, sizeof(newPosition));
	memcpy_s(&rotation, sizeof(rotation), &newRotation, sizeof(newRotation));

}