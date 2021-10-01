# Warning when not charging

## Why you might want this:
This program is intended as a reminder for laptop users. Comming home from school, I find myself just placing down my lapotp without remembering to charge it. After one or two hours, when windows devides it is time to notify me, it is alredy to late and it shuts down. To combat this, I wrote a small program that will notify the user when the machine is not charging.  
Putting it in your `%appdata%\Microsoft\Windows\Start Menu\Programs\Startup` folder is something I would recommend, because if you remember to start the program which reminds you to charge your laptop, you probably dont need it :).

---
## Compile:
The binaries in "*Releases*" are compiled with: `g++.exe (Rev5, Built by MSYS2 project) 10.3.0` using:  
```shell
g++ -o3 main.cpp -o CheckBattryLoading.exe
```
Hope it can help.

Sebastian - 01.10.2021