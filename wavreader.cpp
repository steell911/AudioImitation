/**************************************************************************
** Qt Creator license header template
**   Special keywords:  26.01.2018 2018
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
//	date: 26.01.2018
//	file: wavreader.cpp
//	class: WavReader
#include "wavreader.h"

namespace reader {

WavReader::WavReader() :
    currentName("")
{
    data.clear();
}

bool WavReader::read(const std::string& name)
{
    FILE *fp = nullptr;
    fp = fopen(name.c_str(), "rb");

    SingleWav sw;
    char type[4];

    fread(type, sizeof(char), 4, fp);
    if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F') {
        return false;
    }

    fread(&(sw.size), sizeof(DWORD), 1, fp);
    fread(type, sizeof(char), 4, fp);
    if(type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E') {
        return false;
    }

    fread(type, sizeof(char), 4, fp);
    if(type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' ') {
        return false;
    }

    fread(&(sw.chunkSize), sizeof(DWORD), 1, fp);
    fread(&(sw.formatType), sizeof(short), 1, fp);
    fread(&(sw.channels), sizeof(short), 1, fp);
    fread(&(sw.sampleRate), sizeof(DWORD), 1, fp);
    fread(&(sw.avgBytesPerSec), sizeof(DWORD), 1, fp);
    fread(&(sw.bytesPerSample), sizeof(short), 1, fp);
    fread(&(sw.bitsPerSample), sizeof(short), 1, fp);

    fread(type, sizeof(char), 4, fp);
    if(type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a') {
        return false;
    }

    fread(&(sw.dataSize), sizeof(DWORD), 1, fp);
    sw.buffer = new unsigned char[sw.dataSize];
    fread(sw.buffer, sizeof(BYTE), sw.dataSize, fp);

    data.insert(make_pair(name, sw));

    return true;
}

bool WavReader::isData(const std::string& name) const
{
    return (data.count(name) > 0);
    return false;
}

bool WavReader::setCurrentName(const std::string& name)
{
    if(data.count(name) > 0) {
        currentName = name;
        return true;
    }
    return false;
}

void WavReader::removeData(const std::string& name)
{
    data.erase(name);
}

const SingleWav& WavReader::getData(std::string &name) const
{
    return data.at(name);
}

const SingleWav& WavReader::getData() const
{
    return data.at(currentName);
}

DWORD WavReader::getSize() const
{
    return data.at(currentName).size;
}

DWORD WavReader::getChunkSize() const
{
    return data.at(currentName).chunkSize;
}

short WavReader::getFormatType() const
{
    return data.at(currentName).formatType;
}

short WavReader::getChannels() const
{
    return data.at(currentName).channels;
}

DWORD WavReader::getSampleRate() const
{
    return data.at(currentName).sampleRate;
}

DWORD WavReader::getAvgBytesPerSec() const
{
    return data.at(currentName).avgBytesPerSec;
}

short WavReader::getBytePerSample() const
{
    return data.at(currentName).bytesPerSample;
}

short WavReader::getBitsPerSample() const
{
    return data.at(currentName).bitsPerSample;
}

DWORD WavReader::getDataSize() const
{
    return data.at(currentName).dataSize;
}

unsigned char* WavReader::getBuffer() const
{
    return data.at(currentName).buffer;
}
}
