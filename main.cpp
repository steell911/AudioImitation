/**************************************************************************
** Qt Creator license header template
**   Special keywords:  22.01.2018 2018
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
//	date: 22.01.2018

#include <string>
#include "converter.h"
#include "audio.h"
#include "wavreader.h"

using namespace std;

snd::Audio audio;
reader::WavReader wavReader;

int main(int argc, char* argv[])
{
    //  read wav file
    std::string name = argv[1];
    wavReader.read(name);
    wavReader.setCurrentName(name);

    //  convert coordinates from polar to rectangular
    ifstream fin;
    fin.open("config.ini");
    float radius, zenith, azimuth;
    float coord[3] = {0,0,0};
    fin >> radius >> zenith >> azimuth;
    converter::polarToRectangular(radius, zenith, azimuth, coord);

    //  play sound
    audio.openDevice(NULL);
    audio.createContext(NULL);
    audio.generateBuffer();
    audio.generateSource();

    audio.setFormat(wavReader.getChannels(), wavReader.getBitsPerSample());
    audio.setFrequency(wavReader.getSampleRate());
    audio.setBuffer(wavReader.getBuffer(), wavReader.getDataSize());

    audio.setListenerPosition(0, 0, 0);
    audio.setListenerVelocity(0, 0, 0);
    audio.setListenerOrientation(0, 0, -1, 0, 1, 0);

    audio.setSourcePosition(coord[0], coord[1], coord[2]);
    audio.setSourceVelocity(0, 0, 0);
    audio.initSource();

    audio.play();

    while(true);
    return 0;
}
