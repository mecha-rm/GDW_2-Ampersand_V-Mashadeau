#include "scenes/MSQ_TransitionerScene.h"

#include "scenes/MSQ_GameplayScene.h"


// constructor
MSQ_TransitionerScene::MSQ_TransitionerScene() { nextScene = MSQ_GameplayScene::createScene(); }

Scene * MSQ_TransitionerScene::createScene()
{
	Scene * scene = Scene::create();
	
	MSQ_TransitionerScene * layer = MSQ_TransitionerScene::create();
	
	scene->addChild(layer); // adds the layer to the scene.

	return scene;
}

void MSQ_TransitionerScene::onEnter() { Scene::onEnter(); }

void MSQ_TransitionerScene::onExit() { Scene::onExit(); }

bool MSQ_TransitionerScene::init()
{
	// Ensures the parent init function was called first. If it wasn't, this one is exited.
	if (!Scene::init())
		return false;

	director = Director::getInstance();

	// Let cocos know that the init function was successful
	return true;
}

// sets the scene to transition to.
void MSQ_TransitionerScene::switchScene(Scene * newScene, TransitionScene * sceneTransition, float speed)
{
	nextScene = newScene; // saves the scene to transition to next.
	// Director::getInstance()->replaceScene(sceneTransition->create(speed, nextScene));
}

// gets the scene being transitioned to.
Scene * MSQ_TransitionerScene::getScene() const { return nextScene; }

void MSQ_TransitionerScene::update(float deltaTime)
{

	if (nextScene != nullptr && switchScenes == false)
	{
		Director::getInstance()->replaceScene(nextScene);
		//vDirector::getInstance()->replaceScene(transition->create(speed, nextScene));
		switchScenes = true;
	}
}
