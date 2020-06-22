#pragma once
#include <media\Sound.h>
#include <layers\audio\Audio.h>

namespace layers {

	/**
	 * Class AudioManager
	 *
	 * Manages the Audio Layer
	 */
	class AudioManager {

	private:

		// The audio plugin
		static Audio* audio;

	public:

		/**
		*	Free any resources held by this manager
		*/
		static void free();

		/**
		*	Plays a sound or music
		*
		*	@param soundName The sound name
		*	@param loop whether or not to loop the sound/music
		*/
		static void play(const std::string soundName, const bool loop = false);

		/**
		*	Plays a sound or music
		*
		*	@param sound The sound
		*	@param loop whether or not to loop the sound/music
		*/
		static void play(const media::Sound* sound, const bool loop = false);

		/**
		*	Resumes the music playing, or plays the given one if there is no music paused
		*
		*	@param soundName The sound name
		*	@param loop whether or not to loop the sound/music
		*/
		static void resume(const std::string soundName, const bool loop = false);

		/**
		*	Resumes the music playing, or plays the given one if there is no music paused
		*
		*	@param sound The sound
		*	@param loop whether or not to loop the sound/music
		*/
		static void resume(const media::Sound* sound, const bool loop = false);

		/**
		*	Pauses the music
		*/
		static void pauseMusic();

		/**
		*	Stops the music
		*/
		static void stopMusic();

	};

}