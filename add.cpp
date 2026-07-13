#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "utils.hpp"

using namespace std;
namespace fs = std::filesystem;

void add_file(string path_to_file)
{
    fs::path git_dir = ".mini-git";

    if (!fs::exists(git_dir))
    {
        cout << "No repository found in this directory. Use .mini-git init to initialize one.\n";
        return;
    }
    if (!fs::exists(path_to_file))
    {
        cout << "Error! File not found.";
        return;
    }
    bool wasModified = check_mod(path_to_file);
    if (!wasModified)
    {
        cout << "File is not modified. No need to add it again.\n";
        return;
    }
    string hash = save_object(path_to_file);

    vector<pair<string, string>> entries;
    ifstream indexIn(".mini-git/index");
    string line;
    while (getline(indexIn, line))
    {
        istringstream iss(line);
        string filename, existingHash;
        iss >> filename >> existingHash;
        if (!filename.empty() && filename != path_to_file)
        {
            entries.push_back({filename, existingHash});
        }
    }

    ofstream indexFile(".mini-git/index", ios::trunc);
    if (!indexFile)
    {
        cerr << "Error: Could not update index.\n";
        return;
    }

    for (const auto &entry : entries)
    {
        indexFile << entry.first << " " << entry.second << "\n";
    }
    indexFile << path_to_file << " " << hash << "\n";
}