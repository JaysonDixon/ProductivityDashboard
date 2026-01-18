# Personal Productivity Dashboard (C++ SFML)

A feature-rich productivity tracking application built with C++ and SFML.

## Features

- **Habit Tracking**: Log multiple habits (Exercise, Work, Reading, Meditation)
- **Streak System**: Track consecutive days of habit completion
- **Trend Analysis**: View weekly trends (Up/Down/Stable)
- **Gamification**: Earn XP and level up as you complete habits
- **Analytics**: Real-time statistics and visualizations
- **Charts**: Visual bar charts showing habit progress
- **Rule Engine**: Automated triggers based on conditions
- **Animations**: Smooth visual feedback
- **Audio Support**: Optional sound effects (when audio files are provided)
- **Persistent Storage**: Saves habit data to habit_log.txt

## Controls

- **Space** - Log Exercise habit
- **W** - Log Work habit
- **R** - Log Reading habit
- **M** - Log Meditation habit

## Prerequisites

### Windows (Using vcpkg - Recommended)

1. **Install Visual Studio 2019 or later** with C++ development tools
2. **Install vcpkg**:
   ```powershell
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   .\vcpkg integrate install
   ```

3. **Install SFML**:
   ```powershell
   .\vcpkg install sfml:x64-windows
   ```

4. **Install CMake**: Download from https://cmake.org/download/

## Building the Project

### Option 1: Using CMake with vcpkg

```powershell
cd cpp-dashboard
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

Replace `[path-to-vcpkg]` with your actual vcpkg installation path.

### Option 2: Using Visual Studio directly

1. Open Visual Studio
2. Select "Open a local folder" and choose the `cpp-dashboard` directory
3. Visual Studio will detect CMakeLists.txt
4. Build using Build > Build All (Ctrl+Shift+B)

### Option 3: Manual compilation with g++ (if SFML is installed)

```powershell
cd cpp-dashboard
g++ -std=c++17 main.cpp -o ProductivityDashboard.exe -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
```

## Running the Application

After building:

```powershell
# From the build directory
.\Release\ProductivityDashboard.exe

# Or from Debug
.\Debug\ProductivityDashboard.exe
```

## Project Structure

```
cpp-dashboard/
├── main.cpp              # Main application source code
├── CMakeLists.txt        # CMake build configuration
├── assets/               # Assets directory
│   ├── README.txt        # Font instructions
│   └── AUDIO_README.txt  # Audio instructions
├── habit_log.txt         # Generated: Persistent habit data
└── README.md             # This file
```

## Optional Assets

### Fonts
Place a TrueType font file named `arial.ttf` in the `assets/` directory for custom fonts.

### Audio
Place a WAV file named `click.wav` in the `assets/` directory for sound effects.

## Architecture

The application uses several design patterns and modules:

- **HabitLog**: Core data model with persistence
- **AnalyticsModule**: Data analysis and statistics
- **SuggestionEngine**: Motivational tips generator
- **GamifiedEnvironment**: XP and leveling system
- **RuleEngine**: Condition-action automation
- **ChartView**: Visual data representation
- **StatsView**: Textual statistics display
- **Animation**: Visual feedback system
- **AudioManager**: Sound effect management

## Troubleshooting

### "Failed to load font" warning
- Download a TrueType font and place it as `assets/arial.ttf`
- The app will still work with default SFML font

### CMake can't find SFML
- Ensure vcpkg is properly integrated: `vcpkg integrate install`
- Use the correct toolchain file path in cmake command
- Verify SFML installation: `vcpkg list`

### Build errors
- Ensure C++17 support is enabled
- Check that all SFML components are installed
- Try cleaning build directory: `rm -r build; mkdir build`

## License

Free to use and modify for educational purposes.

## Future Enhancements

- Custom habit creation UI
- Export data to CSV
- Multi-day calendar view
- Goal setting and reminders
- Dark mode theme
