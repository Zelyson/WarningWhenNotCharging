#include <windows.h>

int main(int argc, char const* argv[])
{
	// Battery status
	SYSTEM_POWER_STATUS status;

	// For console handles
	HWND consoleWindow = GetConsoleWindow();

	ShowWindow(consoleWindow, SW_MAXIMIZE);
	Sleep(10);
	ShowWindow(consoleWindow, SW_HIDE);

	while (true)
	{
		GetSystemPowerStatus(&status);
		if (!status.ACLineStatus)
		{
			PlaySoundA((LPCSTR)"C:\\Dev\\C++\\CheckBatteryLoading\\x64\\Release\\scream.wav", NULL, SND_FILENAME | SND_ASYNC);
			MessageBox(NULL, (LPCWSTR)L"Your Device is not plugged in.", (LPCWSTR)L"Device not plugged in.", MB_ICONWARNING);
			Sleep(3200);

			while (!status.ACLineStatus)
			{
				Sleep(6000);
				GetSystemPowerStatus(&status);
			}
		}

		if (status.ACLineStatus) Sleep(5000);
	}

	return 0;
}

