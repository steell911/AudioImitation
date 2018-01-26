/**************************************************************************
** Qt Creator license header template
**   Special keywords:  26.01.2018 2018
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
//	date: 26.01.2018
//	file: audio.h
//	class: Audio
#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"
#include "windows.h"

namespace snd {

bool cmdIsValid();

class Audio
{
public:
    Audio();
    ~Audio();

    bool openDevice(const ALCchar *name = NULL);
    bool createContext(const ALCint *attribute = NULL);
    bool closeDevice();

    bool generateBuffer();
    bool generateSource();

    bool setListenerPosition(ALfloat x, ALfloat y, ALfloat z);
    bool setListenerVelocity(ALfloat x, ALfloat y, ALfloat z);
    bool setListenerOrientation(ALfloat atX, ALfloat atY, ALfloat atZ,
                                ALfloat upX, ALfloat upY, ALfloat upZ);

    bool setSourcePosition(ALfloat x, ALfloat y, ALfloat z);
    bool setSourceVelocity(ALfloat x, ALfloat y, ALfloat z);
    bool initSource();

    bool setFormat(short channels, short bitsPerSample);
    bool setFrequency(DWORD rate);
    bool setBuffer(unsigned char* data, DWORD dataSize);

    bool play();
    bool pause();
    bool stop();

private:
    ALCdevice *device;
    ALCcontext *context;

    ALuint source;
    ALuint buffer;
    ALuint frequency;
    ALenum format;

};
}

#endif // AUDIO_H
