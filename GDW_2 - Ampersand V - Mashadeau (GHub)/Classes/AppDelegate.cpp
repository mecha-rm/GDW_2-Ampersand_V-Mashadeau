/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "scenes/MSQ_MainMenu.h" //Main menu scene
#include "scenes/MSQ_GameplayScene.h" // the gameplay scene

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

// Our screen resolution is (1920, 1080)
// static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size designResolutionSize = cocos2d::Size(1800, 960);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1800, 960);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// This is the default code that comes with cocos for creating a window. The method used to make the game window is the one used in the Upset Avians example.
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    // controls what kind of gl view is opened. Only use one.
	if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("GDW_2 - Ampersand V - Mashadeau", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height), 1.0F, true); // creates a resizable cocos window
		// glview = GLViewImpl::createWithFullScreen("GDW_2 - Ampersand V - Mashadeau"); // creates a cocos window as a full screen
		// glview = GLViewImpl::createWithRect("GDW_2 - Ampersand V - Mashadeau", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height)); // creates a regular cocos window.
#else
        glview = GLViewImpl::create("GDW_2 - Ampersand V - Mashadeau");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();
	
    // create a scene. it's an autorelease object
	auto scene = MSQ_GameplayScene::createScene();
	auto _menu = MSQ_MainMenu::createScene();
	// auto scene = HelloWorld::createScene();
	
	bool stats = false; // set it to 'true' if you want the stats to be visisble.
	
	if (stats)
	{
		director->setDisplayStats(true); // turn on display FPS
		director->setAnimationInterval(1.0f / 60); // set FPS. the default value is 1.0/60 if you don't call this
	}
	
    // run
	//director->runWithScene(_menu); //USE THIS TO RUN FROM MAIN MENU
    director->runWithScene(scene); //USE THIS TO RUN FROM GAMEPLAYSCENE
	
	/*
	// Creating the cocos window.
	Director* director = Director::getInstance();
	auto glview = director->getOpenGLView();

	float width(1900.0F), height(850.0F); // sets the size of the screen

	// DISPLAY->init(960.0f, 540.0f, "100701758 - Essential Mathematics for Games I - Assignment 3", false);

	if (!glview)
	{

		// window name, window sizezoom factor, resizable
		glview = GLViewImpl::createWithRect("Mashadeau", Rect(0.0f, 0.0f, width, height), 1.0f, false);
		director->setOpenGLView(glview);
	}

	// INPUTS->init();

	// Originally took no arguments; now takes the screen width and height
	Scene* scene = MSQ_GameplayScene::createScene(width, height);

	// Scene* scene = MSQ_GameplayScene::createScene();
	director->runWithScene(scene);

	return true;

	// run
	director->runWithScene(scene);
	*/

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
