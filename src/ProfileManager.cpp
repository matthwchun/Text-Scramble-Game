#include "ProfileManager.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

void ProfileManager::chooseProfile() {

    ifstream readUserFile;
    string readName;

    readUserFile.open("../data/usernamesFile.txt");

    if (readUserFile.fail()) {

        createUsernamesFile();
    }

    cout << "Select a username from the following list: " << endl;
    printNames();

    string userSelectInput;

    getline(cin, userSelectInput);

    bool userFound = search(userSelectInput);

    while (!userFound) {

        cout << "That profile does not exist, please try again." << endl;

        getline(cin, userSelectInput);

        userFound = search(userSelectInput);

    }

    username = userSelectInput;
    fileHold->switchProfile(username);

    readUserFile.close();
    
}

bool ProfileManager::search(const string& userSelectInput) {

    ifstream compareUserFile("../data/usernamesFile.txt");

    if (compareUserFile.fail()) {

        throw std::runtime_error("There was an error reading the file.");

    }

    string readName;

    while (getline(compareUserFile, readName)) {

        if (userSelectInput == readName) {return true;}

    }
    
    compareUserFile.close();
    //this assumes that the usernames didn't match
    return false;

}

void ProfileManager::createProfile() {

    string newName;
    cout << "Please enter your new username: " << endl;
    
    getline(cin, newName);

    ofstream inUsernamesFile("../data/usernamesFile.txt", fstream::app);

    if (inUsernamesFile.fail()) {

        throw std::runtime_error("There was an error reading the file.");

    }

    inUsernamesFile << newName << endl;
    inUsernamesFile.close();

    createUserProfile(newName);

}

void ProfileManager::createUserProfile(const string& newName) {

    string newUserFileName = getUserFileName(newName);

    ofstream newFile(newUserFileName);

    for(unsigned i = 0; i < 6; ++i) {

        newFile << 0 << endl;

    }

    newFile.close();

}

void ProfileManager::printNames() {

    ifstream printUsernames("../data/usernamesFile.txt");

    if (printUsernames.fail()) {

        throw std::runtime_error("There was an error reading the file.");

    }

    string nameToPrint;
    cout << "Profiles:";
    while (getline(printUsernames, nameToPrint)) {

        cout <<  nameToPrint << endl;

    }

    printUsernames.close();

}

void ProfileManager::createUsernamesFile () {

    string newUser;

    //file that holds usernames is created, 
    ofstream usernamesOut("../data/usernamesFile.txt");

    cout << "Enter your new Username: " << endl;
    getline(cin, newUser);
    //cin.ignore();

    usernamesOut << newUser << endl;

    createUserProfile(newUser);

    usernamesOut.close();

}

void ProfileManager::deleteProfile(string& userToDelete) {

    if (search(userToDelete)) {
    ifstream getUsernames("../data/usernamesFile.txt");
    string usernameList = "";
    string tempStore = "";

    while (getline(getUsernames, tempStore)) {
        if (tempStore != userToDelete)
        {
            usernameList += tempStore;
            usernameList += "\n";
        }
    }
    
    ofstream rewriteUsers("../data/usernamesFile.txt");
    rewriteUsers << usernameList;

    string toDeleteString = getUserFileName(userToDelete);

    remove(toDeleteString.c_str());
    }
    else
    {
        cout << "That user already doesn't exist." << endl;
        this_thread::sleep_for(milliseconds(500));
    }
}

void ProfileManager::switchUsername(string& newUsername) {
    //need to 1) set new username, 2) edit usernames file, 3) if data file already exists, rename it
    if (search(newUsername)) {
        cout << "Looks like that username is already taken! :(" << endl;
        this_thread::sleep_for(milliseconds(500));
        return;
    }
    if (fileHold->fileCheck())
    {
        string currFileName = getUserFileName(username);
        string newFileName = "../data/" + newUsername + ".txt";
        rename(currFileName.c_str(), newFileName.c_str());
    }

    ifstream getUsernames("../data/usernamesFile.txt");
    string usernameList((std::istreambuf_iterator<char>(getUsernames)), (std::istreambuf_iterator<char>()) );
    replace_first(usernameList, this->username, newUsername);
    ofstream rewriteUsers("../data/usernamesFile.txt");
    rewriteUsers << usernameList;

    username = newUsername;
    fileHold->switchProfile(newUsername);
}

void ProfileManager::replace_first(string& s, string& toReplace, string& replaceWith) {
    size_t pos = s.find(toReplace);
    if (pos == std::string::npos) return; //not found
    s.replace(pos, toReplace.length(), replaceWith);
}