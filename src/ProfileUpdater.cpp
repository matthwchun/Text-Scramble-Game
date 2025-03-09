#include "ProfileUpdater.h"
#include <string>
#include <fstream>
#include <iostream>

bool ProfileUpdater::readProfile() {
    
    if (!fileCheck())
    {
        cout << "Data file not created yet!" << endl;
        return false;
    }

    ifstream profileData(fileToOpen.c_str());

    profileData >> WPM;
    profileData >> accuracy;
    profileData >> time;
    profileData >> errors;
    profileData >> attScore;
    profileData >> testCount;

    profileData.close();

    return true;
}

void ProfileUpdater::writeStats() {

    ofstream writeNewTotals(fileToOpen.c_str());

    writeNewTotals << WPM << endl;
    writeNewTotals << accuracy << endl;
    writeNewTotals << time << endl;
    writeNewTotals << errors << endl;
    writeNewTotals << attScore << endl;
    writeNewTotals << testCount << endl;

    writeNewTotals.close();

}

void ProfileUpdater::switchProfile(string& newProfile){
    selectedProfile = newProfile;
    fileToOpen = "../data/" + selectedProfile + ".txt";
}

bool ProfileUpdater::fileCheck()
{
    struct stat check;
    bool exist = (stat(fileToOpen.c_str(), &check) == 0); // .c_str converts string to char array and stat will return 0 if no error occurs (i.e. file exists and can be accessed)
    return exist;
}

void ProfileUpdater::setStats(double newWPM, double newAccuracy, double newTime, int newErrors, int newScore, int newTestCount) {

    WPM = newWPM;
    accuracy = newAccuracy;
    time = newTime;
    errors = newErrors;
    attScore = newScore;
    testCount = newTestCount;

    writeStats();

}

void ProfileUpdater::outputProfile() {
    if(readProfile()) {
    cout << "Time taken for test: " << time << endl;
    cout << "Accuracy: " << accuracy << endl;
    cout << "WPM: " << WPM << endl;
    cout << "Number of errors: " << errors << endl;
    cout << "Attrition score: " << attScore << endl;
    cout << "Total number of tests taken: " << testCount << endl;
    }
}