@echo off
REM Automated GitHub Setup Script
REM Run this after you know your GitHub username

echo ================================================
echo    GitHub Repository Setup - Automated
echo ================================================
echo.

REM Get username from user
set /p GITHUB_USERNAME="Enter your GitHub username: "

echo.
echo Setting up repository for: %GITHUB_USERNAME%
echo.

REM Step 1: Add all files
echo [Step 1/5] Adding files to git...
git add .

REM Step 2: Commit
echo.
echo [Step 2/5] Creating commit...
git commit -m "Initial commit: Productivity Dashboard - T1 & T2 Implementation

- Implemented T1: Menu Interface with SFML navigation
- Implemented T2: Habit Logging Input functionality  
- Added web-based preview for demonstration
- Included console version (no SFML dependency)
- Added comprehensive documentation and build guides"

REM Step 3: Set remote
echo.
echo [Step 3/5] Connecting to GitHub repository...
git remote add origin https://github.com/%GITHUB_USERNAME%/ProductivityDashboard.git

REM Step 4: Set branch name
echo.
echo [Step 4/5] Setting branch to main...
git branch -M main

REM Step 5: Push
echo.
echo [Step 5/5] Uploading to GitHub...
echo.
echo IMPORTANT: You will need to authenticate!
echo - Username: %GITHUB_USERNAME%
echo - Password: Use a Personal Access Token (NOT your password)
echo.
echo To create a token:
echo 1. Go to: https://github.com/settings/tokens
echo 2. Click "Generate new token (classic)"
echo 3. Check "repo" scope
echo 4. Copy the token and paste it when prompted
echo.
pause

git push -u origin main

echo.
echo ================================================
echo           Upload Complete!
echo ================================================
echo.
echo Your repository is now available at:
echo https://github.com/%GITHUB_USERNAME%/ProductivityDashboard
echo.
echo To enable GitHub Pages (optional):
echo 1. Go to repository Settings
echo 2. Click Pages in sidebar
echo 3. Set Source to: main branch, / (root)
echo 4. Save
echo.
echo Your web preview will be at:
echo https://%GITHUB_USERNAME%.github.io/ProductivityDashboard/dashboard-preview.html
echo.
pause
