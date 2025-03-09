#pragma once

#include <string>
#include <sys/stat.h>

using namespace std;

class ProfileUpdater {

    private :
        string selectedProfile;
        string fileToOpen;
        double WPM;
        double accuracy;
        double time;
        int errors;
        int attScore;
        int testCount;

        bool readProfile();
        void writeStats();

    public :

        ProfileUpdater() : selectedProfile(""), fileToOpen(""), 
                        WPM(0.0), accuracy(0.0), time(0.0), errors(0), attScore(0), testCount(0) {}

        void setStats(double, double, double, int, int, int);
        void outputProfile();
        void switchProfile(string& newProfile);
        bool fileCheck();
};