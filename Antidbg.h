struct TrustItems {
	bool IsResCheck;
	bool IsInVM;
	bool IsHostingAVM;
	bool IsSmallHardDrive;
	bool IsSmallRAM;
	bool IsBeingDebugged;
	bool HasOneCore;
	bool HasMultipleMonitors;
	bool HasBeenTimepatched;
	bool UserIsInactive;
	bool HasActiveInternet;
	bool Proxied;
	bool HasRunningAntiMalware;
	bool HasMoreThan20Apps;
	bool ExtUserActivity;
};

class AntiDBG {
public:
	int trust = 100;
	TrustItems TrustItem;
	void Initialize();
private:
	bool ResCheck();
	bool VMGFileCheck();
	bool VMHFileCheck();
	bool HDDCheck();
	bool RAMCheck();
	bool CPUCheck();
	bool MonitorCheck();
	bool TimeCheck();
	bool InteractionCheck();
	bool InternetCheck();
	bool AMCheck();
	bool AppCheck();

};

