#pragma once
#include "AudioEngine.h"

class Sound {
public: 
	Sound(std::string _effect);
	~Sound();

	void play();
	void stop();

private:
	std::string effect;
};

class Music {
public: 
	Music(std::string _AIN);
	~Music();

	void play();
	void stop();

private: 
	std::string AIN;
};