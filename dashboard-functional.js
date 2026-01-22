// Productivity Dashboard - FULLY FUNCTIONAL VERSION
// Complete implementation with localStorage persistence and real-time features

// Data Storage
let loggedHabits = [];
let selectedHabitName = 'Exercise';
let selectedHabitType = 'binary';
let dailyGoal = 5;
let userXP = 0;
let userLevel = 1;
let userStreak = 0;
let lastLoginDate = null;
let achievements = [];
let notificationsEnabled = true;
let currentTheme = 'Light';

// Initialize achievements
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

// Load data from localStorage
function loadData() {
    const saved = localStorage.getItem('productivityDashboard');
    if (saved) {
        const data = JSON.parse(saved);
        loggedHabits = data.habits || [];
        userXP = data.xp || 0;
        userLevel = data.level || 1;
        userStreak = data.streak || 0;
        lastLoginDate = data.lastLogin || null;
        dailyGoal = data.dailyGoal || 5;
        notificationsEnabled = data.notifications !== undefined ? data.notifications : true;
        currentTheme = data.theme || 'Light';
    }
    
    initAchievements();
    updateStreak();
    updateLevel();
    console.log('[DATA] Loaded from localStorage:', { habits: loggedHabits.length, xp: userXP, level: userLevel, streak: userStreak });
}

// Save data to localStorage
function saveData() {
    const data = {
        habits: loggedHabits,
        xp: userXP,
        level: userLevel,
        streak: userStreak,
        lastLogin: new Date().toDateString(),
        dailyGoal: dailyGoal,
        notifications: notificationsEnabled,
        theme: currentTheme
    };
    localStorage.setItem('productivityDashboard', JSON.stringify(data));
    localStorage.setItem('achievements', JSON.stringify(achievements));
    console.log('[DATA] Saved to localStorage');
}

// Update streak based on login dates
function updateStreak() {
    const today = new Date().toDateString();
    
    if (lastLoginDate === today) {
        // Already logged in today, streak continues
        return;
    }
    
    if (lastLoginDate) {
        const lastDate = new Date(lastLoginDate);
        const todayDate = new Date(today);
        const diffTime = todayDate - lastDate;
        const diffDays = Math.floor(diffTime / (1000 * 60 * 60 * 24));
        
        if (diffDays === 1) {
            // Consecutive day - increment streak
            userStreak++;
            console.log('[STREAK] Increased to:', userStreak);
        } else if (diffDays > 1) {
            // Missed days - reset streak
            userStreak = 1;
            console.log('[STREAK] Reset to 1 (missed days)');
        }
    } else {
        // First login
        userStreak = 1;
    }
    
    lastLoginDate = today;
    checkAchievements();
}

// Calculate XP needed for next level
function getXPForNextLevel() {
    return userLevel * 100;
}

// Update level based on XP
function updateLevel() {
    const xpNeeded = getXPForNextLevel();
    while (userXP >= xpNeeded) {
        userLevel++;
        console.log('[LEVEL UP!] Now Level', userLevel);
        checkAchievements();
    }
}

// Check and unlock achievements
function checkAchievements() {
    let newUnlocks = false;
    
    // First Steps - log first habit
    if (loggedHabits.length >= 1 && !achievements[0].unlocked) {
        achievements[0].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: First Steps 🏆');
    }
    
    // Week Warrior - 7 day streak
    if (userStreak >= 7 && !achievements[1].unlocked) {
        achievements[1].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: Week Warrior 📅');
    }
    
    // Hydration Hero - 50 glasses of water
    const waterCount = loggedHabits.filter(h => h.name === 'Water').reduce((sum, h) => sum + h.value, 0);
    if (waterCount >= 50 && !achievements[2].unlocked) {
        achievements[2].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: Hydration Hero 💧');
    }
    
    // Bookworm - 500 minutes reading
    const readingMinutes = loggedHabits.filter(h => h.name === 'Reading').reduce((sum, h) => sum + h.value, 0);
    if (readingMinutes >= 500 && !achievements[3].unlocked) {
        achievements[3].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: Bookworm 📚');
    }
    
    // Level 5 Master
    if (userLevel >= 5 && !achievements[4].unlocked) {
        achievements[4].unlocked = true;
        newUnlocks = true;
        console.log('[ACHIEVEMENT] Unlocked: Level 5 Master ⭐');
    }
    
    // Perfect Day - 10 habits in one day
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

// Navigation function
function navigateTo(screenName) {
    const screens = document.querySelectorAll('.screen');
    screens.forEach(screen => screen.classList.add('hidden'));
    
    const targetScreen = document.getElementById(screenName + 'Screen');
    if (targetScreen) {
        targetScreen.classList.remove('hidden');
    }
    
    // Update screen-specific content
    if (screenName === 'dashboard') {
        updateHabitsList();
        updateClock();
    } else if (screenName === 'charts') {
        updateCharts();
    } else if (screenName === 'gamified') {
        updateGamification();
    } else if (screenName === 'settings') {
        updateSettingsDisplay();
    }
    
    console.log(`[NAVIGATION] → ${screenName} screen`);
}

// Select habit type
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

// Log habit with XP calculation
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
        timestamp: now.toISOString(),
        timeString: now.toLocaleTimeString(),
        dateString: now.toDateString()
    };
    
    loggedHabits.push(habit);
    
    // Award XP
    let xpGained = 0;
    switch(selectedHabitType) {
        case 'binary':
            xpGained = 10;
            break;
        case 'count':
            xpGained = Math.min(value * 2, 50); // 2 XP per count, max 50
            break;
        case 'duration':
            xpGained = Math.min(value, 100); // 1 XP per minute, max 100
            break;
    }
    
    userXP += xpGained;
    updateLevel();
    checkAchievements();
    
    updateHabitsList();
    showFeedback(`+${xpGained} XP`);
    saveData();
    
    document.getElementById('binaryCheckbox').checked = false;
    document.getElementById('countValue').value = '';
    document.getElementById('durationValue').value = '';
    
    console.log(`[LOGGED] ${habit.name} - ${habit.displayValue} (+${xpGained} XP) at ${habit.timeString}`);
}

// Update habits list
function updateHabitsList() {
    const habitsList = document.getElementById('habitsList');
    const habitCount = document.getElementById('habitCount');
    
    // Filter today's habits
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

// Show feedback animation
function showFeedback(message = 'Logged! ✓') {
    const overlay = document.getElementById('feedbackOverlay');
    const text = overlay.querySelector('.feedback-text');
    text.textContent = message;
    overlay.classList.remove('hidden');
    
    setTimeout(() => {
        overlay.classList.add('hidden');
    }, 1500);
}

// Update real-time clock
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

// Update charts with real data
function updateCharts() {
    const last7Days = [];
    const today = new Date();
    
    for (let i = 6; i >= 0; i--) {
        const date = new Date(today);
        date.setDate(date.getDate() - i);
        last7Days.push(date.toDateString());
    }
    
    const dayNames = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'];
    const chartContainer = document.getElementById('barChart');
    
    if (chartContainer) {
        chartContainer.innerHTML = '';
        
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
    
    // Update statistics
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

// Update gamification display
function updateGamification() {
    document.getElementById('userLevel').textContent = userLevel;
    document.getElementById('currentXP').textContent = userXP;
    const xpNeeded = getXPForNextLevel();
    document.getElementById('neededXP').textContent = xpNeeded;
    document.getElementById('userStreak').textContent = userStreak;
    
    const xpProgress = ((userXP % 100) / 100) * 100;
    document.getElementById('xpProgress').style.width = `${xpProgress}%`;
    
    // Update achievements
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
    saveData();
    console.log(`[SETTINGS] Daily goal: ${dailyGoal}`);
}

// Toggle notifications
function toggleNotifications() {
    notificationsEnabled = !notificationsEnabled;
    saveData();
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
    saveData();
    console.log(`[SETTINGS] Theme: ${theme}`);
}

// Export data
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

// Clear all data (for demo reset)
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
            
            // Refresh the page
            location.reload();
        }
    }
}

// Initialize on page load
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
    
    loadData();
    updateClock();
    setInterval(updateClock, 1000); // Update clock every second
    
    console.log('[INIT] Dashboard ready! Current stats:');
    console.log(`  Level: ${userLevel} | XP: ${userXP} | Streak: ${userStreak} days`);
    console.log(`  Total habits logged: ${loggedHabits.length}`);
    console.log(`  Achievements unlocked: ${achievements.filter(a => a.unlocked).length}/${achievements.length}\n`);
});
