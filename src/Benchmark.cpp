#include "Benchmark.h"

using namespace std;
using namespace std::chrono;

void Benchmark::BenchmarkStart() {
    TextDisplay bench;
    
    time = bench.timedDisplay(userInput, passage, wordCount);
    time -= 0.5;
}

double Benchmark::calcWPM() {
    stringstream  stream(userInput);
    string oneWord;
    unsigned int count = 0;
    while(stream >> oneWord) { ++count;}

    double WPM = static_cast<double>(count) / (time / 60.0);
    return WPM;
}

double Benchmark::calcAccuracy() {
    addErrors();
    double accuracy = static_cast<double>((passage.size() - errors)) / passage.size()  * 100;
    if (accuracy < 0.0) accuracy = 0.0;
    return accuracy;
}

void Benchmark::addErrors() {
    errors = 0;
    int newLineCounter = 0;
        
    for (auto i(userInput.begin() ); i != userInput.end(); ++i){ // reads and compares the system prompt vs the user string
        if (*(passage.begin() + distance(userInput.begin() , i) + newLineCounter) == '\n')
        {
            newLineCounter++;
        }
        if (*i != *(passage.begin() + distance(userInput.begin() , i) + newLineCounter)){ // if the current char (i) is not equal to the userString at i (beginning of userString (0) + distance of i)
            ++errors;
        }
    }

    if((userInput.size() + newLineCounter) < passage.size())
    {
        errors += (passage.size() - (userInput.size() + newLineCounter));
    }

}
