#include "AudioHandler.h"

std::map<std::string, FMOD::Sound*>AudioHandler::audioMap = std::map<std::string, FMOD::Sound*>();
std::map<int, FMOD::Channel*>AudioHandler::channelMap = std::map<int, FMOD::Channel*>();

std::unique_ptr<AudioHandler> AudioHandler::audioHandlerInstance = nullptr;

AudioHandler::AudioHandler()
{

}

AudioHandler::~AudioHandler()
{
    OnDestroy();
}

AudioHandler* AudioHandler::GetInstance()
{
	if (audioHandlerInstance.get() == nullptr)
	{
		audioHandlerInstance.reset(new AudioHandler());
	}
	return audioHandlerInstance.get();
}

bool AudioHandler::InitializeAudio(glm::vec3 position_, glm::vec3 velocity_, glm::vec3 forwardDirection_, glm::vec3 upDirection_)
{
	channelCount = -1;
	FMOD::System_Create(&fmodSystem);

    if (FMOD::System_Create(&fmodSystem) != FMOD_OK)
    {
        Debug::Error("Failed to Initialze FMOD!", "AudioHandler.cpp", __LINE__);
        return false;
    }

    if (fmodSystem->getNumDrivers(driverCount) <= 0)
    {
        Debug::Error("There are ", "AudioHandler.cpp", __LINE__);
    }

    fmodSystem->init(2, FMOD_INIT_NORMAL | FMOD_3D | FMOD_INIT_3D_RIGHTHANDED, nullptr);
    fmodSystem->set3DListenerAttributes(0, glmToFMOD(position_), glmToFMOD(velocity_), glmToFMOD(forwardDirection_), glmToFMOD(upDirection_));

    return true;
}

void AudioHandler::Update(const float deltaTime_)
{
    fmodSystem->update();
}

void AudioHandler::OnDestroy()
{
    for (auto snd : audioMap)
    {
        FMOD_Sound_Release(reinterpret_cast<FMOD_SOUND*>(&audioMap));
        snd.second = nullptr;
    }

    audioMap.clear();

    for (auto channel : channelMap)
    {
        FMOD_Channel_Stop(reinterpret_cast<FMOD_CHANNEL*>(&channelMap));
        channel.second = nullptr;
    }

    channelMap.clear();

    fmodSystem->close();
    fmodSystem->release();
    fmodSystem = nullptr;
}

void AudioHandler::UpdateChannelPositionVelocity(int channelID_, glm::vec3 newPos_, glm::vec3 newVel_)
{

}

FMOD_VECTOR* AudioHandler::glmToFMOD(glm::vec3 vec3_)
{
    FMOD_VECTOR* fmodVec = new FMOD_VECTOR;

    fmodVec->x = vec3_.x;
    fmodVec->y = vec3_.y;
    fmodVec->z = vec3_.z;

    return fmodVec;
}

void AudioHandler::LoadSound(std::string audioName_, bool loop_, bool audio3D_, bool compressedAudio_)
{
    bool shouldLoop = loop_;
    bool audio3D = audio3D_;
    bool audioCompressed = compressedAudio_;

    if (GetSound(audioName_) != nullptr){
        return;
    }

    FMOD_MODE mode = FMOD_DEFAULT;

    if (loop_){
        mode = mode | FMOD_LOOP_NORMAL;
    }
    else{
        mode = mode | FMOD_LOOP_OFF;
    }

    if (audio3D_){
        mode = mode | FMOD_3D;
    }
    else{
        mode = mode | FMOD_2D;
    }

    if (compressedAudio_){
        mode = mode | FMOD_CREATESTREAM;
    }
    else{
        mode = mode | FMOD_CREATESAMPLE;
    }

    FMOD::Sound* soundPtr = nullptr;
    std::string tempString = "./Resources/Audio/" + audioName_;
    fmodSystem->createSound(tempString.c_str(), mode, nullptr, &soundPtr);
    audioMap.insert(std::pair<std::string, FMOD::Sound*>(audioName_, soundPtr));
}

int AudioHandler::PlaySound(std::string audioName_, glm::vec3 audioPos_, glm::vec3 audioVel_, float audioVolume_)
{
    if (GetSound(audioName_) == nullptr)
    {
        LoadSound(audioName_, loopAudio, audio3D, audioCompressed);
    }

    int channelID = -1;
    FMOD::Channel* channelPtr = nullptr;

    fmodSystem->playSound(GetSound(audioName_), nullptr, true, &channelPtr);
    channelPtr->set3DAttributes(glmToFMOD(audioPos_), glmToFMOD(audioVel_));
    channelPtr->setVolume(audioVolume_);
    channelPtr->setPaused(false);
    channelID = channelID + 1;

    channelMap.insert(std::pair<int, FMOD::Channel*>(channelID, channelPtr));
    return channelID;
}

FMOD::Sound* AudioHandler::GetSound(std::string audioName_)
{
    if (audioMap.find(audioName_) != audioMap.end())
    {
        return audioMap[audioName_];
    }
    else
    {
        return nullptr;
    }
}

bool AudioHandler::IsPlaying(int channelID_)
{
    bool audioPlaying;

    if (channelMap.count(channelID_))
    {
        audioPlaying = IsPlaying(channelID_);
    }

    return audioPlaying;
}
