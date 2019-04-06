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
// a scene used for transitioning to another scene, since scene transitions were causing problems.
// this was ultimately not used since we figured out what our problem was, but we did not remove it in fear of it breaking.
// this class can pretty much be ignored.
#pragma once

#include "scenes/MSQ_GameplayScene.h"
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

	// called when teh scene is exited.
	void onExit();

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

	Scene * nextScene = nullptr; // what would've been used to save the next scene.
	TransitionScene * transition = nullptr; // the scene transition.


	bool switchScenes; // becomes 'true' when the scenes are being switched.

	float speed = 1.0F; // the transition speed.

protected:

} TransitionerScene;

