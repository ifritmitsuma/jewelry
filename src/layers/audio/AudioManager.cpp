#include <layers/audio/AudioManager.h>
#include <layers/audio/sdl/SDLAudio.h>

using namespace layers;

Audio* AudioManager::audio = SDLAudio::getAudio();

void AudioManager::free() {
	audio->onClose();
}

void AudioManager::play(const std::string soundName, const bool loop) {
	audio->play(soundName, loop);
}

void AudioManager::play(const media::Sound* sound, const bool loop) {
	audio->play(sound, loop);
}

void AudioManager::resume(const std::string soundName, const bool loop) {
	audio->resume(soundName, loop);
}

void AudioManager::resume(const media::Sound* sound, const bool loop) {
	audio->resume(sound, loop);
}

void AudioManager::pauseMusic() {
	audio->pauseMusic();
}

void AudioManager::stopMusic() {
	audio->stopMusic();
}