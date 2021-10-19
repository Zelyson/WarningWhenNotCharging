#include <iostream>
#include <windows.h>

// Return COORD object with modified XY-Coordinates
COORD setPosXY(COORD position, int x, int y)
{
	position.X = x;
	position.Y = y;

	return position;
}

// MAIN()
int main(int argc, char const* argv[])
{
	// Battery status
	SYSTEM_POWER_STATUS status;
	GetSystemPowerStatus(&status);

	// For console handles
	HWND consoleWindow = GetConsoleWindow();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = GetLargestConsoleWindowSize(console);
	COORD pos;
	char thx[] =   "| Thank you! |";
	char undLn[] = "<------------>";
	char msgChargerMissing[] = "-- Please plug in a charger --";
	int missingCount = 7;
	pos = setPosXY(size, (size.X - sizeof(msgChargerMissing)) / 2, size.Y / 2);

	// Hide cursor
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(console, &info);

	// Skip following *Not plugged in* loop and go into plugged in loop
	if (status.ACLineStatus) goto pluggedLoop;
notPlugged:
	ShowWindow(consoleWindow, SW_MAXIMIZE);
	SetConsoleTextAttribute(console, 4);
	pos = setPosXY(pos, pos.X - (missingCount-1) * sizeof(msgChargerMissing) / 2, pos.Y);  // Calculate offset to center messages
	SetConsoleCursorPosition(console, pos);
	for (int i = missingCount; i > 0; i--) 
	{
		std::cout << msgChargerMissing;
	}
	pos = setPosXY(pos, pos.X, pos.Y + 1);
	Sleep(3200);
	ShowWindow(consoleWindow, SW_HIDE);
	
	// AcLineStatus returns 1 if pc is loading
	while (!status.ACLineStatus)
	{
		// Notify user and update power status
		GetSystemPowerStatus(&status);
		Sleep(2000);
	}

	// Clear Screen and Thank user for plugging in Laptop
	system("cls");
	SetConsoleTextAttribute(console, 11);
	ShowWindow(consoleWindow, SW_MAXIMIZE);

	pos = setPosXY(pos, (size.X - sizeof(thx)) / 2, size.Y / 2);
	SetConsoleCursorPosition(console, pos);
	std::cout << thx;
	pos = setPosXY(pos, pos.X, pos.Y - 1); // Top Line Box
	SetConsoleCursorPosition(console, pos);
	std::cout << undLn;
	pos = setPosXY(pos, pos.X, pos.Y + 2); // Bottom Line Box
	SetConsoleCursorPosition(console, pos);
	std::cout << undLn;

	// Wait, hide window and check every 10 sec if AC is no more
	Sleep(2000);
pluggedLoop:
	ShowWindow(consoleWindow, SW_HIDE); // Hide Window
	while (true)
	{
		if (!status.ACLineStatus)
		{
			system("cls");
			goto notPlugged;
		}
		Sleep(2000);
		GetSystemPowerStatus(&status);
	}
	return 0;
}