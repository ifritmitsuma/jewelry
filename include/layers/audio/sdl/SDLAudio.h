#pragma once
#include <layers/audio/Audio.h>
#include <media/Sound.h>
#include <map>
#include <sdl/SDL_mixer.h>

using namespace media;

namespace layers {

	class SDLAudio : public Audio {

	private:

		std::map<const Sound*, Mix_Music*>* music = new std::map<const Sound*, Mix_Music*>();
		std::map<const Sound*, Mix_Chunk*>* sounds = new std::map<const Sound*, Mix_Chunk*>();
		std::map<const std::string, const media::Sound*>* soundNames = new std::map<const std::string, const media::Sound*>();

		void loadSound(const std::string filename, bool sfx);

	public:

		void initialize() override;

		void onClose() const override;

		void play(const std::string soundName, const bool loop = false) override;

		void play(const media::Sound* sound, const bool loop = false) override;

		void resume(const std::string soundName, const bool loop = false) override;

		void resume(const media::Sound* sound, const bool loop = false) override;

		void pauseMusic() override;

		void stopMusic() override;

		static SDLAudio* getAudio();

	};

}