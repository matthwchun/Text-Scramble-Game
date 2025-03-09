#ifndef ATTRITION_H
#define ATTRITION_H

#include <vector>
#include <string>
#include "TextDisplay.h"
#include "words.h"

using namespace std;

class Attrition {
  private:
    int score;
    vector<string> wordList;
    vector<string> userInput;
    int maxScore;
    double time;

  public:
    Attrition() : score(0), wordList({}), userInput({}), maxScore (0), time (0.0) {}
    void AttritionStart();
    void setMaxScore(int max) {maxScore = max;}
    int getScore() {return score;}
    int getMaxScore() {return maxScore;}
    double getTime() {return time;}
    double calcWPM();
    double calcAccuracy();
    int calcErrors();


};

#endif