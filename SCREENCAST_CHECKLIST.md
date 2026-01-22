# 🎬 SCREENCAST RECORDING CHECKLIST

## Before Recording

### Setup
- [ ] Close unnecessary applications
- [ ] Increase screen resolution to 1920x1080
- [ ] Set font size to 16-18pt in code editor
- [ ] Prepare a clean desktop
- [ ] Test microphone audio
- [ ] Have water nearby (for speaking)

### Files to Show
- [ ] `main_complete.cpp` - Main application
- [ ] `HabitModel.hpp` - Data model with algorithms
- [ ] `ChartsDataModel.hpp` - Sample data
- [ ] `GamificationModel.hpp` - XP calculation
- [ ] `DashboardScreenEnhanced.hpp` - Multi-type inputs
- [ ] `CMakeLists.txt` - Build configuration

---

## Recording Script (10-12 minutes)

### PART 1: Introduction (30 seconds)
**Script**:
"Hello, I'm Jayson Dixon, and this is my Productivity Dashboard application for Advanced Software Engineering. This project features multi-type habit tracking, data analytics with charts, gamification with rewards, and a comprehensive settings system. Let me show you how it works."

**Actions**:
- Show the menu screen
- Point to each button

---

### PART 2: Feature Demonstration (3 minutes)

#### 2.1 Dashboard - Habit Logging (1 min)
**Script**:
"Starting with the Dashboard, I can log three types of habits. Binary habits use a checkbox - like Exercise, which I'll mark as complete. Count-based habits take a number - here I'll log 8 glasses of water. And duration-based habits track time - let me log 30 minutes of reading."

**Actions**:
1. Click Dashboard button
2. Select Exercise → check box → Log
3. Select Water → type "8" → Log
4. Select Reading → type "30" → Log
5. Show the habit list updating

#### 2.2 Charts & Analytics (1 min)
**Script**:
"The Charts screen visualizes my progress over 6 days. Each bar represents daily water intake, and the statistics show I exercised 4 out of 6 days, drank an average of 7 glasses per day, and read a total of 295 minutes this week."

**Actions**:
1. Click Back → Charts
2. Point to each bar
3. Highlight the statistics section

#### 2.3 Gamification (45 seconds)
**Script**:
"The Gamified view shows my progress. I'm at Level 5 with 450 XP, maintaining a 12-day streak. I've unlocked 3 achievements so far, and the leaderboard shows I'm ranked 4th out of 6 players, with goals to reach like Alex_Fit at the top."

**Actions**:
1. Click Back → Gamified View
2. Point to XP bar
3. Show achievements (unlocked vs locked)
4. Point to leaderboard and "You" entry

#### 2.4 Settings (15 seconds)
**Script**:
"Settings let me customize notifications, choose themes, set daily goals, and manage my data. I can increase my goal from 5 to 6 habits per day, toggle notifications, and export data if needed."

**Actions**:
1. Click Back → Settings
2. Click + button to increase goal
3. Show notification toggle

---

### PART 3: Code Walkthrough (5 minutes)

#### 3.1 HabitModel.hpp (1 min)
**Script**:
"Let me show you the code. In HabitModel.hpp, I use an enum class to define the three habit types: Binary, Count, and Duration. The Habit struct stores each entry with its type, value, and timestamp. The addHabit function handles logging - it takes the habit name, type, and value, creates a new habit entry, saves it to file, and outputs console feedback based on the habit type."

**Actions**:
1. Open `HabitModel.hpp`
2. Scroll to enum (lines 10-14)
3. Show Habit struct (lines 16-27)
4. Show addHabit function (lines 47-70)
5. **Zoom in** on the switch statement

**Key Code to Highlight**:
```cpp
Lines 47-70: addHabit() function
Lines 58-68: Console feedback switch statement
```

#### 3.2 ChartsDataModel.hpp (1 min)
**Script**:
"For the charts, ChartsDataModel contains 6 days of sample data. Each DailyData object stores exercise count, water glasses, and minutes for different activities. The getAverageWater algorithm iterates through all days, sums the water intake, and divides by the number of days to get the average."

**Actions**:
1. Open `ChartsDataModel.hpp`
2. Show constructor with sample data (lines 24-29)
3. Show getAverageWater algorithm (lines 42-49)
4. **Zoom in** on the calculation logic

**Key Code to Highlight**:
```cpp
Lines 24-29: Sample data initialization
Lines 42-49: Average calculation algorithm
```

#### 3.3 GamificationModel.hpp (1 min 30 sec)
**Script**:
"The gamification system tracks XP, levels, and achievements. The XP calculation uses modular arithmetic - each level requires 100 XP, so getXPForNextLevel multiplies the current level by 100. The getXPProgress function uses modulo to show progress within the current level. Achievement unlocking happens in checkAchievements - it evaluates conditions like 'if current streak is 7 or more, unlock Week Warrior' or 'if level is 5 or more, unlock Level 5 achievement'."

**Actions**:
1. Open `GamificationModel.hpp`
2. Show Achievement struct (lines 10-19)
3. Show LeaderboardEntry struct (lines 21-28)
4. Show XP calculation (lines 53-59)
5. Show checkAchievements logic (lines 61-66)
6. **Zoom in** on each function

**Key Code to Highlight**:
```cpp
Lines 53-59: XP calculation algorithms
Lines 61-66: Achievement unlock logic
Lines 42-48: Leaderboard initialization
```

#### 3.4 DashboardScreenEnhanced.hpp (1 min)
**Script**:
"The Dashboard UI handles multiple input types. When a habit is selected, the selectHabitType function updates the UI to show the appropriate control - checkboxes for binary, numeric input for count, or time input for duration. The logCurrentHabit function reads the value from the active control, calls the data model to save it, triggers a feedback animation, and resets the inputs."

**Actions**:
1. Open `DashboardScreenEnhanced.hpp`
2. Show selectHabitType (lines 100-125)
3. Show logCurrentHabit (lines 127-150)
4. **Zoom in** on the type switching logic

**Key Code to Highlight**:
```cpp
Lines 100-125: Input type switching
Lines 127-150: Habit logging with validation
```

#### 3.5 UI Architecture (30 seconds)
**Script**:
"The architecture uses a screen-based system. The ScreenManager handles navigation between screens - Menu, Dashboard, Charts, Gamified, and Settings. Each screen implements the Screen interface with handleEvent, update, and draw methods. The Button class encapsulates hover effects, click handling, and callback functions."

**Actions**:
1. Open `ScreenManager.hpp` (show navigation logic)
2. Open `Screen.hpp` (show interface)
3. Open `Button.hpp` (show event handling)

---

### PART 4: Build Process (2 minutes)

#### 4.1 Clean Build Directory (15 seconds)
**Script**:
"Now let me demonstrate the build process. First, I'll clean any existing build files."

**Actions**:
```powershell
cd cpp-dashboard
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
mkdir build
cd build
```

#### 4.2 CMake Configuration (45 seconds)
**Script**:
"Next, I'll configure the project with CMake. The CMakeLists.txt file specifies C++17 as the standard, finds the SFML library, and links the graphics, window, and system components. I'm using vcpkg to manage dependencies."

**Actions**:
```powershell
# Show CMakeLists.txt first
# Then run cmake
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

**Point out in CMakeLists.txt**:
- Line 4: C++17 standard
- Line 10: SFML package search
- Line 13: Executable creation
- Lines 15-19: Library linking

#### 4.3 Compilation (45 seconds)
**Script**:
"Now I'll compile the project. CMake will invoke the compiler to build all source files and link them with SFML libraries."

**Actions**:
```powershell
cmake --build . --config Release
```

**While compiling, mention**:
- "Compiling main_complete.cpp..."
- "Linking SFML libraries..."
- "Creating executable..."

#### 4.4 Execution (15 seconds)
**Script**:
"And here's the executable running."

**Actions**:
```powershell
.\Release\ProductivityDashboard.exe
```

**Show**: Application window opening

---

### PART 5: Research & Hurdles (2 minutes)

#### Research Areas (1 min)
**Script**:
"During development, I researched several key areas. For the SFML library, I studied event handling patterns - how to capture mouse clicks, text input, and window resize events. For gamification, I researched XP curve design and achievement systems, looking at how games balance progression to keep users engaged. I also explored data persistence strategies, ultimately choosing a pipe-delimited format for its simplicity and human readability."

**Topics to Cover**:
1. SFML event system and callbacks
2. Gamification psychology and XP curves
3. File I/O with structured data
4. UI/UX principles for feedback

#### Hurdles Encountered (1 min)
**Script**:
"I faced several challenges. The biggest was handling multiple input types in one screen. My solution was to create three separate input controls and show/hide them based on the selected habit type. Another challenge was window resize responsiveness - UI elements would stay in fixed positions. I solved this by recalculating positions proportionally when the window resizes. Finally, data persistence required a format that could store different types and values. I used a pipe-delimited format where each line has name, type integer, value, and timestamp."

**Hurdles**:
1. **Multi-type inputs** → Dynamic UI with show/hide
2. **Window resize** → Proportional repositioning
3. **Data format** → Pipe-delimited structure

---

### PART 6: Closing (15 seconds)
**Script**:
"This project demonstrates software architecture with screen-based navigation, algorithm development for XP and data aggregation, persistent data storage, and responsive UI design. The complete source code, documentation, and build files are available on GitHub. Thank you for watching!"

**Actions**:
- Show GitHub repository in browser
- Show README.md
- End recording

---

## After Recording

### Editing Checklist
- [ ] Trim dead air at start/end
- [ ] Add title screen (0-3 seconds)
- [ ] Add subtitles for key algorithms
- [ ] Highlight code sections with zoom/box
- [ ] Add transitions between parts
- [ ] Check audio levels
- [ ] Export in 1080p

### Upload to YouTube
- [ ] Title: "Productivity Dashboard - Advanced Software Engineering Project"
- [ ] Description: Include GitHub link and feature list
- [ ] Tags: C++, SFML, Software Engineering, Habit Tracking
- [ ] Visibility: Unlisted (if only for submission) or Public
- [ ] Copy link for submission

---

## Submission

### FSO Upload
1. **Text/PDF file containing**:
   - GitHub URL: https://github.com/JaysonDixon/ProductivityDashboard
   - YouTube link: [Your video URL]
   - Build instructions (copy from FINAL_SUBMISSION.md)

2. **Executable file**:
   - ProductivityDashboard.exe (from Release build)
   - OR zip with exe + assets folder

3. **Additional info in Feedback**:
   - Mention any special requirements
   - Note that web version is also available

---

## Time Estimates

| Section | Time | Notes |
|---------|------|-------|
| Introduction | 0:30 | Keep brief |
| Feature Demo | 3:00 | Show all 5 screens |
| Code Walkthrough | 5:00 | Focus on algorithms |
| Build Process | 2:00 | Real-time compilation |
| Research/Hurdles | 2:00 | Be specific |
| Closing | 0:15 | Include GitHub link |
| **TOTAL** | **12:45** | Target: 10-12 min |

---

## Pro Tips

1. **Practice First**: Record a practice run without submitting
2. **Speak Clearly**: Pretend you're teaching someone
3. **Pause When Needed**: Edit out dead space later
4. **Show, Don't Tell**: Let the application demonstrate features
5. **Highlight Algorithms**: Zoom in on key code sections
6. **Be Honest**: Discuss real challenges you faced
7. **Stay Focused**: Stick to the script, avoid tangents
8. **Test Everything**: Run the app before recording to avoid surprises

---

**GOOD LUCK! 🎬**
