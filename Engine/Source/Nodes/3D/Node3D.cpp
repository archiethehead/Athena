#include "Nodes/3D/Node3D.h"

node3D::node3D(const char* newNodeName, glm::vec3 newPosition, glm::vec3 newRotation) : node(newNodeName) {

	position = newPosition;
	rotation = newRotation;

}