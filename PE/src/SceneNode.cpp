#include "../headers/SceneNode.h"
#ifdef _MSC_VER
	#include <Windows.h>
#endif
#include "../headers/SimplePoint.h"
#include <GL\gl.h>
#include <stdlib.h>

ObjectId SceneNode::addNode(SceneNode* child)
{
	this->childs.push_back(child);
	ObjectId obj(this->childs.size() - 1);
	return ObjectId(obj);
}

void SceneNode::removeNode(ObjectId id)
{
	childs.erase(childs.begin() + id.id);
}

void SceneNode::render(RenderClues* rc)
{
	transform();
	for(auto node : childs)
	{
		node->render(rc);
	}
	revertTransform();
}

void SceneNode::update(UpdateClues* uc)
{
	if(uc != NULL)
	{
		absoluteTransform = uc->parentTransform + translation;
		absoluteRotation = uc->parentRotation + rotation;
		absoluteScale = uc->parentScale + scale;
	}
	else
		uc = new UpdateClues();

	uc->parentTransform = absoluteTransform;
	uc->parentRotation = absoluteRotation;
	uc->parentScale = absoluteScale;

	for(auto node : childs)
	{
		node->update(uc);
	}

	if(bb != NULL) 
	{
		bb->translate(absoluteTransform);
	}
}

void SceneNode::setRenderStrategy(RenderStrategy* rs)
{
	this->rs = rs;
}

void SceneNode::transform()
{
	glPushMatrix();		//store matrix
	glTranslatef(translation.x, translation.y, translation.z); //translate
	glRotatef(rotation.x, 1, 0 , 0); //rotate x
	glRotatef(rotation.y, 0, 1 , 0); //rotate y
	glRotatef(rotation.z, 0, 0 , 1); //rotate z
	
	glScalef(scale.x, scale.y, scale.z); //scale
}

void SceneNode::revertTransform()
{
	glPopMatrix();
}

SceneNode::SceneNode()
{
	this->scale = SimplePoint(1,1,1);
}

SceneNode::SceneNode(BoundingBox* bb)
{
	this->scale = SimplePoint(1,1,1);
	this->bb = bb;
}

void SceneNode::move(SimplePoint vector)
{
	translation = translation + vector;
	absoluteTransform = absoluteTransform + vector;
	if(bb != NULL) bb->translate(absoluteTransform);
	update(NULL);
}

void SceneNode::rotate(SimplePoint vector)
{
	rotation = rotation + vector;
	absoluteRotation = absoluteRotation + vector;
	if(bb != NULL) bb->rotate(absoluteRotation);
	update(NULL);
}