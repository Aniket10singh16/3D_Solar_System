// Entity class is the super class for all entities.
// All common functions, declarions and variables will be defined.
// This class cannot implemented directly and has to be inherited and functions has to be overloaded.


#pragma once
#include<glm/glm.hpp>

class Entity
{
private:
	int numOfVertices;		// Store the num of vertices in the entity
	int numOfIndices;		// Store the num of indices in the entity.

public:
	virtual void buildVertices() = 0;
	virtual void buildIndices() = 0;
};
