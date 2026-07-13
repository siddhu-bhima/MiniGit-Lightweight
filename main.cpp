#include <iostream>
#include <string>
#include <vector>
#include "commands.hpp"

/**
 * MiniGit Lightweight command line entry point.
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "MiniGit Lightweight\n\nCommands:\ninit\nadd\nstatus\ncommit\nlog\ncheckout\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "init")
    {
        initialize_repo();
    }
    else if (command == "add")
    {
        if (argc < 3)
        {
            std::cerr << "Usage: mini-git add <filename>\n";
            return 1;
        }
        add_file(argv[2]);
    }
    else if (command == "commit")
    {
        if (argc < 4 || std::string(argv[2]) != "-m")
        {
            std::cerr << "Usage: mini-git commit -m \"<message>\"\n";
            return 1;
        }
        commit(argv[3]);
    }
    else if (command == "log")
    {
        log();
    }
    else if (command == "checkout")
    {
        if (argc < 3)
        {
            std::cerr << "Usage: mini-git checkout <branch-name || commitID>\n";
            return 1;
        }

        bool force = false;
        if (argc >= 4)
        {
            if (std::string(argv[3]) == "--force" || std::string(argv[3]) == "-f")
            {
                force = true;
            }
            else
            {
                std::cerr << "Usage: mini-git checkout <branch-name || commitID> [--force]\n";
                return 1;
            }
        }

        checkout(argv[2], force);
    }
    else if (command == "status")
    {
        status();
    }
    else
    {
        std::cerr << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
}
