#include "AudioBase.h"

AudioBase::AudioBase(std::string audioName_, bool loop_, bool audio3D_, bool compressedAudio_)
{
    channelID = -1;

    audioName = audioName_;

    AudioHandler::GetInstance()->LoadSound(audioName_, loop_, audio3D_, compressedAudio_);
}

AudioBase::~AudioBase()
{

}

bool AudioBase::OnCreate(GameObject* gameObject_)
{
    parent = gameObject_;
    PlaySound();
    std::cout << ("AudioBase was created");
    return true;
}

void AudioBase::Update(const float deltaTime_)
{
    AudioHandler::GetInstance()->Update(deltaTime_);
}

void AudioBase::PlaySound()
{
    channelID = AudioHandler::GetInstance()->PlaySound(audioName, parent->GetPosition());
}

bool AudioBase::isPlaying()
{
    return AudioHandler::GetInstance()->IsPlaying(channelID);
}