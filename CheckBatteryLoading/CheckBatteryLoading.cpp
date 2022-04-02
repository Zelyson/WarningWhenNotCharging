#include <windows.h>

int main(int argc, char const* argv[])
{
	// Battery status
	SYSTEM_POWER_STATUS status;

	while (true)
	{
		GetSystemPowerStatus(&status);
		if (!status.ACLineStatus)
		{
			MessageBeep(MB_ICONWARNING);
			MessageBoxW(NULL, (LPCWSTR)L"Your Device is not plugged in.", (LPCWSTR)L"Check battery loading", MB_OK | MB_TASKMODAL);

			while (!status.ACLineStatus)
			{
				Sleep(6000);
				GetSystemPowerStatus(&status);
			}
		}
		if (status.ACLineStatus) Sleep(1000);
	}

	return 0;
}

