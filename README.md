  Personal Productivity Dashboard

A feature-rich productivity tracking application built with **C++ SFML** and **Web Technologies**.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/C++-17-blue.svg)
![SFML](https://img.shields.io/badge/SFML-2.5+-green.svg)

 Project Overview

This project implements a comprehensive productivity dashboard with multiple versions:
- SFML C++ Application- Full-featured desktop application
- **Web Preview** - Browser-based demonstration
- **Console Version** - Command-line interface (no graphics required)

 Implemented Features

 T1 - Dashboard Menu Interface ✓
-  Responsive navigation menu with SFML
-  4 navigation buttons: Dashboard, Charts, Gamified View, Settings
- Scalable layout (handles window resize)
- Smooth animations and hover effects
-  Proper routing to placeholder screens

 T2 - Habit Logging Input ✓
-  Text input field for habit names
-  "Log Habit" button functionality
-  Real-time display of logged habits
-  Input validation (max 30 characters)
-  Keyboard support (Enter to submit)
-  Back button navigation

 Quick Start

 Web Preview (No Installation Required)

Simply open `dashboard-preview.html` in your browser to see the T1 & T2 features in action!

```bash
# Windows
start dashboard-preview.html

# Or just double-click the file
```

 C++ SFML Version

Prerequisites:
- SFML 2.5+
- CMake 3.16+
- C++17 compatible compiler

Build Instructions:

```bash
# Install SFML via vcpkg (Windows)
vcpkg install sfml:x64-windows

# Build the project
cd cpp-dashboard
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release

# Run
.\Release\ProductivityDashboard.exe
```

See `cpp-dashboard/README_T1_T2.md` for detailed build instructions.

 Console Version (No SFML Required)

```bash
cd cpp-dashboard
g++ -std=c++17 main_console.cpp -o ProductivityDashboard.exe
.\ProductivityDashboard.exe
```

 Project Structure

```
ProductivityDashboard/
├── cpp-dashboard/              # C++ SFML Implementation
│   ├── main_dashboard.cpp     # T1 & T2 Implementation
│   ├── main.cpp               # Full-featured version
│   ├── main_console.cpp       # Console version
│   ├── Button.hpp             # UI Button component
│   ├── Screen.hpp             # Screen interface
│   ├── ScreenManager.hpp      # Navigation manager
│   ├── MenuScreen.hpp         # Menu interface (T1)
│   ├── DashboardScreen.hpp    # Habit logging (T2)
│   ├── ChartsScreen.hpp       # Charts placeholder
│   ├── GamifiedScreen.hpp     # Gamification placeholder
│   ├── SettingsScreen.hpp     # Settings placeholder
│   ├── CMakeLists.txt         # Build configuration
│   ├── README_T1_T2.md        # Detailed documentation
│   └── assets/                # Fonts and audio files
├── index.html                  # Original web dashboard
├── script.js
├── style.css
├── dashboard-preview.html      # T1 & T2 web preview
├── dashboard-preview.css
├── dashboard-preview.js
├── GITHUB_UPLOAD_GUIDE.md     # GitHub setup guide
└── README.md                   # This file
```

 Usage

 SFML Application

1. **Main Menu**: Click any button to navigate
2. **Dashboard**: 
   - Click the text field
   - Type a habit name
   - Press Enter or click "Log Habit"
   - View your logged habits
3. **Charts/Gamified/Settings**: Placeholder screens (future implementation)

 Web Preview

Open `dashboard-preview.html` and interact with the same features in your browser.

 Technology Stack

 C++ Version
- **SFML 2.5+** - Graphics and window management
- **C++17** - Modern C++ features
- **CMake** - Build system

 Web Version
- **HTML5** - Structure
- **CSS3** - Styling and animations
- **JavaScript (ES6)** - Logic and interactivity

 Screenshots

 Main Menu (T1)
![Menu Screenshot](screenshots/menu.png)
*Responsive navigation with 4 feature buttons*

Dashboard - Habit Logging (T2)
![Dashboard Screenshot](screenshots/dashboard.png)
*Text input and habit tracking interface*

 Features Breakdown

| Feature | Status | Description |
|---------|--------|-------------|
| **Menu Navigation** | Complete | T1 - 4 buttons with routing |
| **Habit Logging** |  Complete | T2 - Input field and display |
| **Charts View** |  Placeholder | Analytics and visualizations |
| **Gamified View** |  Placeholder | XP, levels, achievements |
| **Settings** |  Placeholder | App configuration |
| **Responsive Layout** |  Complete | Handles window resize |
| **Data Persistence** |  Planned | Save/load from files |

 Roadmap

- [ ] Implement chart rendering with habit statistics
- [ ] Add XP and leveling system in gamified view
- [ ] Create settings panel with theme options
- [ ] Add data persistence (SQLite or JSON)
- [ ] Implement streak tracking
- [ ] Add notifications/reminders
- [ ] Export data to CSV

 Contributing

This is an academic/educational project. Feel free to fork and enhance!

 License

This project is available for educational purposes. Free to use and modify.

 Author

Created as part of a productivity tracking system implementation.

 Acknowledgments

- SFML Library - https://www.sfml-dev.org/
- C++ Standard Library
- Modern C++ best practices

 Support

For issues or questions:
- Check `cpp-dashboard/README_T1_T2.md` for detailed documentation
- Review `GITHUB_UPLOAD_GUIDE.md` for GitHub setup
- See build instructions in `cpp-dashboard/BUILD_CONSOLE.md`

---

**Status**: T1 & T2  Complete | Additional features  In Progress
