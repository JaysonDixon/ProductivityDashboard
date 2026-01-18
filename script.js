let tasks = JSON.parse(localStorage.getItem('tasks')) || [];
let timerInterval = null;
let timeLeft = 25 * 60;
let isPaused = false;
let pomodoroCount = parseInt(localStorage.getItem('pomodoroCount')) || 0;
let completedTasksCount = parseInt(localStorage.getItem('completedTasksCount')) || 0;
let totalFocusTime = parseInt(localStorage.getItem('totalFocusTime')) || 0;

function updateDateTime() {
    const now = new Date();
    const options = { 
        weekday: 'long', 
        year: 'numeric', 
        month: 'long', 
        day: 'numeric',
        hour: '2-digit',
        minute: '2-digit'
    };
    document.getElementById('datetime').textContent = now.toLocaleDateString('en-US', options);
}

function addTask() {
    const taskInput = document.getElementById('taskInput');
    const taskText = taskInput.value.trim();
    
    if (taskText) {
        tasks.push({ text: taskText, completed: false });
        taskInput.value = '';
        saveTasks();
        renderTasks();
    }
}

function toggleTask(index) {
    tasks[index].completed = !tasks[index].completed;
    if (tasks[index].completed) {
        completedTasksCount++;
        localStorage.setItem('completedTasksCount', completedTasksCount);
        updateStats();
    }
    saveTasks();
    renderTasks();
}

function deleteTask(index) {
    tasks.splice(index, 1);
    saveTasks();
    renderTasks();
}

function saveTasks() {
    localStorage.setItem('tasks', JSON.stringify(tasks));
}

function renderTasks() {
    const taskList = document.getElementById('taskList');
    taskList.innerHTML = '';
    
    tasks.forEach((task, index) => {
        const li = document.createElement('li');
        li.className = task.completed ? 'completed' : '';
        li.innerHTML = `
            <span onclick="toggleTask(${index})" style="cursor: pointer; flex: 1;">${task.text}</span>
            <div class="task-actions">
                <button class="delete-btn" onclick="deleteTask(${index})">Delete</button>
            </div>
        `;
        taskList.appendChild(li);
    });
}

function startTimer() {
    if (timerInterval) return;
    
    isPaused = false;
    timerInterval = setInterval(() => {
        if (timeLeft > 0) {
            timeLeft--;
            updateTimerDisplay();
        } else {
            clearInterval(timerInterval);
            timerInterval = null;
            alert('Pomodoro completed! Take a break.');
            pomodoroCount++;
            totalFocusTime += 25;
            localStorage.setItem('pomodoroCount', pomodoroCount);
            localStorage.setItem('totalFocusTime', totalFocusTime);
            updateStats();
            resetTimer();
        }
    }, 1000);
}

function pauseTimer() {
    if (timerInterval) {
        clearInterval(timerInterval);
        timerInterval = null;
        isPaused = true;
    }
}

function resetTimer() {
    clearInterval(timerInterval);
    timerInterval = null;
    timeLeft = 25 * 60;
    isPaused = false;
    updateTimerDisplay();
}

function updateTimerDisplay() {
    const minutes = Math.floor(timeLeft / 60);
    const seconds = timeLeft % 60;
    document.getElementById('timerDisplay').textContent = 
        `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;
}

function saveNotes() {
    const notes = document.getElementById('notes').value;
    localStorage.setItem('notes', notes);
    alert('Notes saved successfully!');
}

function loadNotes() {
    const savedNotes = localStorage.getItem('notes');
    if (savedNotes) {
        document.getElementById('notes').value = savedNotes;
    }
}

function updateStats() {
    document.getElementById('completedTasks').textContent = completedTasksCount;
    document.getElementById('pomodoroCount').textContent = pomodoroCount;
    document.getElementById('focusTime').textContent = totalFocusTime + ' min';
}

document.getElementById('taskInput').addEventListener('keypress', function(e) {
    if (e.key === 'Enter') {
        addTask();
    }
});

updateDateTime();
setInterval(updateDateTime, 60000);
renderTasks();
loadNotes();
updateStats();
