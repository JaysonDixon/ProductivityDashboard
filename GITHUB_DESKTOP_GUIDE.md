# GitHub Desktop Upload Guide - Step by Step

## 📥 Step 1: Install GitHub Desktop

The download page has been opened in your browser.

1. Download GitHub Desktop from: https://desktop.github.com/
2. Run the installer (GitHubDesktopSetup-x64.exe)
3. Follow the installation wizard
4. Launch GitHub Desktop when installation completes

## 🔐 Step 2: Sign In to GitHub

1. **If you DON'T have a GitHub account yet:**
   - Click "Create your free account"
   - Go to https://github.com/signup
   - Enter your email, password, and username
   - Verify your email address
   - Return to GitHub Desktop and sign in

2. **If you already have a GitHub account:**
   - Click "Sign in to GitHub.com"
   - Enter your username/email and password
   - Complete 2FA if enabled
   - Click "Authorize desktop"

## 📂 Step 3: Add Your Project to GitHub Desktop

Once you're signed in:

1. Click **"File"** → **"Add local repository"**
   
2. Click **"Choose..."** and navigate to:
   ```
   C:\Users\jayso\OneDrive\Desktop\ProductivityDashboard
   ```

3. Click **"Add repository"**

GitHub Desktop will now show all your files ready to commit!

## ✅ Step 4: Make Your First Commit

You should see a list of changed files on the left side:

1. **Review the files:**
   - ✓ cpp-dashboard/ (all C++ files)
   - ✓ dashboard-preview.html, .css, .js
   - ✓ index.html, script.js, style.css
   - ✓ README.md
   - ✓ GITHUB_UPLOAD_GUIDE.md
   - ✓ .gitignore

2. **All files should be checked** (leave them all selected)

3. **Write a commit message** in the bottom-left:
   ```
   Initial commit: Productivity Dashboard

   - Implemented T1: Menu Interface with SFML navigation
   - Implemented T2: Habit Logging Input functionality
   - Added web-based preview for demo
   - Included console version (no SFML required)
   - Comprehensive documentation and build guides
   ```

4. Click the blue **"Commit to master"** button

## 🚀 Step 5: Publish to GitHub

After committing:

1. Click the **"Publish repository"** button at the top

2. A dialog will appear:
   - **Name:** ProductivityDashboard (you can change this)
   - **Description:** Personal Productivity Dashboard with C++ SFML and Web versions
   - **Keep this code private:** ☐ (uncheck for public, check for private)
   - **Organization:** None (unless you're part of one)

3. Click **"Publish repository"**

4. Wait for upload to complete (you'll see a progress bar)

## 🎉 Step 6: View Your Repository

Once published:

1. In GitHub Desktop, click **"Repository"** → **"View on GitHub"**
   
   OR

2. Go to: `https://github.com/YOUR_USERNAME/ProductivityDashboard`

Your code is now on GitHub! 🎊

## 📝 Future Updates

When you make changes to your code:

1. Open GitHub Desktop
2. It will automatically detect changed files
3. Review the changes in the "Changes" tab
4. Write a commit message (e.g., "Added chart rendering feature")
5. Click "Commit to master"
6. Click "Push origin" to upload to GitHub

## 🌐 Optional: Enable GitHub Pages (Host Web Preview Online)

To make your web preview accessible online:

1. Go to your repository on GitHub
2. Click **"Settings"** (top right)
3. Scroll to **"Pages"** in left sidebar
4. Under **"Source"**, select:
   - Branch: **master**
   - Folder: **/ (root)**
5. Click **"Save"**
6. Wait 1-2 minutes
7. Your site will be live at:
   ```
   https://YOUR_USERNAME.github.io/ProductivityDashboard/dashboard-preview.html
   ```

## 🎯 Quick Reference

| Action | Steps |
|--------|-------|
| **Add files** | They appear automatically in "Changes" tab |
| **Commit** | Write message → Click "Commit to master" |
| **Upload** | Click "Push origin" (or "Publish" for first time) |
| **View online** | Repository → View on GitHub |
| **Undo commit** | Repository → History → Right-click → Revert |

## ⚠️ Common Issues

### "Repository not found"
- Make sure you're in the correct folder
- Check that `.git` folder exists in ProductivityDashboard

### "Authentication failed"
- Sign out and sign back in
- Go to File → Options → Sign out
- Then sign in again

### "Cannot push"
- Click "Fetch origin" first
- Then try "Push origin" again

### "Merge conflicts"
- This happens if you edited on GitHub and locally
- GitHub Desktop will show conflict resolution options

## 📚 What You're Uploading

Your repository will include:

✅ Complete C++ SFML implementation (T1 & T2)
✅ Web-based preview (works in any browser)
✅ Console version (no graphics needed)
✅ Comprehensive documentation
✅ Build instructions for Windows/Linux/Mac
✅ CMake configuration files
✅ Professional README with badges

## 🔗 Useful Links

- GitHub Desktop Help: https://docs.github.com/en/desktop
- Your Repositories: https://github.com/YOUR_USERNAME?tab=repositories
- GitHub Learning Lab: https://lab.github.com/

---

**Next Steps:**
1. ✅ Install GitHub Desktop
2. ✅ Sign in to GitHub
3. ✅ Add your repository
4. ✅ Commit your files
5. ✅ Publish to GitHub
6. 🎉 Share your repository link!

Need help? The download page is now open in your browser. Just follow the installation wizard!
