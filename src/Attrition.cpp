#include "Attrition.h"
#include <iostream>
#include <fstream>

using namespace std;

void Attrition::AttritionStart() {
    cout << "Starting Attrition Test..." << endl << endl;

    TextDisplay attri;
    
    time = attri.lifeDisplay(userInput, score, wordList);
    time -= (userInput.size() * 0.5);

    if (score > maxScore) {
        setMaxScore(score);
    }
}

double Attrition::calcWPM() {
    double WPM = static_cast<double>(userInput.size()) / (time / 60.0) ;
    return WPM;
}

double Attrition::calcAccuracy() {
    int number = userInput.size();
    int charCount = 0;
    int errors = 0;
    for (int i = 0; i < number; ++i){
        for (auto j(userInput.at(i).begin() ); j != userInput.at(i).end(); ++j){ // reads and compares the system prompt vs the user string
            if (*j != *(wordList.at(i).begin() + distance(userInput.at(i).begin() , j))){ // if the current char (i) is not equal to the userString at i (beginning of userString (0) + distance of i)
                ++errors;
            } 
        }

        if (userInput.at(i).size() < wordList.at(i).size())
        {
            errors +=  (wordList.at(i).size() - userInput.at(i).size());
        }

        charCount += wordList.at(i).size();
    }

    double accuracy = static_cast<double>(charCount - errors) / charCount  * 100;
    if (accuracy < 0.0) accuracy = 0.0;
    return accuracy;
}

int Attrition::calcErrors() {
    int number = userInput.size();
    int errors = 0;
    for (int i = 0; i < number; ++i){
        for (auto j(userInput.at(i).begin() ); j != userInput.at(i).end(); ++j){ // reads and compares the system prompt vs the user string
            if (*j != *(wordList.at(i).begin() + distance(userInput.at(i).begin() , j))){ // if the current char (i) is not equal to the userString at i (beginning of userString (0) + distance of i)
                ++errors;
            } 
        }

        if (userInput.at(i).size() < wordList.at(i).size())
        {
            errors +=  (wordList.at(i).size() - userInput.at(i).size());
        }
    }

    return errors;
}