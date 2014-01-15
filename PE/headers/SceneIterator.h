#ifndef SCENEITERATOR_H
#define SCENEITERATOR_H

#include <vector>
#include "SceneNode.h"

class SceneIterator
{
	SceneNode* current;
	std::vector<std::pair<SceneNode*,int>> path;
public:
	SceneNode* next();
	SceneNode* end(); 
	bool hasNext();
};

#endif