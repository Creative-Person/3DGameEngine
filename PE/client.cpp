#include "./headers/Game.h"
#include "./headers/Timer.h"
#include "./headers/MeshBuildStrategy.h"
#include "./headers/VertexArrayBuildStrategy.h"
#include "./headers/StaticObject.h"
#include "./headers/LineRenderStrategy.h"
#include "./headers/MaterialRenderStrategy.h"

#include <stdio.h>

SceneNode* rocket;

class MyTimer : public Timer
{
public:
	MyTimer(int ticks, int interval)
	: Timer(ticks, interval)
	{

	}

	virtual void tick()
	{
		printf("tick!\n");
		rocket->move(SimplePoint(0,0,-0.1));
	}
};

class MyGame : public Game
{

public:
	virtual void initializeGame(GameConfig* config)
	{
		this->getTimerClock()->addTimer(new MyTimer(1000, 1000));
		MeshBuildStrategy* mbs = dynamic_cast<MeshBuildStrategy*>(new VertexArrayBuildStrategy());
		StaticObject* sn = new StaticObject(this->getOBJPool()->getMesh(mbs, "./resources/obj/rocket.obj"));
		sn->setRenderStrategy(dynamic_cast<RenderStrategy*>(new MaterialRenderStrategy()));
		this->getScene()->getRoot()->addNode(sn);
		rocket = dynamic_cast<SceneNode*>(sn);
	}
};
int main()
{
	MyGame m;
	m.start();
}