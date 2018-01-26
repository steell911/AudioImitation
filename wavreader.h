/**************************************************************************
** Qt Creator license header template
**   Special keywords:  26.01.2018 2018
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
//	date: 26.01.2018
//	file: wavreader.h
//	class: WavReader
#ifndef WAVREADER_H
#define WAVREADER_H

#include <string>
#include <map>
#include <fstream>
#include <windows.h>

namespace reader {

struct SingleWav
{
    char type[4] = {};
    DWORD size = 0;
    DWORD chunkSize = 0;
    short formatType = 0;
    short channels = 0;
    DWORD sampleRate = 0;
    DWORD avgBytesPerSec = 0;
    short bytesPerSample = 0;
    short bitsPerSample = 0;
    DWORD dataSize = 0;
    unsigned char* buffer = nullptr;
};

class WavReader
{
public:
    WavReader();
    bool read(const std::string& name);
    bool isData(const std::string& name) const;
    bool setCurrentName(const std::string& name);
    void removeData(const std::string& name);

    const SingleWav& getData(std::string& name) const;
    const SingleWav& getData() const;

    DWORD getSize() const;
    DWORD getChunkSize() const;
    short getFormatType() const;
    short getChannels() const;
    DWORD getSampleRate() const;
    DWORD getAvgBytesPerSec() const;
    short getBytePerSample() const;
    short getBitsPerSample() const;
    DWORD getDataSize() const;
    unsigned char* getBuffer() const;


private:
    std::map<std::string, SingleWav> data;
    std::map<std::string, int> data2;
    std::string currentName;
};
}

#endif // WAVREADER_H
