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
	Scene* _new = MSQ_TransitionerScene::createScene(); //For switching scenes

} MainMenu;