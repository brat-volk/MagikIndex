#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "../MagikIndex/base64.h"
FILE* INPUT_FILE;
FILE* OUTPUT_FILE;
std::string DecryptMyString(std::string EncryptedString);
int GetKey(std::string EncryptedString);
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
	std::string FileBuffer;
	std::string DecryptedBuffer;
	std::ifstream InputFile(FilePath);
	while(!InputFile.eof()) {
		std::getline(InputFile, FileBuffer, ';');
		DecryptedBuffer += DecryptMyString(FileBuffer);
	}
	InputFile.close();
	fopen_s(&OUTPUT_FILE, "DecryptedLog.txt", "a+");
	fprintf(OUTPUT_FILE, "%s", DecryptedBuffer.c_str());
	fclose(OUTPUT_FILE);
	std::cout << "Logs decrypted successfully." << std::endl;
	Sleep(5000);
	exit(1);
}
std::string DecryptMyString(std::string EncryptedString) {
	int Key = GetKey(EncryptedString);
	std::string CryptedString;
	for (int r = 0; r < EncryptedString.size(); r++) {
		if (Key % 2 == 0) {
			if (EncryptedString[r] % 2 == 0)
				CryptedString += (int)EncryptedString[r] + Key - 2;
			else
				CryptedString += (int)EncryptedString[r] + Key - 4;
		}
		else {
			if (EncryptedString[r] % 2 != 0)
				CryptedString += (int)EncryptedString[r] + Key - 1;
			else
				CryptedString += (int)EncryptedString[r] + Key - 3;
		}
	}
	return CryptedString;
}
int GetKey(std::string EncryptedString) {
	std::string Decoded64;
	for (int i = 4; i >= 2; i--) {
		Decoded64 += EncryptedString[EncryptedString.size() - i];
	}
	EncryptedString = Decoded64;
	ZeroMemory(&Decoded64, sizeof(Decoded64));
	Base64::decode(EncryptedString, &Decoded64);
	if (Decoded64.size() == 0){
		std::cout << Decoded64.size() << EncryptedString << "\n";
	}
	return (int)Decoded64[0];
}