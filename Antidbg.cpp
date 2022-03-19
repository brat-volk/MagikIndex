#include "common.h"


void AntiDBG::Initialize() {
    memset(&TrustItem,false,sizeof(TrustItem));
    if(ResCheck())
        trust -= 20;
    if(VMGFileCheck())
        trust -= 30;
    if(VMHFileCheck())
        trust += 30;
    if(HDDCheck())
        trust -= 30;
    if(RAMCheck())
        trust -= 30;
    if(CPUCheck())
        trust -= 30;
    if(MonitorCheck())
        trust += 10;
    if(TimeCheck())
        trust -= 30;
    if(InteractionCheck())
        trust -= 20;
    if(InternetCheck())
        trust += 10;
    if(AMCheck())
        trust += 10;
    if(AppCheck())
        trust -= 30;
    if (IsDebuggerPresent) {
        trust -= 50;
        TrustItem.IsBeingDebugged = true;
    }
}

bool AntiDBG::ResCheck() {

    int x1, y1, x2, y2, w, h;

    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    w = x2 - x1;
    h = y2 - y1;


    double Ratios[6] = { 4 / 3,16 / 9,21 / 9,32 / 9,16 / 10,5 / 4 };
    double Ratioed = (double)w / h;
    for (int q = 0; q < 6; q++) {
        if (Ratioed == Ratios[q]) {
            TrustItem.IsResCheck = true;
            return true;
        }
    }
    return false;
}
bool AntiDBG::VMGFileCheck() {
    LPCSTR BannedFiles[] = {   //crypt em n encrypt em at runtime for 1337 h4x0r status
        //VMWare
         "C:\\Windows\\System32\\drivers\\vmnet.sys",
         "C:\\Windows\\System32\\drivers\\vmmouse.sys",
         "C:\\Windows\\System32\\drivers\\vmusb.sys",
         "C:\\Windows\\System32\\drivers\\vm3dmp.sys",
         "C:\\Windows\\System32\\drivers\\vmci.sys",
         "C:\\Windows\\System32\\drivers\\vmhgfs.sys",
         "C:\\Windows\\System32\\drivers\\vmmemctl.sys",
         "C:\\Windows\\System32\\drivers\\vmx86.sys",
         "C:\\Windows\\System32\\drivers\\vmrawdsk.sys",
         "C:\\Windows\\System32\\drivers\\vmusbmouse.sys",
         "C:\\Windows\\System32\\drivers\\vmkdb.sys",
         "C:\\Windows\\System32\\drivers\\vmnetuserif.sys",
         "C:\\Windows\\System32\\drivers\\vmnetadapter.sys",
        //VirtualBox
         "C:\\Windows\\System32\\drivers\\VBoxMouse.sys",
         "C:\\Windows\\System32\\drivers\\VBoxGuest.sys",
         "C:\\Windows\\System32\\drivers\\VBoxSF.sys",
         "C:\\Windows\\System32\\drivers\\VBoxVideo.sys",
         "C:\\Windows\\System32\\vboxdisp.dll",
         "C:\\Windows\\System32\\vboxhook.dll",
         "C:\\Windows\\System32\\vboxmrxnp.dll",
         "C:\\Windows\\System32\\vboxogl.dll",
         "C:\\Windows\\System32\\vboxoglarrayspu.dll",
         "C:\\Windows\\System32\\vboxoglcrutil.dll",
         "C:\\Windows\\System32\\vboxoglerrorspu.dll",
         "C:\\Windows\\System32\\vboxoglfeedbackspu.dll",
         "C:\\Windows\\System32\\vboxoglpackspu.dll",
         "C:\\Windows\\System32\\vboxoglpassthroughspu.dll",
         "C:\\Windows\\System32\\vboxservice.exe",
         "C:\\Windows\\System32\\vboxtray.exe",
         "C:\\Windows\\System32\\VBoxControl.exe",
        //KVM 
         "C:\\Windows\\System32\\drivers\\balloon.sys",
         "C:\\Windows\\System32\\drivers\\netkvm.sys",
         "C:\\Windows\\System32\\drivers\\pvpanic.sys",
         "C:\\Windows\\System32\\drivers\\viofs.sys",
         "C:\\Windows\\System32\\drivers\\viogpudo.sys",
         "C:\\Windows\\System32\\drivers\\vioinput.sys",
         "C:\\Windows\\System32\\drivers\\viorng.sys",
         "C:\\Windows\\System32\\drivers\\vioscsi.sys",
         "C:\\Windows\\System32\\drivers\\vioser.sys",
         "C:\\Windows\\System32\\drivers\\viostor.sys",
        //general files
         "C:\\a\\foobar.bmp",
         "C:\\passwords.txt",
         "C:\\email.txt",
         "C:\\email.htm",
         "C:\\work.doc",
         "C:\\work.docx",
         "C:\\work.xls"
    };

    for (int i = 0; i < 46; i++) {                                              //deploy dynamic size thanks
        if (fexists(BannedFiles[i])) {
            TrustItem.IsInVM = true;
            return true;
        }
    }
    return false;
}
bool AntiDBG::VMHFileCheck() {
    LPCSTR BannedFiles[] = {
       //VirtualBox
        "C:\\Windows\\System32\\drivers\\VBoxDrv.sys",
        "C:\\Windows\\System32\\drivers\\VBoxNetAdp6",
        "C:\\Windows\\System32\\drivers\\VBoxNetLwf.sys",
        "C:\\Windows\\System32\\drivers\\VBoxUSBMon.sys",
    };

    for (int i = 0; i < 4; i++) {                                              //deploy dynamic size thanks
        if (fexists(BannedFiles[i])) {
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
    drive = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (drive == INVALID_HANDLE_VALUE) {
        CloseHandle(drive);
        return true;
    }
    result = DeviceIoControl(drive, IOCTL_DISK_GET_LENGTH_INFO, NULL, 0, &size, sizeof(GET_LENGTH_INFORMATION), &lpBytesReturned, NULL);
    CloseHandle(drive);
    if (result != 0) {
        if (size.Length.QuadPart / 1073741824 <= MinHardDisk) {
            TrustItem.IsSmallHardDrive = true;
            return true;
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
    if ((RAMStatus.ullTotalPhys / 1024) / 1024 < RequiredRam) {
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
            TrustItem.ExtUserActivity == true;
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
       //mbam
        "mbamtray.exe",
        "mbam.exe",
       //bitdefender
        "bdagent.exe",
        "bdredline.exe",
        "bdss.exe",
       //avast
        "AvastSvc.exe",
        "avastUI.exe",
        "afwServ.exe",
        "ashWebSv.exe",
       //norton
        "ccsvchst.exe",
        "navapsvc.exe",
       //mcafee
        "masvc.exe",
        "macmnsvc.exe",
        "macompatsvc.exe",
        "mfefire.exe",
        "mfemms.exe",
        "mfevtps.exe",
        "mctray.exe",
        "mfeatp.exe",
        "Mcshield.exe"

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