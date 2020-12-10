#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <string>
#include <map>
#include <memory>
#include <fmod.hpp>
#include <glm/glm.hpp>
#include "AudioBase.h"
#include "../Core/Debug.h"

class AudioHandler
{
public:
	void Update(const float deltaTime_);
	void OnDestroy();

	AudioHandler(const AudioHandler&) = delete;
	AudioHandler(AudioHandler&&) = delete;
	AudioHandler& operator=(const AudioHandler&) = delete;
	AudioHandler& operator=(AudioHandler&&) = delete;

	static AudioHandler* GetInstance();
	bool InitializeAudio(glm::vec3 position_ = glm::vec3(0.0f), glm::vec3 velocity_ = glm::vec3(0.0f), glm::vec3 forwardDirection_ = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 upDirection_ = glm::vec3(0.0f, 1.0f, 0.0f));

//private:
    AudioHandler();
    ~AudioHandler();

    static std::unique_ptr<AudioHandler> audioHandlerInstance;
    friend std::default_delete<AudioHandler>;

    friend class AudioSource;

    //updates channel position and velocity
    void UpdateChannelPositionVelocity(int channelID_, glm::vec3 newPos_, glm::vec3 newVel_ = glm::vec3(0.0f));

    //glm::vec3 to an FMOD_VECTOR
    FMOD_VECTOR* glmToFMOD(glm::vec3 vec3_);

    //load the Sound to play
    void LoadSound(std::string audioName_, bool loop_, bool audio3D_, bool compressedAudio_);

    //play a certain sound with the channelID
    int PlaySound(std::string audioName_, glm::vec3 audioPos_, glm::vec3 audioVel_ = glm::vec3(0.0f), float audioVolume_ = 1.0f);

    //returns an FMOD::Sound pointer
    FMOD::Sound* GetSound(std::string audioName_);

    //checks to see if audio is playing
    bool IsPlaying(int channelID_);

    FMOD::System* fmodSystem;

    static std::map<std::string, FMOD::Sound*>audioMap;
    static std::map<int, FMOD::Channel*>channelMap;

    int channelCount;
    int* driverCount;

    bool loopAudio;
    bool audio3D;
    bool audioCompressed;
};
#endif