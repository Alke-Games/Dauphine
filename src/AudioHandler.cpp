#include "AudioHandler.h"
#include "Logger.h"


AudioHandler* AudioHandler::instance = nullptr;


AudioHandler::AudioHandler() :
	currentMusic(nullptr),
	currentEffect(nullptr)
{
	initialize();
}

AudioHandler::~AudioHandler(){
	free();

	if(AudioHandler::instance != nullptr){
		delete AudioHandler::instance;
	}
	
	Mix_CloseAudio();
	Mix_Quit();
}

AudioHandler* AudioHandler::getInstance(){
	if(AudioHandler::instance == nullptr){
		AudioHandler::instance = new AudioHandler();
	}
	
	return AudioHandler::instance;
}

void AudioHandler::initialize(){
	const int frequency = 44100;
	const int channels = 2;
	const int chunksize = 4096;

	const int initialized = Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize);

	if(initialized != 0) {
		Logger::warning("Could not open audio handler.");
		free();
		AudioHandler::instance = nullptr;
	}
}

void AudioHandler::free(){
	if(this->currentMusic != nullptr){
		Mix_FreeMusic(this->currentMusic);
		this->currentMusic = nullptr;
	}
	if(this->currentEffect != nullptr){
		Mix_FreeChunk(this->currentEffect);
		this->currentEffect = nullptr;
	}
}

void AudioHandler::setCurrentMusic(const string& path_){
	if(this->currentMusic != nullptr){
		Mix_FreeMusic(this->currentMusic);
	}

	this->currentMusic = Mix_LoadMUS(path_.c_str());
}

void AudioHandler::playMusic(const int times_){
	if(this->currentMusic){
		Mix_PlayMusic(this->currentMusic, times_);
	}
	else{
		Logger::warning("There is no song loaded.");
	}
}

void AudioHandler::stopMusic(){
	Mix_HaltMusic();	
}

void AudioHandler::setMusicVolume(const unsigned int percent_){
	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(value);
}

void AudioHandler::setCurrentEffect(const string& path_){
	if(this->currentEffect)
		Mix_FreeChunk(this->currentEffect);

	this->currentEffect = Mix_LoadWAV(path_.c_str());
}

void AudioHandler::playEffect(const int times_){
	if(this->currentEffect){
		Mix_PlayChannel(1, this->currentEffect, times_);
	}
	else{
		Logger::warning("There is no effect loaded.");
	}
}

void AudioHandler::setEffectVolume(const unsigned int percent_){
	const int value = percent_ * MIX_MAX_VOLUME/100;
	Mix_Volume(1, value);
}

void AudioHandler::changeMusic(const string& path_){
	stopMusic();
	setCurrentMusic(path_);
	playMusic(MIX_LOOP);
}