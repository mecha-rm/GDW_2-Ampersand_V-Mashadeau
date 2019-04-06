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

// This was meant for the main menu, which was not used in the GDW build.
#include "scenes/MSQ_MainMenu.h"

// constructor
MSQ_MainMenu::MSQ_MainMenu() : keyboard(OOP::KeyboardListener(this)) {}

// creates a menu scene.
Scene* MSQ_MainMenu::createScene() {
	return MSQ_MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MSQ_MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MSQ_MainMenu::init() {
	if (!Scene::init()) return false;

	//Initializes keyboard listener
	keyboard.setLabelVisible(false);
	keyboard.getListener()->onKeyPressed = CC_CALLBACK_2(MSQ_MainMenu::onKeyPressed, this);
	keyboard.getListener()->onKeyReleased = CC_CALLBACK_2(MSQ_MainMenu::onKeyReleased, this);
	keyboard.getListener()->setEnabled(true);

	//Initializes music (just the Earth track)
	Music titleMusic("Mashadeau_4_Earth");
	titleMusic.preload();
	titleMusic.play();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//ENTER TO NEW GAME
	auto label0 = Label::createWithTTF("PRESS ENTER TO START NEW GAME", "fonts/BRITANIC.TTF", 24);
	if (label0 == nullptr) problemLoading("'fonts/BRITANIC.TTF'");
	else {
		label0->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 160.0f));

		this->addChild(label0, 1);
	}
	//ESCAPE TO CLOSE
	auto label1 = Label::createWithTTF("PRESS ESCAPE TO CLOSE", "fonts/BRITANIC.TTF", 24);
	if (label1 == nullptr) problemLoading("'fonts/BRITANIC.TTF'");
	else {
		label1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 200.0f));

		this->addChild(label1, 1);
	}
	//Ampersand V (&V) Text
	Label* label2 = Label::createWithTTF("&V (AMPERSAND V)", "fonts/BRITANIC.TTF", 18);
	if (label2 == nullptr) problemLoading("'fonts/BRITANIC.TTF'");
	else {
		label2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 80.0f));

		this->addChild(label2, 1);
	}

	//Mashadeau logo
	auto sprite = Sprite::create("images/mashadeau_logo.png");
	if (sprite == nullptr) problemLoading("'mashadeau_logo.png'");
	else {
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 80.0f));
		this->addChild(sprite, 0);
	}
	//&V logo
	auto logo = Sprite::create("images/&V_logo.png");
	if (logo == nullptr) problemLoading("'&V_logo.png'");
	else {
		logo->setScale(0.05);
		logo->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + 80.0f));
		this->addChild(logo, 0);
	}
	return true;
}

// When the key has been pressed, certain sounds should play.
void MSQ_MainMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event);

	AudioLibrary::MSQ_ui.preload();
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ENTER:
		AudioLibrary::MSQ_ui.play();
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		AudioLibrary::MSQ_ui.play();
		break;
	}
}

// When the key is released, the proper action actually happens.
void MSQ_MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event);

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ENTER:
		Director::getInstance()->replaceScene(msq_gps);
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	}
}
