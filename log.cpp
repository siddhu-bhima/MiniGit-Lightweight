#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include "utils.hpp"

/**
 */
void log(void)
{
    ifstream headFile(".mini-git/HEAD");
    if (!headFile)
    {
        cerr << "fatal: HEAD not found.\n";
        return;
    }

    string headContent;
    getline(headFile, headContent);

    string commitHash;

    if (headContent.rfind("ref: ", 0) == 0)
    {
        string refPath = ".mini-git/" + headContent.substr(5);
        commitHash = trim(readFile(refPath));
    }
    else
    {
        commitHash = trim(headContent);
    }
    if (commitHash.empty())
    {
        cerr << "fatal: no commits yet.\n";
        return;
    }

    while (!commitHash.empty())
    {
        string commitPath = ".mini-git/objects/" + commitHash;
        string content = readFile(commitPath);
        if (content.empty())
        {
            cerr << "fatal: commit object not found: " << commitHash << "\n";
            break;
        }

        string author, date, message, parent;
        istringstream iss(content);
        string line;
        while (getline(iss, line))
        {
            if (line.find("author ") == 0)
            {
                author = line.substr(7);
            }
            else if (line.find("date ") == 0)
            {
                date = line.substr(5);
            }
            else if (line.find("message ") == 0)
            {
                message = line.substr(8);
            }
            else if (line.find("parent ") == 0)
            {
                parent = line.substr(7);
            }
        }

        cout << "commit " << commitHash << "\n";
        cout << "Author: " << author << "\n";
        cout << "Date:   " << date << "\n\n";
        cout << "    " << message << "\n\n";

        commitHash = parent;
    }
}
