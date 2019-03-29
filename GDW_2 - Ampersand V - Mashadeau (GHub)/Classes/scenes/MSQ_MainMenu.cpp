#include "scenes/MSQ_MainMenu.h"

MSQ_MainMenu::MSQ_MainMenu() : keyboard(OOP::KeyboardListener(this)) {}

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
	//&V
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

void MSQ_MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event);

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ENTER:
		Director::getInstance()->replaceScene(_new); //move to the tutorial scene. This don't work, but leaving it uncommented for the meme (and the potential to be fixed when I'm more mentally functional)
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	}
}
