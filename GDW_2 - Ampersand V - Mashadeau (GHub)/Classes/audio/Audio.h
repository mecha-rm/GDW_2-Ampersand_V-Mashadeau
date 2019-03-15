#pragma once
#include "AudioEngine.h"

void profileSetup();

class Sound {
public: 
	Sound(std::string _effect);
	~Sound();

	void play();
	void resume();
	void pause();
	void stop();
	void end();

private:
	std::string effect;
	int id;
};

class Music {
public: 
	Music(std::string _AIN);
	~Music();

	void play();
	void resume();
	void pause();
	void stop();
	void end();

private: 
	std::string AIN;
	int id;
};

void preload();