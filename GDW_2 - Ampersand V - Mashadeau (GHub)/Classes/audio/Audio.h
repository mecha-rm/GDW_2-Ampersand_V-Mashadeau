#pragma once
#include "AudioEngine.h"

void profileSetup();

class Sound {
public: 
	Sound(std::string _effect, bool _loop);
	~Sound();

	void preload();
	void uncache();
	void play();
	void resume();
	void pause();
	void stop();
	void end();

private:
	std::string effect;
	int id;
	bool loop;
};

class Music {
public: 
	Music(std::string _AIN);
	~Music();
	
	void preload();
	void uncache();
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