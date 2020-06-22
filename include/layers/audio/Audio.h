#pragma once
#include <layers/Layer.h>
#include <media/Sound.h>

namespace layers {

	class Audio : public Layer {

	public:

		virtual void initialize() = 0;

		virtual void onClose() const = 0;

		virtual void play(const std::string soundName, const bool loop = false) = 0;

		virtual void play(const media::Sound* sound, const bool loop = false) = 0;

		virtual void resume(const std::string soundName, const bool loop = false) = 0;

		virtual void resume(const media::Sound* sound, const bool loop = false) = 0;

		virtual void pauseMusic() = 0;

		virtual void stopMusic() = 0;

	};

}