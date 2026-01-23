/*
═══════════════════════════════════════════════════════════════════════
  PRODUCTIVITY DASHBOARD - FULLY FUNCTIONAL VERSION
  NEW CODE HIGHLIGHTS - Everything marked with // 🆕 is NEW!
═══════════════════════════════════════════════════════════════════════
*/

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW: Data Storage Variables (Lines 4-15)
// ═══════════════════════════════════════════════════════════════
let loggedHabits = [];
let selectedHabitName = 'Exercise';
let selectedHabitType = 'binary';
let dailyGoal = 5;
let userXP = 0;                    // 🆕 NEW: Track XP points
let userLevel = 1;                 // 🆕 NEW: Track level
let userStreak = 0;                // 🆕 NEW: Track daily streak
let lastLoginDate = null;          // 🆕 NEW: Track last login for streak
let achievements = [];             // 🆕 NEW: Achievement array
let notificationsEnabled = true;
let currentTheme = 'Light';

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Initialize achievements (Lines 18-30)
// ═══════════════════════════════════════════════════════════════
function initAchievements() {
    const defaultAchievements = [
        { id: 'first_habit', name: 'First Steps', icon: '🏆', description: 'Log your first habit', unlocked: false },
        { id: 'week_warrior', name: 'Week Warrior', icon: '📅', description: 'Log habits for 7 days straight', unlocked: false },
        { id: 'hydration_hero', name: 'Hydration Hero', icon: '💧', description: 'Log 50 glasses of water', unlocked: false },
        { id: 'bookworm', name: 'Bookworm', icon: '📚', description: 'Read for 500 minutes total', unlocked: false },
        { id: 'level_5', name: 'Level 5 Master', icon: '⭐', description: 'Reach Level 5', unlocked: false },
        { id: 'perfect_day', name: 'Perfect Day', icon: '🎯', description: 'Complete 10 habits in one day', unlocked: false }
    ];
    
    const saved = localStorage.getItem('achievements');
    achievements = saved ? JSON.parse(saved) : defaultAchievements;
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Load data from localStorage (Lines 33-51)
// This restores all user data when page loads!
// ═══════════════════════════════════════════════════════════════
function loadData() {
    const saved = localStorage.getItem('productivityDashboard');
    if (saved) {
        const data = JSON.parse(saved);
        loggedHabits = data.habits || [];
        userXP = data.xp || 0;                    // 🆕 Restore XP
        userLevel = data.level || 1;              // 🆕 Restore level
        userStreak = data.streak || 0;            // 🆕 Restore streak
        lastLoginDate = data.lastLogin || null;   // 🆕 Restore last login
        dailyGoal = data.dailyGoal || 5;
        notificationsEnabled = data.notifications !== undefined ? data.notifications : true;
        currentTheme = data.theme || 'Light';
    }
    
    initAchievements();
    updateStreak();                               // 🆕 Calculate streak
    updateLevel();                                // 🆕 Update level
    console.log('[DATA] Loaded from localStorage:', { habits: loggedHabits.length, xp: userXP, level: userLevel, streak: userStreak });
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Save data to localStorage (Lines 54-68)
// This saves ALL user data - called after every action!
// ═══════════════════════════════════════════════════════════════
function saveData() {
    const data = {
        habits: loggedHabits,
        xp: userXP,                   // 🆕 Save XP
        level: userLevel,             // 🆕 Save level
        streak: userStreak,           // 🆕 Save streak
        lastLogin: new Date().toDateString(),
        dailyGoal: dailyGoal,
        notifications: notificationsEnabled,
        theme: currentTheme
    };
    localStorage.setItem('productivityDashboard', JSON.stringify(data));
    localStorage.setItem('achievements', JSON.stringify(achievements));
    console.log('[DATA] Saved to localStorage');
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Update streak based on login dates (Lines 71-101)
// Calculates consecutive daily logins
// ═══════════════════════════════════════════════════════════════
function updateStreak() {
    const today = new Date().toDateString();
    
    if (lastLoginDate === today) {
        return; // Already logged in today
    }
    
    if (lastLoginDate) {
        const lastDate = new Date(lastLoginDate);
        const todayDate = new Date(today);
        const diffTime = todayDate - lastDate;
        const diffDays = Math.floor(diffTime / (1000 * 60 * 60 * 24));
        
        if (diffDays === 1) {
            userStreak++;  // 🆕 Consecutive day - increment
            console.log('[STREAK] Increased to:', userStreak);
        } else if (diffDays > 1) {
            userStreak = 1;  // 🆕 Missed days - reset
            console.log('[STREAK] Reset to 1 (missed days)');
        }
    } else {
        userStreak = 1;  // 🆕 First login
    }
    
    lastLoginDate = today;
    checkAchievements();
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Calculate XP needed for next level (Line 104)
// ═══════════════════════════════════════════════════════════════
function getXPForNextLevel() {
    return userLevel * 100;  // 🆕 100 XP per level
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Update level based on XP (Lines 109-116)
// Auto-levels up when XP is sufficient
// ═══════════════════════════════════════════════════════════════
function updateLevel() {
    const xpNeeded = getXPForNextLevel();
    while (userXP >= xpNeeded) {
        userLevel++;  // 🆕 Level up!
        console.log('[LEVEL UP!] Now Level', userLevel);
        checkAchievements();
    }
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Check and unlock achievements (Lines 119-171)
// Progressive achievement system - unlocks as you progress
// ═══════════════════════════════════════════════════════════════
function checkAchievements() {
    let newUnlocks = false;
    
    // 🆕 First Steps - log first habit
    if (loggedHabits.length >= 1 && !achievements[0].unlocked) {
        achievements[0].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: First Steps 🏆');
    }
    
    // 🆕 Week Warrior - 7 day streak
    if (userStreak >= 7 && !achievements[1].unlocked) {
        achievements[1].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: Week Warrior 📅');
    }
    
    // 🆕 Hydration Hero - 50 glasses of water
    const waterCount = loggedHabits.filter(h => h.name === 'Water').reduce((sum, h) => sum + h.value, 0);
    if (waterCount >= 50 && !achievements[2].unlocked) {
        achievements[2].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: Hydration Hero 💧');
    }
    
    // 🆕 Bookworm - 500 minutes reading
    const readingMinutes = loggedHabits.filter(h => h.name === 'Reading').reduce((sum, h) => sum + h.value, 0);
    if (readingMinutes >= 500 && !achievements[3].unlocked) {
        achievements[3].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: Bookworm 📚');
    }
    
    // 🆕 Level 5 Master
    if (userLevel >= 5 && !achievements[4].unlocked) {
        achievements[4].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: Level 5 Master ⭐');
    }
    
    // 🆕 Perfect Day - 10 habits in one day
    const today = new Date().toDateString();
    const todayHabits = loggedHabits.filter(h => new Date(h.timestamp).toDateString() === today);
    if (todayHabits.length >= 10 && !achievements[5].unlocked) {
        achievements[5].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: Perfect Day 🎯');
    }
    
    if (newUnlocks) {
        saveData();
    }
}

// ═══════════════════════════════════════════════════════════════
// Navigation function (MODIFIED to update screens)
// ═══════════════════════════════════════════════════════════════
function navigateTo(screenName) {
    const screens = document.querySelectorAll('.screen');
    screens.forEach(screen => screen.classList.add('hidden'));
    
    const targetScreen = document.getElementById(screenName + 'Screen');
    if (targetScreen) {
        targetScreen.classList.remove('hidden');
    }
    
    // 🆕 NEW: Update screen-specific content with real data
    if (screenName === 'dashboard') {
        updateHabitsList();
        updateClock();
    } else if (screenName === 'charts') {
        updateCharts();       // 🆕 Update charts with real data
    } else if (screenName === 'gamified') {
        updateGamification(); // 🆕 Update gamification display
    } else if (screenName === 'settings') {
        updateSettingsDisplay();
    }
    
    console.log(`[NAVIGATION] → ${screenName} screen`);
}

// Select habit type (same as before)
function selectHabit(habitName, habitType) {
    selectedHabitName = habitName;
    selectedHabitType = habitType;
    
    document.querySelectorAll('.habit-type-btn').forEach(btn => {
        btn.classList.remove('active');
    });
    event.target.classList.add('active');
    
    document.getElementById('selectedHabit').textContent = habitName;
    
    let typeText = '';
    let unitText = 'times';
    
    switch(habitType) {
        case 'binary':
            typeText = 'Check if completed';
            break;
        case 'count':
            typeText = 'Enter count';
            if (habitName === 'Water') unitText = 'glasses';
            else if (habitName === 'Push-ups') unitText = 'reps';
            break;
        case 'duration':
            typeText = 'Enter minutes';
            break;
    }
    
    document.getElementById('inputType').textContent = typeText;
    if (document.getElementById('countUnit')) {
        document.getElementById('countUnit').textContent = unitText;
    }
    
    document.getElementById('binaryInput').classList.add('hidden');
    document.getElementById('countInput').classList.add('hidden');
    document.getElementById('durationInput').classList.add('hidden');
    
    if (habitType === 'binary') {
        document.getElementById('binaryInput').classList.remove('hidden');
    } else if (habitType === 'count') {
        document.getElementById('countInput').classList.remove('hidden');
    } else if (habitType === 'duration') {
        document.getElementById('durationInput').classList.remove('hidden');
    }
    
    document.getElementById('binaryCheckbox').checked = false;
    document.getElementById('countValue').value = '';
    document.getElementById('durationValue').value = '';
    
    console.log(`[HABIT] Selected: ${habitName} (${habitType})`);
}

// ═══════════════════════════════════════════════════════════════
// 🆕 ENHANCED: Log habit with XP calculation (Lines 252-326)
// Now awards XP and triggers level-ups and achievements!
// ═══════════════════════════════════════════════════════════════
function logHabitEnhanced() {
    let value = 0;
    let displayValue = '';
    
    switch(selectedHabitType) {
        case 'binary':
            value = document.getElementById('binaryCheckbox').checked ? 1 : 0;
            displayValue = value ? '✓ Done' : '✗ Not done';
            if (value === 0) {
                alert('Please check the box to mark as completed!');
                return;
            }
            break;
        case 'count':
            const countInput = document.getElementById('countValue').value;
            if (!countInput || countInput <= 0) {
                alert('Please enter a valid count!');
                return;
            }
            value = parseInt(countInput);
            let unit = document.getElementById('countUnit').textContent;
            displayValue = `${value} ${unit}`;
            break;
        case 'duration':
            const durationInput = document.getElementById('durationValue').value;
            if (!durationInput || durationInput <= 0) {
                alert('Please enter valid minutes!');
                return;
            }
            value = parseInt(durationInput);
            displayValue = `${value} min`;
            break;
    }
    
    const now = new Date();
    const habit = {
        name: selectedHabitName,
        type: selectedHabitType,
        value: value,
        displayValue: displayValue,
        timestamp: now.toISOString(),      // 🆕 Full timestamp
        timeString: now.toLocaleTimeString(),  // 🆕 Display time
        dateString: now.toDateString()     // 🆕 Date for filtering
    };
    
    loggedHabits.push(habit);
    
    // ═══════════════════════════════════════════════════════════
    // 🆕 NEW: Award XP based on habit type (Lines 299-311)
    // ═══════════════════════════════════════════════════════════
    let xpGained = 0;
    switch(selectedHabitType) {
        case 'binary':
            xpGained = 10;  // 🆕 Binary = 10 XP
            break;
        case 'count':
            xpGained = Math.min(value * 2, 50);  // 🆕 2 XP per count, max 50
            break;
        case 'duration':
            xpGained = Math.min(value, 100);  // 🆕 1 XP per minute, max 100
            break;
    }
    
    userXP += xpGained;           // 🆕 Add XP
    updateLevel();                // 🆕 Check for level up
    checkAchievements();          // 🆕 Check for achievement unlocks
    
    updateHabitsList();
    showFeedback(`+${xpGained} XP`);  // 🆕 Show XP in feedback
    saveData();                   // 🆕 Save everything
    
    document.getElementById('binaryCheckbox').checked = false;
    document.getElementById('countValue').value = '';
    document.getElementById('durationValue').value = '';
    
    console.log(`[LOGGED] ${habit.name} - ${habit.displayValue} (+${xpGained} XP) at ${habit.timeString}`);
}

// ═══════════════════════════════════════════════════════════════
// 🆕 ENHANCED: Update habits list (Lines 329-365)
// Now filters by today and shows real timestamps
// ═══════════════════════════════════════════════════════════════
function updateHabitsList() {
    const habitsList = document.getElementById('habitsList');
    const habitCount = document.getElementById('habitCount');
    
    // 🆕 Filter today's habits only
    const today = new Date().toDateString();
    const todayHabits = loggedHabits.filter(h => new Date(h.timestamp).toDateString() === today);
    
    habitCount.textContent = todayHabits.length;
    
    if (todayHabits.length === 0) {
        habitsList.innerHTML = '<li class="empty-message">No habits logged yet today. Start tracking!</li>';
        return;
    }
    
    habitsList.innerHTML = '';
    
    todayHabits.reverse().forEach((habit, index) => {
        const li = document.createElement('li');
        li.className = 'habit-item';
        
        let icon = '';
        switch(habit.type) {
            case 'binary': icon = '☑'; break;
            case 'count': icon = '🔢'; break;
            case 'duration': icon = '⏱'; break;
        }
        
        li.innerHTML = `
            <span class="habit-icon">${icon}</span>
            <span class="habit-name">${habit.name}</span>
            <span class="habit-value">${habit.displayValue}</span>
            <span class="habit-time">${habit.timeString}</span>
        `;
        habitsList.appendChild(li);
    });
}

// 🆕 ENHANCED: Show feedback with custom message
function showFeedback(message = 'Logged! ✓') {
    const overlay = document.getElementById('feedbackOverlay');
    const text = overlay.querySelector('.feedback-text');
    text.textContent = message;  // 🆕 Custom message (shows XP)
    overlay.classList.remove('hidden');
    
    setTimeout(() => {
        overlay.classList.add('hidden');
    }, 1500);
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Update real-time clock (Lines 380-393)
// Shows current date/time, updates every second
// ═══════════════════════════════════════════════════════════════
function updateClock() {
    const clockElement = document.getElementById('currentTime');
    if (clockElement) {
        const now = new Date();
        clockElement.textContent = now.toLocaleString('en-US', { 
            weekday: 'short', 
            month: 'short', 
            day: 'numeric', 
            hour: '2-digit', 
            minute: '2-digit',
            second: '2-digit'
        });
    }
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Update charts with real data (Lines 396-444)
// Generates bar chart from actual logged habits
// ═══════════════════════════════════════════════════════════════
function updateCharts() {
    const last7Days = [];
    const today = new Date();
    
    // 🆕 Generate last 7 days
    for (let i = 6; i >= 0; i--) {
        const date = new Date(today);
        date.setDate(date.getDate() - i);
        last7Days.push(date.toDateString());
    }
    
    const dayNames = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'];
    const chartContainer = document.getElementById('barChart');
    
    if (chartContainer) {
        chartContainer.innerHTML = '';
        
        // 🆕 Create bar for each day
        last7Days.forEach((dateStr, index) => {
            const dayHabits = loggedHabits.filter(h => new Date(h.timestamp).toDateString() === dateStr);
            const count = dayHabits.length;
            const maxHeight = 100;
            const height = count > 0 ? Math.min((count / 10) * 100, maxHeight) : 10;
            
            const date = new Date(dateStr);
            const dayName = dayNames[date.getDay()];
            
            const barGroup = document.createElement('div');
            barGroup.className = 'bar-group';
            barGroup.innerHTML = `
                <div class="bar-label">${dayName}</div>
                <div class="bar" style="height: ${height}%;"></div>
                <div class="bar-value">${count}</div>
            `;
            chartContainer.appendChild(barGroup);
        });
    }
    
    // 🆕 Update statistics from real data
    const waterCount = loggedHabits.filter(h => h.name === 'Water').reduce((sum, h) => sum + h.value, 0);
    const waterAvg = loggedHabits.filter(h => h.name === 'Water').length > 0 
        ? (waterCount / loggedHabits.filter(h => h.name === 'Water').length).toFixed(1) 
        : 0;
    
    const readingMinutes = loggedHabits.filter(h => h.name === 'Reading').reduce((sum, h) => sum + h.value, 0);
    const exerciseDays = new Set(loggedHabits.filter(h => h.name === 'Exercise').map(h => new Date(h.timestamp).toDateString())).size;
    
    document.getElementById('avgWater').textContent = `${waterAvg} glasses`;
    document.getElementById('totalReading').textContent = `${readingMinutes} min`;
    document.getElementById('exerciseDays').textContent = `${exerciseDays} days`;
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Update gamification display (Lines 447-472)
// Shows real XP, level, streak, and achievements
// ═══════════════════════════════════════════════════════════════
function updateGamification() {
    document.getElementById('userLevel').textContent = userLevel;
    document.getElementById('currentXP').textContent = userXP;
    const xpNeeded = getXPForNextLevel();
    document.getElementById('neededXP').textContent = xpNeeded;
    document.getElementById('userStreak').textContent = userStreak;
    
    // 🆕 Update XP progress bar
    const xpProgress = ((userXP % 100) / 100) * 100;
    document.getElementById('xpProgress').style.width = `${xpProgress}%`;
    
    // 🆕 Update achievements grid
    const achievementsGrid = document.getElementById('achievementsGrid');
    if (achievementsGrid) {
        achievementsGrid.innerHTML = '';
        achievements.forEach(ach => {
            const div = document.createElement('div');
            div.className = `achievement ${ach.unlocked ? 'unlocked' : 'locked'}`;
            div.innerHTML = `
                <div class="achievement-icon">${ach.icon}</div>
                <div class="achievement-name">${ach.name}</div>
            `;
            div.title = ach.description;
            achievementsGrid.appendChild(div);
        });
    }
}

// Update settings display
function updateSettingsDisplay() {
    const notifToggle = document.getElementById('notificationsToggle');
    if (notifToggle) {
        notifToggle.checked = notificationsEnabled;
    }
    
    const goalValue = document.getElementById('goalValue');
    if (goalValue) {
        goalValue.textContent = dailyGoal;
    }
    
    document.querySelectorAll('.theme-btn').forEach(btn => {
        btn.classList.remove('active');
        if (btn.textContent === currentTheme) {
            btn.classList.add('active');
        }
    });
}

// Change daily goal
function changeGoal(delta) {
    dailyGoal = Math.max(1, Math.min(20, dailyGoal + delta));
    document.getElementById('goalValue').textContent = dailyGoal;
    saveData();  // 🆕 Save after change
    console.log(`[SETTINGS] Daily goal: ${dailyGoal}`);
}

// Toggle notifications
function toggleNotifications() {
    notificationsEnabled = !notificationsEnabled;
    saveData();  // 🆕 Save after change
    console.log(`[SETTINGS] Notifications: ${notificationsEnabled ? 'ON' : 'OFF'}`);
}

// Change theme
function changeTheme(theme) {
    currentTheme = theme;
    document.querySelectorAll('.theme-btn').forEach(btn => {
        btn.classList.remove('active');
        if (btn.textContent === theme) {
            btn.classList.add('active');
        }
    });
    saveData();  // 🆕 Save after change
    console.log(`[SETTINGS] Theme: ${theme}`);
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Export data (Lines 523-543)
// Downloads all data as JSON file
// ═══════════════════════════════════════════════════════════════
function exportData() {
    const data = {
        habits: loggedHabits,
        xp: userXP,
        level: userLevel,
        streak: userStreak,
        achievements: achievements,
        exportDate: new Date().toISOString()
    };
    
    const json = JSON.stringify(data, null, 2);
    const blob = new Blob([json], { type: 'application/json' });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = `productivity-dashboard-${new Date().toISOString().split('T')[0]}.json`;
    a.click();
    
    console.log('[EXPORT] Data exported successfully');
    alert('Data exported successfully!');
}

// ═══════════════════════════════════════════════════════════════
// 🆕 NEW FUNCTION: Clear all data (Lines 546-565)
// Resets everything for fresh demo
// ═══════════════════════════════════════════════════════════════
function clearAllData() {
    if (confirm('⚠️ This will delete ALL your data! Are you sure?\n\nThis is useful for starting a fresh demo.')) {
        if (confirm('Really delete everything? This cannot be undone!')) {
            localStorage.clear();
            loggedHabits = [];
            userXP = 0;
            userLevel = 1;
            userStreak = 0;
            dailyGoal = 5;
            initAchievements();
            saveData();
            
            console.log('[CLEAR] All data cleared - fresh start!');
            alert('✅ All data cleared! Starting fresh.');
            
            location.reload();  // 🆕 Reload page
        }
    }
}

// ═══════════════════════════════════════════════════════════════
// 🆕 ENHANCED: Initialize on page load (Lines 568-587)
// Loads data and starts clock
// ═══════════════════════════════════════════════════════════════
document.addEventListener('DOMContentLoaded', () => {
    console.log('==========================================================');
    console.log('  PRODUCTIVITY DASHBOARD - FULLY FUNCTIONAL');
    console.log('==========================================================');
    console.log('✅ Real-time data persistence with localStorage');
    console.log('✅ Dynamic XP and leveling system');
    console.log('✅ Achievement tracking');
    console.log('✅ Streak calculation');
    console.log('✅ Live charts from actual data');
    console.log('==========================================================\n');
    
    loadData();                              // 🆕 Load saved data
    updateClock();                           // 🆕 Update clock immediately
    setInterval(updateClock, 1000);          // 🆕 Update every second
    
    console.log('[INIT] Dashboard ready! Current stats:');
    console.log(`  Level: ${userLevel} | XP: ${userXP} | Streak: ${userStreak} days`);
    console.log(`  Total habits logged: ${loggedHabits.length}`);
    console.log(`  Achievements unlocked: ${achievements.filter(a => a.unlocked).length}/${achievements.length}\n`);
});

/*
═══════════════════════════════════════════════════════════════════════
  END OF NEW CODE
  
  🆕 SUMMARY OF NEW FEATURES:
  
  1. localStorage persistence (loadData, saveData)
  2. XP calculation system (10-100 XP per habit)
  3. Auto-leveling (every 100 XP)
  4. Achievement system (6 progressive achievements)
  5. Streak tracking (daily login counter)
  6. Real-time clock (updates every second)
  7. Dynamic charts (last 7 days from real data)
  8. Live gamification display (XP bar, achievements)
  9. Export to JSON (download backup)
  10. Clear data function (reset for demo)
  
  All data persists between sessions! Close browser and reopen - 
  everything is still there! 🎉
═══════════════════════════════════════════════════════════════════════
*/
