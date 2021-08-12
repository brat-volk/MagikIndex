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
	int ShiftKey = NULL;

	std::cout << "Encrypt key used for the logs: ";
	std::cin >> ShiftKey;
	std::cout << std::endl;

	if (!std::cin) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Invalid key." << std::endl;
		goto key;
	}

	std::ifstream is(FilePath, std::ifstream::binary);
	is.seekg(0, is.end);
	int length = is.tellg();
	is.seekg(0, is.beg);

	char* buffer = new char[length];

	std::cout << "Reading " << length << " characters... \n";
	is.read(buffer, length);

	if (is)
		std::cout << "all characters read successfully.\n";
	else
		std::cout << "error: only " << is.gcount() << " could be read\n";
	is.close();

	fopen_s(&OUTPUT_FILE, "DecryptedLog.txt", "a+");

	std::string DecryptedBuffer;

	for (int i = 0; i < length; i++) {
		DecryptedBuffer += buffer[i] - ShiftKey;
	}
	//std::cout << DecryptedBuffer << std::endl;
	fprintf(OUTPUT_FILE, "%s", DecryptedBuffer.c_str());
	fclose(OUTPUT_FILE);
	delete[] buffer;
	std::cout << "Logs decrypted successfully." << std::endl;
	Sleep(5000);
	exit(1);
}