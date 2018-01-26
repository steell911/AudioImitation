/**************************************************************************
** Qt Creator license header template
**   Special keywords:  26.01.2018 2018
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
//	date: 26.01.2018
//	file: audio.cpp
//	class: Audio
#include "audio.h"

#ifdef PROG_DEBUG
#include <iostream>
#endif

using namespace std;

namespace snd {


bool cmdIsValid()
{
#ifdef PROG_DEBUG
    auto code = alGetError();
    string err;

    if(code == AL_NO_ERROR) err = "no error";
    else if(code == AL_INVALID_NAME) err = "invalid name";
    else if(code == AL_INVALID_ENUM) err = "invalid enum";
    else if(code == AL_INVALID_VALUE) err = "invalid value";
    else if(code == AL_INVALID_OPERATION) err = "invalid operation";
    else if(code == AL_OUT_OF_MEMORY) err = "out of memory";

    cout << err << "\n";
    return code == AL_NO_ERROR;
#endif
#ifndef PROG_DEBUG
    if(alGetError() == AL_NO_ERROR) return true;
    return false;
#endif
}

Audio::Audio() :
    device(nullptr),
    context(nullptr),
    source(0),
    buffer(0),
    frequency(0),
    format(0)
{

}

Audio::~Audio()
{

}

bool Audio::openDevice(const ALCchar *name)
{
    device = alcOpenDevice(name);
    return cmdIsValid();
}

bool Audio::createContext(const ALCint *attribute)
{
    context = alcCreateContext(device, attribute);
    alcMakeContextCurrent(context);
    return cmdIsValid();
}

bool Audio::closeDevice()
{
    alcCloseDevice(device);
    return cmdIsValid();
}

bool Audio::generateBuffer()
{
    alGenBuffers(1, &buffer);
    return cmdIsValid();
}

bool Audio::generateSource()
{
    alGenSources(1, &source);
    return cmdIsValid();
}

bool Audio::setListenerPosition(ALfloat x, ALfloat y, ALfloat z)
{
    ALfloat position[3] = {x, y, z};
    alListenerfv(AL_POSITION, position);
    return cmdIsValid();
}

bool Audio::setListenerVelocity(ALfloat x, ALfloat y, ALfloat z)
{
    ALfloat velocity[3] = {x, y, z};
    alListenerfv(AL_VELOCITY, velocity);
    return cmdIsValid();
}

bool Audio::setListenerOrientation(ALfloat atX, ALfloat atY, ALfloat atZ,
                                   ALfloat upX, ALfloat upY, ALfloat upZ)
{
    ALfloat orientation[6] = {atX, atY, atZ, upX, upY, upZ};
    alListenerfv(AL_ORIENTATION, orientation);
    return cmdIsValid();
}

bool Audio::setSourcePosition(ALfloat x, ALfloat y, ALfloat z)
{
    ALfloat position[3] = {x, y, z};
    alSourcefv(source, AL_POSITION, position);
    return cmdIsValid();
}

bool Audio::setSourceVelocity(ALfloat x, ALfloat y, ALfloat z)
{
    ALfloat velocity[3] = {x, y, z};
    alSourcefv(source, AL_VELOCITY, velocity);
    return cmdIsValid();
}

bool Audio::initSource()
{
    alSourcei(source, AL_BUFFER, buffer);
    if(!cmdIsValid()) return false;
    alSourcef(source, AL_PITCH, 1.0f);
    if(!cmdIsValid()) return false;
    alSourcef(source, AL_GAIN, 1.0f);
    if(!cmdIsValid()) return false;
    alSourcei(source, AL_LOOPING, AL_FALSE);
    return cmdIsValid();
}

bool Audio::setFormat(short channels, short bitsPerSample)
{
    if(bitsPerSample == 8) {
        if(channels == 1) {
            format = AL_FORMAT_MONO8;
            return true;
        }
        else if(channels == 2) {
            format = AL_FORMAT_STEREO8;
            return true;
        }
    }
    else if(bitsPerSample == 16) {
        if(channels == 1) {
            format = AL_FORMAT_MONO16;
            return true;
        }
        else if(channels == 2) {
            format = AL_FORMAT_STEREO16;
            return true;
        }
    }
    return false;
}

bool Audio::setFrequency(DWORD rate)
{
    frequency = rate;
    return true;
}

bool Audio::setBuffer(unsigned char *data, DWORD dataSize)
{
    alBufferData(buffer, format, data, dataSize, frequency);
    return cmdIsValid();
}

bool Audio::play()
{
    alSourcePlay(source);
    return cmdIsValid();
}

bool Audio::pause()
{
    alSourcePause(source);
    return cmdIsValid();
}

bool Audio::stop()
{
    alSourceStop(source);
    return cmdIsValid();
}

}
