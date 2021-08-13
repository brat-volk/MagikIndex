#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
FILE* INPUT_FILE;
FILE* OUTPUT_FILE;
bool fexists(const std::string& filename) {
	std::ifstream ifile(filename.c_str());
	return (bool)ifile;
}
void main() {
input:
	char FilePath[MAX_PATH];
	std::cout << "Full path to the crypted log: ";
	std::cin >> FilePath;
	std::cout << std::endl;
	if (!fexists(FilePath)) {
		std::cout << "Invalid file path." << std::endl;
		goto input;
	}
key:
	int ShiftKey;
	std::cout << "Base shift value used for the logs: ";
	std::cin >> ShiftKey;
	std::cout << std::endl;
	if (!std::cin) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Invalid base value." << std::endl;
		goto key;
	}
	std::string Password;
	std::cout << "Password used for the logs: ";
	std::cin >> Password;
	std::cout << std::endl;
	std::string Passwd = Password;
	int ExtrapolatedKey = ShiftKey;
	for (int plq = 0; plq < Passwd.size(); plq++) {
		ExtrapolatedKey += (int)Passwd[plq];
	}
	std::string FileBuffer;
	std::ifstream InputFile(FilePath);
	if (!InputFile.eof()) {
		std::getline(InputFile, FileBuffer, '\0');
	}
	InputFile.close();
	fopen_s(&OUTPUT_FILE, "DecryptedLog.txt", "a+");
	std::string DecryptedBuffer;
	for (int i = 0; i < FileBuffer.size(); i++) {
		DecryptedBuffer += FileBuffer[i] - ExtrapolatedKey;
	}
	fprintf(OUTPUT_FILE, "%s", DecryptedBuffer.c_str());
	fclose(OUTPUT_FILE);
	std::cout << "Logs decrypted successfully." << std::endl;
	Sleep(5000);
	exit(1);
}