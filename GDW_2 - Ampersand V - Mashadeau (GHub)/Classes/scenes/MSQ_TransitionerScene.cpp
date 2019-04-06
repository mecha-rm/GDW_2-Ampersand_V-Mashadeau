/*
Project: Mashadeau: Sorcerer's Quest (Game Development Workshop II (INFR 1396U) Video Game)
Team: Ampersand V (&V)
	- Caleb Birnie (100699828)
	- Carter Menary (100700587)
	- Devin Fitzpatrick (100709082)
	- Nathan Tuck (100708651)
	- Roderick “R.J.” Montague (100701758)
	- Jason Lee (100698121)
		*Jason Lee was only part of this group for the purposes of Digital Game Design.
		*Jason is not in Essential Mathematics for Games II, Object Oriented Programming, or Game Development Workshop II.
Date: 04/03/2019
*/

// This scene was meant to handle transitions when we were having issues, but these problems were resolved, and this scene is no longer needed. You can ignore this.
#include "scenes/MSQ_TransitionerScene.h"
#include "scenes/MSQ_GameplayScene.h"


// constructor
MSQ_TransitionerScene::MSQ_TransitionerScene() { nextScene = MSQ_GameplayScene::createScene(); }

// creates the scene
Scene * MSQ_TransitionerScene::createScene()
{
	Scene * scene = Scene::create();
	
	MSQ_TransitionerScene * layer = MSQ_TransitionerScene::create();
	
	scene->addChild(layer); // adds the layer to the scene.

	return scene;
}

// called upon entry
void MSQ_TransitionerScene::onEnter() { Scene::onEnter(); }

// called upon exit
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
	// Director::getInstance()->replaceScene(sceneTransition->create(speed, nextScene)); // this was meant to start the transition.
}

// gets the scene being transitioned to.
Scene * MSQ_TransitionerScene::getScene() const { return nextScene; }

void MSQ_TransitionerScene::update(float deltaTime)
{

	if (nextScene != nullptr && switchScenes == false) // provents overlapping transitions.
	{
		Director::getInstance()->replaceScene(nextScene);
		//vDirector::getInstance()->replaceScene(transition->create(speed, nextScene));
		switchScenes = true;
	}
}
