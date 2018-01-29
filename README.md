# Simple OpenAL example
![Powered by steell911](https://github.com/steell911/logo/blob/master/steell911_logo_3.png?raw=true)
### Introduction
This repository contains a small working OpenAL example. In this example you can play *.wav file and set source position

### Install OpenAL
##### Install on windows
* [Download](https://www.openal.org/downloads/) the last version **OpenAL Core Sdk** *(at the beginning 2018 it OpenAL 1.1 Core SDK)*
* Install **OpenAL**
* Install **oalinst.exe** from *redist* folder of OpenAL installation directory *(default is C:\Program Files (x86)\OpenAL 1.1 SDK)*
* Copy all **header** files from *include* folder to *include/AL* folder *(AL folder needs to be previously created)* of you compiler *(for me it MinGW 5.3.0 compiler in path C:\Qt\Tools\mingw530_32\i686-w64-mingw32)*
* Copy **OpenAL32.lib** from the *libs/Win32 or libs/Win64 folder (depending on your platform) of OpenAL installation directory* to *lib* folder of you compiler
* Copy **OpenAL32.dll** from the *Windows/System32* or *Windows/SysWOW64* folder to *lib* folder of your compiler

### Run 
##### Run with QT
Before run the program you need create **config.ini** file in execution folder. This file contain position and velocity parameters of sound source:
```sh
px
py
pz
vx
vy
vz
```
where **px**, **py**, **pz** is *float* position values and **vx**, **vy**, **vz** is *float* velocity values.
Also you need add .wav file name *(for example drama.wav from system windows wav files)* to command line arguments *(in Qt Creator it Projects->Build&Run->Run->Command line arguments)*, and copy this file to execution folder.