# GitHub Upload Guide

## Quick Steps to Upload to GitHub

### Step 1: Create a GitHub Repository

1. Go to https://github.com
2. Click the "+" icon in top right → "New repository"
3. Repository name: `ProductivityDashboard` (or your preferred name)
4. Description: "Personal Productivity Dashboard with C++ SFML and Web versions"
5. Choose Public or Private
6. **DO NOT** initialize with README (we already have files)
7. Click "Create repository"

### Step 2: Connect Local Repository to GitHub

After creating the repo, GitHub will show you commands. Use these:

```powershell
# Set your remote repository (replace YOUR_USERNAME and REPO_NAME)
git remote add origin https://github.com/YOUR_USERNAME/ProductivityDashboard.git

# Verify remote is set
git remote -v
```

### Step 3: Add All Files

```powershell
# Add all files to staging
git add .

# Check what will be committed
git status
```

### Step 4: Commit Your Changes

```powershell
# Commit with a descriptive message
git commit -m "Initial commit: Productivity Dashboard with T1 & T2 implementation

- Added SFML C++ dashboard with menu navigation (T1)
- Implemented habit logging input feature (T2)
- Created web-based preview for demo
- Included console version without SFML dependency
- Added comprehensive documentation"
```

### Step 5: Push to GitHub

```powershell
# Push to GitHub (first time)
git push -u origin master

# If prompted for credentials, use GitHub Personal Access Token
# (NOT your password - GitHub deprecated password authentication)
```

## Alternative: Using GitHub Desktop (Easier for Beginners)

1. Download GitHub Desktop: https://desktop.github.com/
2. Install and sign in with your GitHub account
3. Click "Add" → "Add Existing Repository"
4. Choose your folder: `C:\Users\jayso\OneDrive\Desktop\ProductivityDashboard`
5. Click "Publish repository" button
6. Choose name, description, and public/private
7. Click "Publish repository"

Done! Your code is now on GitHub.

## What Gets Uploaded

Your repository will include:

```
ProductivityDashboard/
├── cpp-dashboard/              # C++ SFML implementation
│   ├── main_dashboard.cpp     # T1 & T2 main app
│   ├── main.cpp               # Full featured version
│   ├── main_console.cpp       # Console version
│   ├── Button.hpp             # UI components
│   ├── Screen.hpp
│   ├── ScreenManager.hpp
│   ├── MenuScreen.hpp         # T1 implementation
│   ├── DashboardScreen.hpp    # T2 implementation
│   ├── ChartsScreen.hpp
│   ├── GamifiedScreen.hpp
│   ├── SettingsScreen.hpp
│   ├── CMakeLists.txt         # Build configuration
│   ├── README_T1_T2.md        # Documentation
│   ├── BUILD_CONSOLE.md
│   ├── README.md
│   └── assets/
├── index.html                  # Original web dashboard
├── script.js
├── style.css
├── dashboard-preview.html      # T1 & T2 web preview
├── dashboard-preview.css
├── dashboard-preview.js
└── README.md                   # Main project README
```

## Creating a Personal Access Token (if needed)

If git asks for password:

1. Go to GitHub → Settings → Developer settings → Personal access tokens → Tokens (classic)
2. Click "Generate new token (classic)"
3. Name it: "ProductivityDashboard"
4. Select scopes: `repo` (full control of private repositories)
5. Click "Generate token"
6. **COPY THE TOKEN** (you won't see it again!)
7. Use this token instead of your password when pushing

## Viewing Your Repository

After pushing, visit:
```
https://github.com/YOUR_USERNAME/ProductivityDashboard
```

## GitHub Pages (Optional - Host Web Preview Online)

To make your web preview accessible online:

1. Go to your repository on GitHub
2. Settings → Pages
3. Source: Deploy from a branch
4. Branch: master, folder: / (root)
5. Click Save
6. Your site will be at: `https://YOUR_USERNAME.github.io/ProductivityDashboard/dashboard-preview.html`

## Common Issues

### "Permission denied"
- Use Personal Access Token instead of password
- Or set up SSH keys

### "Already exists"
- Remote already set: `git remote remove origin` then add again

### "Branch not found"
- Your default branch might be 'main' instead of 'master'
- Use: `git push -u origin main`

## Next Steps After Upload

1. Add a nice README.md to describe your project
2. Add screenshots/GIFs of the app
3. Tag releases when you complete features
4. Share the repository link!
