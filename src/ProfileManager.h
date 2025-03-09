#pragma once

#include "ProfileUpdater.h"
#include <string>
#include <map>
#include <vector>
#include "stats.h"

using namespace std;

class ProfileManager {

    private:

        ProfileUpdater* fileHold;
        //this username clarifies what we'll be reading and writing to.
        string username;
        void createUsernamesFile();
        bool search(const string&);

        void createUserProfile(const string&);
        void replace_first(string& s, string& toReplace, string& replaceWith);
    
    public:

        ProfileManager(ProfileUpdater& update) : username(""){ fileHold = &update; }

        string getUsername() {return username;}
        string getUserFileName(string uName) {return "../data/" + uName + ".txt";}

        void chooseProfile();
        void createProfile();
        void printNames();
        void switchUsername(string& newUsername);
        void deleteProfile(string&);
        void writeStat(Stats& statToWrite, int testCount) {
            fileHold->setStats(statToWrite.WPM, statToWrite.accuracy, statToWrite.timeTaken,
                              statToWrite.numErrors, statToWrite.attritionScore, testCount);
        }
        void readProf() { fileHold->outputProfile(); }

};