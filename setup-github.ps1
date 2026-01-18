# Automated GitHub Setup Script
# PowerShell version for Windows

Write-Host "================================================" -ForegroundColor Cyan
Write-Host "   GitHub Repository Setup - Automated" -ForegroundColor Cyan
Write-Host "================================================`n" -ForegroundColor Cyan

# Get GitHub username
$GITHUB_USERNAME = Read-Host "Enter your GitHub username"

Write-Host "`nSetting up repository for: $GITHUB_USERNAME`n" -ForegroundColor Green

# Step 1: Add all files
Write-Host "[Step 1/5] Adding files to git..." -ForegroundColor Yellow
git add .

# Step 2: Commit
Write-Host "`n[Step 2/5] Creating commit..." -ForegroundColor Yellow
git commit -m "Initial commit: Productivity Dashboard - T1 & T2 Implementation

- Implemented T1: Menu Interface with SFML navigation
- Implemented T2: Habit Logging Input functionality  
- Added web-based preview for demonstration
- Included console version (no SFML dependency)
- Added comprehensive documentation and build guides"

# Step 3: Set remote (remove if exists)
Write-Host "`n[Step 3/5] Connecting to GitHub repository..." -ForegroundColor Yellow
git remote remove origin 2>$null
git remote add origin "https://github.com/$GITHUB_USERNAME/ProductivityDashboard.git"

# Step 4: Set branch name
Write-Host "`n[Step 4/5] Setting branch to main..." -ForegroundColor Yellow
git branch -M main

# Step 5: Push
Write-Host "`n[Step 5/5] Preparing to upload to GitHub...`n" -ForegroundColor Yellow

Write-Host "================================================" -ForegroundColor Red
Write-Host "IMPORTANT: Authentication Required!" -ForegroundColor Red
Write-Host "================================================" -ForegroundColor Red
Write-Host "Username: $GITHUB_USERNAME" -ForegroundColor White
Write-Host "Password: Use a Personal Access Token (NOT your GitHub password)`n" -ForegroundColor White

Write-Host "To create a Personal Access Token:" -ForegroundColor Cyan
Write-Host "1. Opening token creation page..." -ForegroundColor White
Start-Process "https://github.com/settings/tokens/new"
Write-Host "2. Give it a name: 'ProductivityDashboard'" -ForegroundColor White
Write-Host "3. Select scope: 'repo' (full control)" -ForegroundColor White
Write-Host "4. Click 'Generate token'" -ForegroundColor White
Write-Host "5. COPY the token (you won't see it again!)" -ForegroundColor White
Write-Host "6. Paste it when git asks for password`n" -ForegroundColor White

Read-Host "Press Enter when you have your token ready"

Write-Host "`nUploading to GitHub..." -ForegroundColor Yellow
git push -u origin main

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n================================================" -ForegroundColor Green
    Write-Host "           Upload Complete!" -ForegroundColor Green
    Write-Host "================================================`n" -ForegroundColor Green

    Write-Host "Your repository is now available at:" -ForegroundColor Cyan
    Write-Host "https://github.com/$GITHUB_USERNAME/ProductivityDashboard`n" -ForegroundColor White

    Write-Host "To enable GitHub Pages (optional):" -ForegroundColor Cyan
    Write-Host "1. Go to repository Settings" -ForegroundColor White
    Write-Host "2. Click 'Pages' in sidebar" -ForegroundColor White
    Write-Host "3. Set Source to: main branch, / (root)" -ForegroundColor White
    Write-Host "4. Click Save`n" -ForegroundColor White

    Write-Host "Your web preview will be at:" -ForegroundColor Cyan
    Write-Host "https://$GITHUB_USERNAME.github.io/ProductivityDashboard/dashboard-preview.html`n" -ForegroundColor White

    # Open repository in browser
    $openRepo = Read-Host "Open repository in browser now? (y/n)"
    if ($openRepo -eq 'y') {
        Start-Process "https://github.com/$GITHUB_USERNAME/ProductivityDashboard"
    }
} else {
    Write-Host "`n================================================" -ForegroundColor Red
    Write-Host "           Upload Failed!" -ForegroundColor Red
    Write-Host "================================================`n" -ForegroundColor Red
    Write-Host "Common issues:" -ForegroundColor Yellow
    Write-Host "1. Repository doesn't exist on GitHub yet" -ForegroundColor White
    Write-Host "   Solution: Create it at https://github.com/new" -ForegroundColor Cyan
    Write-Host "2. Wrong username" -ForegroundColor White
    Write-Host "   Solution: Re-run script with correct username" -ForegroundColor Cyan
    Write-Host "3. Authentication failed" -ForegroundColor White
    Write-Host "   Solution: Use Personal Access Token, not password`n" -ForegroundColor Cyan
}

Read-Host "`nPress Enter to exit"
