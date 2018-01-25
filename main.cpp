/**************************************************************************
** Qt Creator license header template
**   Special keywords:  22.01.2018 2018
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
//	date: 22.01.2018

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include "converter.h"
#include "cmath"

using namespace std;

//ALCdevice *device;
//ALCcontext *context;
ALenum error;

void DisplayALError(string msg);
void DisplayALError(string msg, ALenum code);

struct SndInfo
{
    unsigned int ID;
    string Filename;
    unsigned int Rate;
    unsigned int Format;
};

int main(int argc, char* argv[])
{
    alGetError();

    FILE *fp = NULL;
    fp = fopen(argv[1], "rb");

    char type[4];
    DWORD size, chunkSize;
    short formatType, channels;
    DWORD sampleRate, avgBytesPerSec;
    short bytesPerSample, bitsPerSample;
    DWORD dataSize;

    fread(type, sizeof(char), 4, fp);
    if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F') {
        cout << "No riff file" << "\n";
        return 3;
    }

    fread(&size, sizeof(DWORD), 1, fp);
    fread(type, sizeof(char), 4, fp);
    if(type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E') {
        cout << "No wave file" << "\n";
        return 4;
    }

    fread(type, sizeof(char), 4, fp);
    if(type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' ') {
        cout << "No fmt file" << "\n";
        return 5;
    }

    fread(&chunkSize, sizeof(DWORD), 1, fp);
    fread(&formatType, sizeof(short), 1, fp);
    fread(&channels, sizeof(short), 1, fp);
    fread(&sampleRate, sizeof(DWORD), 1, fp);
    fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
    fread(&bytesPerSample, sizeof(short), 1, fp);
    fread(&bitsPerSample, sizeof(short), 1, fp);

    fread(type, sizeof(char), 4, fp);
    if(type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a') {
        cout << "No data file" << "\n";
        return 6;
    }

    fread(&dataSize, sizeof(DWORD), 1, fp);

    unsigned char* buf = new unsigned char[dataSize];
    fread(buf, sizeof(BYTE), dataSize, fp);

    cout << "List of available devices: " << alcGetString(NULL, ALC_DEVICE_SPECIFIER) << "\n";
    ALCdevice *device;
    ALCcontext *context;
    device = alcOpenDevice(NULL);
    DisplayALError("alcOpenDevice");

    if(!device) return 7;
    context = alcCreateContext(device, NULL);
    DisplayALError("alcCreateContext");
    alcMakeContextCurrent(context);
    DisplayALError("alcMakeContextCurrent");
    if(!context) return 8;

    ALuint source;
    ALuint buffer;
    ALuint frequency = sampleRate;
    ALenum format = 0;

    alGenBuffers(1, &buffer);
    DisplayALError("alGenBuffers");
    alGenSources(1, &source);
    DisplayALError("alGenBuffers");

    if(bitsPerSample == 8) {
        if(channels == 1)
            format = AL_FORMAT_MONO8;
        else if(channels == 2)
            format = AL_FORMAT_STEREO8;
    }
    else if(bitsPerSample == 16) {
        if(channels == 1)
            format = AL_FORMAT_MONO16;
        else if(channels == 2)
            format = AL_FORMAT_STEREO16;
    }

    alBufferData(buffer, format, buf, dataSize, frequency);
    DisplayALError("alBufferData");

    ifstream fin;
    fin.open("config.ini");

    ALfloat sourcePosX, sourcePosY, sourcePosZ;
    ALfloat sourceVelX, sourceVelY, sourceVelZ;

    fin >> sourcePosX;
    fin >> sourcePosY;
    fin >> sourcePosZ;
    fin >> sourceVelX;
    fin >> sourceVelY;
    fin >> sourceVelZ;

    ALfloat SourcePos[] = {sourcePosX, sourcePosY, sourcePosZ};
    ALfloat SourceVel[] = {sourceVelX, sourceVelY, sourceVelZ};
    ALfloat ListenerPos[] = {0.0, 0.0, 0.0};
    ALfloat ListenerVel[] = {0.0, 0.0, 0.0};
    ALfloat ListenerOri[] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};

    alListenerfv(AL_POSITION, ListenerPos);
    DisplayALError("alListenerfv position");
    alListenerfv(AL_VELOCITY, ListenerVel);
    DisplayALError("alListenerfv velocity");
    alListenerfv(AL_ORIENTATION, ListenerOri);
    DisplayALError("alListenerfv orientation");

    alSourcei(source, AL_BUFFER, buffer);
    DisplayALError("alSourcei buffer");
    alSourcef(source, AL_PITCH, 1.0f);
    DisplayALError("alSourcef pitch");
    alSourcef(source, AL_GAIN, 1.0f);
    DisplayALError("alSourcef gain");
    alSourcefv(source, AL_POSITION, SourcePos);
    DisplayALError("alSourcefv position");
    alSourcefv(source, AL_VELOCITY, SourceVel);
    DisplayALError("alSourcefv velocity");
    alSourcei(source, AL_LOOPING, AL_TRUE);
    DisplayALError("alSourcei looping");


    alSourcePlay(source);
    DisplayALError("alSourcePlay");

    while(true) {
        SourcePos[0] += 0.000001;
        alSourcefv(source, AL_POSITION, SourcePos);
    }
    system("pause");

    return 0;
}

void DisplayALError(string msg) {
    auto code = alGetError();
    string err;

    if(code == AL_NO_ERROR) err = "no error";
    else if(code == AL_INVALID_NAME) err = "invalid name";
    else if(code == AL_INVALID_ENUM) err = "invalid enum";
    else if(code == AL_INVALID_VALUE) err = "invalid value";
    else if(code == AL_INVALID_OPERATION) err = "invalid operation";
    else if(code == AL_OUT_OF_MEMORY) err = "out of memory";

    cout << msg << ": " << err << "\n";
}

void DisplayALError(string msg, ALenum code) {
    string err;

    if(code == AL_NO_ERROR) err = "no error";
    else if(code == AL_INVALID_NAME) err = "invalid name";
    else if(code == AL_INVALID_ENUM) err = "invalid enum";
    else if(code == AL_INVALID_VALUE) err = "invalid value";
    else if(code == AL_INVALID_OPERATION) err = "invalid operation";
    else if(code == AL_OUT_OF_MEMORY) err = "out of memory";

    cout << msg << ": " << err << "\n";
}
