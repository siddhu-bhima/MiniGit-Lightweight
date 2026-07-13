#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "utils.hpp"

using namespace std;
namespace fs = filesystem;

static string getCurrentBranchName()
{
    ifstream headFile(".mini-git/HEAD");
    string headLine;
    getline(headFile, headLine);
    if (headLine.rfind("ref: ", 0) == 0)
    {
        string refPath = headLine.substr(5);
        size_t slash = refPath.find_last_of('/');
        if (slash != string::npos)
        {
            return refPath.substr(slash + 1);
        }
    }
    return "detached HEAD";
}

static set<string> getStagedFiles()
{
    set<string> stagedFiles;
    ifstream indexFile(".mini-git/index");
    string line;
    while (getline(indexFile, line))
    {
        istringstream iss(line);
        string filename, hash;
        iss >> filename >> hash;
        if (!filename.empty())
        {
            stagedFiles.insert(filename);
        }
    }
    return stagedFiles;
}

static set<string> getWorkingFiles()
{
    set<string> files;
    for (fs::recursive_directory_iterator it("."), end; it != end; ++it)
    {
        if (it->path().filename() == ".mini-git")
        {
            if (it->is_directory())
            {
                it.disable_recursion_pending();
            }
            continue;
        }

        const fs::path relativePath = it->path().lexically_relative(".");
        if (relativePath.empty())
        {
            continue;
        }

        if (relativePath.string().rfind(".mini-git", 0) == 0)
        {
            if (it->is_directory())
            {
                it.disable_recursion_pending();
            }
            continue;
        }

        if (it->is_regular_file())
        {
            files.insert(relativePath.generic_string());
        }
    }
    return files;
}

void status(void)
{
    if (!fs::exists(".mini-git"))
    {
        cerr << "fatal: not a mini-git repository (or any of the parent directories).\n";
        return;
    }

    string branchName = getCurrentBranchName();
    if (branchName == "detached HEAD")
    {
        cout << "Detached HEAD\n\n";
    }
    else
    {
        cout << "On branch " << branchName << "\n\n";
    }

    map<string, string> trackedFiles = getCurrentTrackedFiles();
    set<string> stagedFiles = getStagedFiles();
    set<string> workingFiles = getWorkingFiles();

    vector<string> staged;
    vector<string> modified;
    vector<string> deleted;
    vector<string> untracked;

    for (const auto &file : stagedFiles)
    {
        staged.push_back(file);
    }

    for (const auto &[filename, blobHash] : trackedFiles)
    {
        bool exists = fs::exists(filename);
        bool stagedNow = stagedFiles.count(filename) > 0;
        if (!exists)
        {
            if (!stagedNow)
            {
                deleted.push_back(filename);
            }
            continue;
        }

        string currentContent = readFile(filename);
        string committedContent = readFile(".mini-git/objects/" + blobHash);
        if (currentContent != committedContent && !stagedNow)
        {
            modified.push_back(filename);
        }
    }

    for (const auto &filename : workingFiles)
    {
        if (trackedFiles.count(filename) == 0 && stagedFiles.count(filename) == 0)
        {
            untracked.push_back(filename);
        }
    }

    if (staged.empty() && modified.empty() && deleted.empty() && untracked.empty())
    {
        cout << "nothing to commit, working tree clean\n";
        return;
    }

    if (!staged.empty())
    {
        cout << "Changes staged for commit:\n";
        for (const auto &file : staged)
        {
            cout << "  new file: " << file << "\n";
        }
        cout << "\n";
    }

    if (!modified.empty() || !deleted.empty())
    {
        cout << "Changes not staged for commit:\n";
        for (const auto &file : modified)
        {
            cout << "  modified: " << file << "\n";
        }
        for (const auto &file : deleted)
        {
            cout << "  deleted:  " << file << "\n";
        }
        cout << "\n";
    }

    if (!untracked.empty())
    {
        cout << "Untracked files:\n";
        for (const auto &file : untracked)
        {
            cout << "  " << file << "\n";
        }
    }
}
