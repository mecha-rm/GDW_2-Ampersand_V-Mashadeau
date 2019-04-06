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

// This class is used for the main menu, which we could not complete in time.
#pragma once

#include "cocos2d.h"
#include "audio/AudioLibrary.h"
#include "KeyboardListener.h"

#include "scenes/MSQ_TransitionerScene.h"
#include "scenes/MSQ_GameplayScene.h"

using namespace cocos2d;

typedef class MSQ_MainMenu : public cocos2d::Scene {
public:
	MSQ_MainMenu();

	static cocos2d::Scene* createScene();

	virtual bool init();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event); //Key presses
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event); //Key releases

	// implement the "static create()" method manually
	CREATE_FUNC(MSQ_MainMenu);


private:
	OOP::KeyboardListener keyboard;
	Scene* _new = MSQ_TransitionerScene::createScene(); // for switching scenes
	Scene* msq_gps = MSQ_GameplayScene::createScene();

} MainMenu;