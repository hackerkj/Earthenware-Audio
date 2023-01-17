/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== CMakeLists.txt ==================
static const unsigned char temp_binary_data_0[] =
"add_executable(test\n"
"    main.cpp\n"
"    _testhelpers.cpp\n"
"    audiodatatest.cpp\n"
"    binodetest.cpp\n"
"    chromagramtest.cpp\n"
"    chromatransformtest.cpp\n"
"    chromatransformfactorytest.cpp\n"
"    constantstest.cpp\n"
"    downsamplershortcuttest.cpp\n"
"    fftadaptertest.cpp\n"
"    keyclassifiertest.cpp\n"
"    keyfindertest.cpp\n"
"    lowpassfiltertest.cpp\n"
"    lowpassfilterfactorytest.cpp\n"
"    spectrumanalysertest.cpp\n"
"    temporalwindowfactorytest.cpp\n"
"    toneprofilestest.cpp\n"
"    windowfunctiontest.cpp\n"
"    workspacetest.cpp)\n"
"target_link_libraries(test keyfinder)\n";

const char* CMakeLists_txt = (const char*) temp_binary_data_0;

//================== tests.pro ==================
static const unsigned char temp_binary_data_1[] =
"#*************************************************************************\n"
"#\n"
"# Copyright 2011-2013 Ibrahim Sha'ath\n"
"#\n"
"# This file is part of LibKeyFinder.\n"
"#\n"
"# LibKeyFinder is free software: you can redistribute it and/or modify\n"
"# it under the terms of the GNU General Public License as published by\n"
"# the Free Software Foundation, either version 3 of the License, or\n"
"# (at your option) any later version.\n"
"#\n"
"# LibKeyFinder is distributed in the hope that it will be useful,\n"
"# but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"# GNU General Public License for more details.\n"
"#\n"
"# You should have received a copy of the GNU General Public License\n"
"# along with LibKeyFinder.  If not, see <http://www.gnu.org/licenses/>.\n"
"#\n"
"#*************************************************************************\n"
"\n"
"cache()\n"
"\n"
"TEMPLATE = app\n"
"CONFIG += console\n"
"CONFIG -= app_bundle\n"
"CONFIG -= qt\n"
"\n"
"CONFIG += c++11\n"
"LIBS += -stdlib=libc++\n"
"QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++\n"
"\n"
"LIBS += -lkeyfinder\n"
"\n"
"HEADERS += _testhelpers.h\n"
"\n"
"SOURCES += \\\n"
"    main.cpp \\\n"
"    _testhelpers.cpp \\\n"
"    audiodatatest.cpp \\\n"
"    binodetest.cpp \\\n"
"    chromagramtest.cpp \\\n"
"    chromatransformtest.cpp \\\n"
"    chromatransformfactorytest.cpp \\\n"
"    constantstest.cpp \\\n"
"    downsamplershortcuttest.cpp \\\n"
"    fftadaptertest.cpp \\\n"
"    keyclassifiertest.cpp \\\n"
"    keyfindertest.cpp \\\n"
"    lowpassfiltertest.cpp \\\n"
"    lowpassfilterfactorytest.cpp \\\n"
"    spectrumanalysertest.cpp \\\n"
"    temporalwindowfactorytest.cpp \\\n"
"    toneprofilestest.cpp \\\n"
"    windowfunctiontest.cpp \\\n"
"    workspacetest.cpp\n"
"\n"
"macx{\n"
"  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7\n"
"  QMAKE_MAC_SDK = macosx10.12\n"
"  DEPENDPATH += /usr/local/lib\n"
"  INCLUDEPATH += /usr/local/include\n"
"  CONFIG -= ppc ppc64\n"
"  CONFIG += x86 x86_64\n"
"}\n"
"\n"
"unix|macx{\n"
"  DEPENDPATH += /usr/local/lib\n"
"  INCLUDEPATH += /usr/local/include catch\n"
"  LIBS += -L/usr/local/lib -L/usr/lib\n"
"}\n"
"\n"
"win32{\n"
"  INCLUDEPATH += C:/minGW32/local/include\n"
"  DEPENDPATH += C:/minGW32/local/bin\n"
"  LIBS += -LC:/minGW32/local/bin -LC:/minGW32/local/lib\n"
"}\n";

const char* tests_pro = (const char*) temp_binary_data_1;

//================== CMakeLists.txt ==================
static const unsigned char temp_binary_data_2[] =
"cmake_minimum_required(VERSION 3.0)\n"
"project(libkeyfinder)\n"
"set(CMAKE_CXX_STANDARD 11)\n"
"set(CMAKE_CXX_STANDARD_REQUIRED True)\n"
"\n"
"if(BUILD_STATIC_LIBS)\n"
"  message(STATUS \"Building libKeyFinder as a static library\")\n"
"  add_library(keyfinder STATIC\n"
"    audiodata.cpp\n"
"    chromagram.cpp\n"
"    chromatransform.cpp\n"
"    chromatransformfactory.cpp\n"
"    fftadapter.cpp\n"
"    keyclassifier.cpp\n"
"    keyfinder.cpp\n"
"    lowpassfilter.cpp\n"
"    lowpassfilterfactory.cpp\n"
"    spectrumanalyser.cpp\n"
"    temporalwindowfactory.cpp\n"
"    toneprofiles.cpp\n"
"    windowfunctions.cpp\n"
"    workspace.cpp\n"
"    constants.cpp\n"
"  )\n"
"else()\n"
"  message(STATUS \"Building libKeyFinder as a dynamic library\")\n"
"  add_library(keyfinder SHARED\n"
"    audiodata.cpp\n"
"    chromagram.cpp\n"
"    chromatransform.cpp\n"
"    chromatransformfactory.cpp\n"
"    fftadapter.cpp\n"
"    keyclassifier.cpp\n"
"    keyfinder.cpp\n"
"    lowpassfilter.cpp\n"
"    lowpassfilterfactory.cpp\n"
"    spectrumanalyser.cpp\n"
"    temporalwindowfactory.cpp\n"
"    toneprofiles.cpp\n"
"    windowfunctions.cpp\n"
"    workspace.cpp\n"
"    constants.cpp\n"
"  )\n"
"endif()\n"
"\n"
"list(APPEND CMAKE_MODULE_PATH \"${CMAKE_CURRENT_SOURCE_DIR}/cmake\")\n"
"find_package(FFTW REQUIRED)\n"
"target_link_libraries(keyfinder PUBLIC FFTW::FFTW)\n"
"target_include_directories(keyfinder PUBLIC \"${CMAKE_CURRENT_SOURCE_DIR}\")\n"
"\n"
"install(TARGETS keyfinder DESTINATION lib)\n"
"install(FILES\n"
"  audiodata.h\n"
"  chromagram.h\n"
"  chromatransform.h\n"
"  chromatransformfactory.h\n"
"  fftadapter.h\n"
"  keyclassifier.h\n"
"  keyfinder.h\n"
"  lowpassfilter.h\n"
"  lowpassfilterfactory.h\n"
"  spectrumanalyser.h\n"
"  temporalwindowfactory.h\n"
"  toneprofiles.h\n"
"  windowfunctions.h\n"
"  workspace.h\n"
"  constants.h\n"
"  exception.h\n"
"  binode.h\n"
"  DESTINATION include/keyfinder)\n"
"\n"
"set(LIBKEYFINDER_VERSION 2.2.2)\n"
"configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libKeyFinder.pc.cmake\n"
"  ${CMAKE_CURRENT_BINARY_DIR}/libKeyFinder.pc @ONLY)\n"
"install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libKeyFinder.pc DESTINATION lib/pkgconfig)\n"
"\n"
"add_subdirectory(tests)\n";

const char* CMakeLists_txt2 = (const char*) temp_binary_data_2;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x90e15cf5:  numBytes = 541; return CMakeLists_txt;
        case 0xbab9378f:  numBytes = 2069; return tests_pro;
        case 0x8b4a41dd:  numBytes = 1909; return CMakeLists_txt2;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "CMakeLists_txt",
    "tests_pro",
    "CMakeLists_txt2"
};

const char* originalFilenames[] =
{
    "CMakeLists.txt",
    "tests.pro",
    "CMakeLists.txt"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
