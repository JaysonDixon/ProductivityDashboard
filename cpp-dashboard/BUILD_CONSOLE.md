# Building the Console Version (No SFML Required)

This is a simple console-based version that requires only a C++ compiler.

## Quick Build Instructions

### Windows - Using MinGW (if installed)
```powershell
g++ -std=c++17 main_console.cpp -o ProductivityDashboard.exe
.\ProductivityDashboard.exe
```

### Windows - Using Visual Studio Developer Command Prompt
```powershell
cl /EHsc /std:c++17 main_console.cpp
.\main_console.exe
```

### Windows - Using MSVC (cl.exe) directly
1. Open "Developer Command Prompt for VS"
2. Navigate to cpp-dashboard folder
3. Run:
```cmd
cl /EHsc main_console.cpp /Fe:ProductivityDashboard.exe
ProductivityDashboard.exe
```

## No Compiler Installed?

### Option 1: Install MinGW-w64
1. Download from: https://www.mingw-w64.org/downloads/
2. Or use chocolatey: `choco install mingw`
3. Add to PATH
4. Compile with g++

### Option 2: Install Visual Studio Build Tools
1. Download: https://visualstudio.microsoft.com/downloads/
2. Install "Build Tools for Visual Studio"
3. Use Developer Command Prompt

### Option 3: Use Online Compiler
Copy the code to:
- https://www.onlinegdb.com/online_c++_compiler
- https://www.programiz.com/cpp-programming/online-compiler/
- https://replit.com/

## Features (No Graphics Required)

✓ Habit tracking with 4 presets + custom habits
✓ Streak tracking (consecutive days)
✓ Weekly trend analysis (Up/Down/Stable)
✓ XP and leveling system
✓ Progress bar visualization (text-based)
✓ ASCII bar charts
✓ Motivational tips
✓ Persistent storage (habit_log.txt, gamification.txt)
✓ Full menu-driven interface

## Controls

Navigate using number keys 1-8:
- 1 = Log Exercise
- 2 = Log Work  
- 3 = Log Reading
- 4 = Log Meditation
- 5 = Log Custom Habit
- 6 = View Statistics
- 7 = View Progress Chart
- 8 = Get Motivation Tip
- 0 = Exit
