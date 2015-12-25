/*
 * AudioManager.cpp
 *
 *  Created on: 2014. 6. 1.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/FileofSpy/Classes/manager/AudioManager.h"
#include "../ResourcesID.h"

AudioManager::AudioManager() {
	// TODO Auto-generated constructor stub
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.4);
}

AudioManager::~AudioManager() {
	// TODO Auto-generated destructor stub
}

AudioManager* AudioManager::Audiomanager;

void AudioManager::playEffectAudio(int id){
	switch(id){
	case SOUND_CLICK:
		SimpleAudioEngine::sharedEngine()->playEffect("common/sounds/click.ogg");
		break;
	case SOUND_ENEMYHIT:
		SimpleAudioEngine::sharedEngine()->playEffect("gameplay/sounds/hitenemy.ogg");
		break;
	case SOUND_SHOT:
		SimpleAudioEngine::sharedEngine()->playEffect("gameplay/sounds/shotsound.ogg");
		break;
	case SOUND_CARCOME:
			SimpleAudioEngine::sharedEngine()->playEffect("gameplay/sounds/carcome.ogg");
			break;
	case SOUND_SIREN:
			SimpleAudioEngine::sharedEngine()->playEffect("gameplay/sounds/siren.ogg");
			break;
	case SOUND_RESULT:
		SimpleAudioEngine::sharedEngine()->playEffect("gameplay/sounds/cash.ogg");
		break;
	default:

		break;
	}

}
void AudioManager::playSound(int id){
	switch(id){
	case SOUND_INTRO:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("common/sounds/intro.mp3",false);
			break;
	case SOUND_MENUAUDIO:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mainmenu/sounds/startmenu.mp3",true);
		break;
	case SOUND_STOREAUDIO:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("store/sounds/store.mp3",true);
		break;
	case SOUND_READYAUDIO:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameplay/sounds/ready.mp3",true);
		break;
	case SOUND_PALYAUDIO_1:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameplay/sounds/stage1.mp3",true);
		break;
	case SOUND_PALYAUDIO_2:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameplay/sounds/stage2.mp3",true);
		break;
	case SOUND_PALYAUDIO_3:
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameplay/sounds/stage3.mp3",true);
		break;
	case SOUND_COMEBACK:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameplay/sounds/comeback.mp3",true);
			break;
	default:

		break;
	}
}
void AudioManager::pauseSound(){
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}
void AudioManager::stopSound(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}
void AudioManager::resumeSound(){
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
void AudioManager::preloadSound(int id){

}
void AudioManager::clearSound(int id){

}
bool AudioManager::isPlaySound(){
return SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}
void AudioManager::setSFXvolume(float value)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(value/10.0);
}

