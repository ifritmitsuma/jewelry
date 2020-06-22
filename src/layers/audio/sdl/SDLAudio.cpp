#include <layers/audio/sdl/SDLAudio.h>
#include <sdl/SDL.h>
#include <sdl/SDL_mixer.h>
#include <map>

using namespace layers;

void SDLAudio::initialize() {

    std::map<std::string, bool>* soundFiles = new std::map<std::string, bool>();
    soundFiles->insert(std::pair<std::string, bool>("song18.mp3", false));
    soundFiles->insert(std::pair<std::string, bool>("song21.mp3", false));
    soundFiles->insert(std::pair<std::string, bool>("Accept.mp3", true));
    soundFiles->insert(std::pair<std::string, bool>("Item2A.wav", true));
    soundFiles->insert(std::pair<std::string, bool>("Menu2A.wav", true));

    //Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    for (const auto& soundFile : *soundFiles) {
        loadSound(soundFile.first, soundFile.second);
    }
}

void SDLAudio::loadSound(std::string filename, bool sfx) {

    Sound* sound = new Sound{ std::string("assets/sound/").append(filename), sfx };

    Mix_Chunk* gSFX = NULL;
    Mix_Music* gMusic = NULL;

    //Load music
    if (sfx) {
        //Load sound effects
        gSFX = Mix_LoadWAV(sound->filename.c_str());

    }
    else {
        gMusic = Mix_LoadMUS(sound->filename.c_str());
    }

    if (gSFX == NULL && gMusic == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else {

        soundNames->insert(std::pair<std::string, const Sound*>(filename, sound));
        if (sfx) {
            sounds->insert(std::pair<Sound*, Mix_Chunk*>(sound, gSFX));
        }
        else {
            music->insert(std::pair<Sound*, Mix_Music*>(sound, gMusic));
        }

    }

}

void SDLAudio::onClose() const {

    for (const auto& m : *music) {
        Mix_FreeMusic(m.second);
    }
    delete music;

    for (const auto& s : *sounds) {
        Mix_FreeChunk(s.second);
    }
    delete sounds;

    //Quit SDL subsystems
    Mix_Quit();

}

void SDLAudio::play(const std::string soundName, const bool loop) {

    play(soundNames->at(soundName), loop);

}

void SDLAudio::play(const media::Sound* sound, const bool loop) {

    if (sound->sfx) {
        Mix_PlayChannel(-1, sounds->at(sound), loop ? -1 : 0);
    }
    else {
        Mix_PlayMusic(music->at(sound), loop ? -1 : 0);
    }

}

void SDLAudio::resume(const std::string soundName, const bool loop) {

    resume(soundNames->at(soundName), loop);

}

void SDLAudio::resume(const media::Sound* sound, const bool loop) {

    if (Mix_PausedMusic() == 1)
    {
        //Resume the music
        Mix_ResumeMusic();
    }
    else {
        play(sound, loop);
    }

}

void SDLAudio::pauseMusic() {
    if (Mix_PlayingMusic() == 1) {
        Mix_PauseMusic();
    }
}

void SDLAudio::stopMusic() {
    if (Mix_PlayingMusic() == 1) {
        Mix_HaltMusic();
    }
}

SDLAudio* SDLAudio::getAudio() {
	SDLAudio* audio = new SDLAudio();
	audio->initialize();
	return audio;
}