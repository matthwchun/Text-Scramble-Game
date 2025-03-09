#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <string>
#include <vector>
#include <thread>
#include <stdio.h>
#include <pthread.h>
#include <sstream>
#include <iostream>
#include "words.h"
#include <chrono>


class TextDisplay {
    private:
        void wordOptions(char& difficulty, std::string& theme);
        void passageSelect(std::string& passage, int& count);
        void wordListSelect(std::vector<std::string>& wordList);
    public:
        double timedDisplay(std::string& userInput, std::string& passage, int& count);
        double lifeDisplay(std::vector<std::string>& userInput, int& score, std::vector<std::string>& wordList);
};

#endif

