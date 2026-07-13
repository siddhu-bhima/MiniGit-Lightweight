#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <map>
#include <chrono>
#include <iomanip>
#include "utils.hpp"

namespace fs = std::filesystem;
using namespace std;

/**
 */
void commit(const string &message)
{
    string cont = get_current_commit();
    cont = get_current_commit();
    string treeContent = generate_tree(cont);
    string treeHash = compute_hash(treeContent);

    ofstream treeFile(".mini-git/objects/" + treeHash);
    treeFile << treeContent;

    string parent = get_current_commit();
    string timestamp = get_timestamp();

    stringstream commitContent;
    commitContent << "tree " << treeHash << "\n";
    if (!parent.empty())
    {
        commitContent << "parent " << parent << "\n";
    }
    commitContent << "author " << get_author_data() << "\n";
    commitContent << "date " << timestamp << "\n";
    commitContent << "message " << message << "\n";

    string commitStr = commitContent.str();
    string commitHash = compute_hash(commitStr);

    ofstream commitFile(".mini-git/objects/" + commitHash);
    commitFile << commitStr;

    update_current_branch(commitHash);

    ofstream clearIndex(".mini-git/index");
    clearIndex.close();

    cout << "Committed as " << commitHash << "\n";
}
