// Dashboard Preview JavaScript - T1 & T2 Implementation

let loggedHabits = [];

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

// Habit logging function (T2)
function logHabit() {
    const input = document.getElementById('habitInput');
    const habitName = input.value.trim();

    if (habitName === '') {
        alert('Please enter a habit name!');
        return;
    }

    loggedHabits.push(habitName);
    input.value = '';
    
    updateHabitsList();
    
    console.log(`Habit logged: ${habitName}`);
}

// Update habits list display
function updateHabitsList() {
    const habitsList = document.getElementById('habitsList');
    
    if (loggedHabits.length === 0) {
        habitsList.innerHTML = '<li class="empty-message">No habits logged yet. Start tracking!</li>';
        return;
    }

    habitsList.innerHTML = '';
    
    loggedHabits.forEach((habit, index) => {
        const li = document.createElement('li');
        li.innerHTML = `<span><span class="habit-number">${index + 1}.</span> ${habit}</span>`;
        habitsList.appendChild(li);
    });
}

// Handle Enter key in input field
function handleEnter(event) {
    if (event.key === 'Enter') {
        logHabit();
    }
}

// Initialize on page load
document.addEventListener('DOMContentLoaded', () => {
    console.log('Productivity Dashboard Preview Loaded');
    console.log('T1 - Menu Interface: ✓');
    console.log('T2 - Habit Logging: ✓');
    
    const habitInput = document.getElementById('habitInput');
    if (habitInput) {
        habitInput.focus();
    }
});

// Demo mode - show example navigation
setTimeout(() => {
    console.log('Demo: Navigation system ready. Click any menu button to test routing.');
}, 1000);
