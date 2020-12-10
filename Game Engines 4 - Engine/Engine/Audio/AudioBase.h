#ifndef AUDIOBASE_H
#define AUDIOBASE_H

#include <iostream>
#include "AudioHandler.h"
#include "../../Engine/Rendering/3D/Component.h"
#include "../../Engine/Rendering/3D/GameObject.h"

class AudioBase : public Component
{
public:

    AudioBase(std::string audioName_, bool loop_, bool audio3D_, bool compressedAudio_);
    virtual ~AudioBase();

    virtual bool OnCreate(GameObject* gameObject_) override;
    virtual void Update(const float deltaTime_) override;

    void PlaySound();
    bool isPlaying();

private:

    std::string audioName;
    int channelID;
};
#endif 