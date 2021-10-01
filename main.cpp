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
int main(int argc, char const *argv[])
{
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    // Battery status

    SYSTEM_POWER_STATUS status;
    GetSystemPowerStatus(&status);

    // For console handles
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = GetLargestConsoleWindowSize(console);
    COORD pos;
    LPDWORD written;
    char thx[] = "| Thank you! |";
    char undLn[] = "<------------>";
    char msgChargerMissing[] = "-- Please plug in a charger --\n";
    pos = setPosXY(pos, (size.X - sizeof(msgChargerMissing)) / 2, size.Y / 2);

    // Hide cursoe
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(console, &info);

jumpHere:
    if (!status.ACLineStatus)
    {
        pos = setPosXY(pos, pos.X, pos.Y + 1);
        SetConsoleCursorPosition(console, pos);
        std::cout << msgChargerMissing;
    }
    // AcLineStatus returns 1 if pc is loading
    while (!status.ACLineStatus)
    {
        // Notify user and update power status
        GetSystemPowerStatus(&status);
        Sleep(900);
    }

    // Clear Screen and Thank user for plugging in Laptop
    system("cls");
    SetConsoleTextAttribute(console, 11);

    pos = setPosXY(pos, (size.X - sizeof(thx)) / 2, size.Y / 2); // Welcome back
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
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Hide Window
    while (true)
    {
        if (!status.ACLineStatus)
        {
            system("cls");
            ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
            goto jumpHere;
        }
        Sleep(10000);
        GetSystemPowerStatus(&status);
    }
    return 0;
}