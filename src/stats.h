#pragma once

#ifndef STAT_H
#define STAT_H

#include <iostream>

using namespace std;

struct Stats
{
  int numErrors;
  double accuracy;
  double WPM;
  double timeTaken;
  int attritionScore;

  void setNumErrors(int errors)
  {
    if (errors < 0) {numErrors = 0;}
    else {numErrors = errors;}
  }
  void setAccuracy(double Accuracy) {
    if (Accuracy < 0) {accuracy = 0;}
    else {accuracy = Accuracy;}
  }
  void setWPM(double wordsPerMin) {
    if (wordsPerMin < 0) {WPM = 0;}
    else {WPM = wordsPerMin;}
  }
  void setTimeTaken(double time) {
    if (time < 0) {timeTaken = 0;}
    else {timeTaken = time;}
  }
  void setAttritionScore(int score) {
    if (score < 0) {attritionScore = 0;}
    else {attritionScore = score;}
  }

  Stats() : numErrors(0), accuracy(0), WPM(0), timeTaken(0), attritionScore(0) {}
};

ostream& operator << (ostream& out, const Stats& print);


#endif

