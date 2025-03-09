#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include "TextDisplay.h"
#include "words.h"

using namespace std;
using namespace std::chrono;

class Benchmark {
  private:
    string passage;
    string userInput;
    double time;
    int wordCount;
    int errors;

  public:
    Benchmark() : passage(""), userInput(""), time (0.0), wordCount(0), errors(0) {}
    void BenchmarkStart();
    double getTime() {return time;}
    double calcWPM();
    double calcAccuracy();
    void addErrors();
    int getErrors() {return errors;}
};


#endif