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
	bool IsInHabo;
};

class AntiDBG {
public:
	int trust;
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
	bool PowerCheck();
	bool TimeCheck();
	bool InteractionCheck();
	bool InternetCheck();
	bool AMCheck();
	bool AppCheck();
	bool HaboCucker();
	BOOL BreakpointChecker();
	BOOL BreakpointChecker2();
	bool HybridCucker();
};

