// Dashboard Enhanced JavaScript - T2 Multi-Type Implementation

let loggedHabits = [];
let selectedHabitName = 'Exercise';
let selectedHabitType = 'binary';

// Navigation function (T1)
function navigateTo(screenName) {
    const screens = document.querySelectorAll('.screen');
    screens.forEach(screen => {
        screen.classList.add('hidden');
    });

    const targetScreen = document.getElementById(screenName + 'Screen');
    if (targetScreen) {
        targetScreen.classList.remove('hidden');
    }

    console.log(`Navigated to: ${screenName}`);
}

// Select habit type
function selectHabit(habitName, habitType) {
    selectedHabitName = habitName;
    selectedHabitType = habitType;

    // Update active button
    document.querySelectorAll('.habit-type-btn').forEach(btn => {
        btn.classList.remove('active');
    });
    event.target.classList.add('active');

    // Update instruction text
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

    // Show/hide appropriate input
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

    // Clear inputs
    document.getElementById('binaryCheckbox').checked = false;
    document.getElementById('countValue').value = '';
    document.getElementById('durationValue').value = '';

    console.log(`Selected habit: ${habitName} (${habitType})`);
}

// Enhanced habit logging function
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

    // Create habit object
    const habit = {
        name: selectedHabitName,
        type: selectedHabitType,
        value: value,
        displayValue: displayValue,
        timestamp: new Date().toLocaleTimeString()
    };

    loggedHabits.push(habit);
    updateHabitsList();
    showFeedback();
    
    // Reset inputs
    document.getElementById('binaryCheckbox').checked = false;
    document.getElementById('countValue').value = '';
    document.getElementById('durationValue').value = '';

    // Console feedback (backend simulation)
    console.log(`[LOGGED] ${habit.name} - ${habit.displayValue} at ${habit.timestamp}`);
}

// Update habits list display
function updateHabitsList() {
    const habitsList = document.getElementById('habitsList');
    const habitCount = document.getElementById('habitCount');
    
    habitCount.textContent = loggedHabits.length;
    
    if (loggedHabits.length === 0) {
        habitsList.innerHTML = '<li class="empty-message">No habits logged yet. Start tracking!</li>';
        return;
    }

    habitsList.innerHTML = '';
    
    loggedHabits.forEach((habit, index) => {
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
            <span class="habit-time">${habit.timestamp}</span>
        `;
        habitsList.appendChild(li);
    });
}

// Show feedback animation
function showFeedback() {
    const overlay = document.getElementById('feedbackOverlay');
    overlay.classList.remove('hidden');
    
    setTimeout(() => {
        overlay.classList.add('hidden');
    }, 1500);
}

// Initialize on page load
document.addEventListener('DOMContentLoaded', () => {
    console.log('Productivity Dashboard Enhanced Preview Loaded');
    console.log('T1 - Menu Interface: ✓');
    console.log('T2 Enhanced - Multi-Type Habit Logging: ✓');
    console.log('Features:');
    console.log('  - Binary habits (checkbox)');
    console.log('  - Count-based habits (numeric input)');
    console.log('  - Duration-based habits (time tracking)');
    console.log('  - Backend data model simulation');
    console.log('  - Animated feedback');
});
