// a scene used for transitioning to another scene, since scene transitions were causing problems.
#pragma once

#include "cocos2d.h"

using namespace cocos2d;

typedef class MSQ_TransitionerScene : public Scene
{
public:
	MSQ_TransitionerScene();

	// Creates a gameplay scene.
	static Scene* createScene();

	// called when the scene is entered
	void onEnter();

	// initialization functions
	bool init(); // what's called when the Cocos2D-X scene is created.

	// sets the scene to be switched to. If 'sceneTransition' is a nullptr, then a transition isn't used.
	void switchScene(Scene * newScene, TransitionScene * sceneTransition = nullptr, float speed = 1.0F);

	// gets the scene that this object will be transitioning to.
	Scene * getScene() const;

	// an update loop that does nothing.
	void update(float deltaTime);
	

	CREATE_FUNC(MSQ_TransitionerScene);

private:
	Director * director; // engine

	Scene * nextScene = nullptr;
	TransitionScene * transition = nullptr;


	bool switchScenes; // becomes 'true' when the scenes are being switched.

	float speed = 1.0F;

protected:

} TransitionerScene;

