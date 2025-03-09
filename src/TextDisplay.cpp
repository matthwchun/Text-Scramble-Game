#include "TextDisplay.h"

using namespace std;
using namespace std::chrono;

milliseconds now_ms(){
    return duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    );
}

double TextDisplay::timedDisplay(string& userInput, string& passage, int& count) {
    this->passageSelect(passage, count);

    cout << "\x1b[H\x1b[2J";
    cout << "Press enter twice once done with passage!" << endl;
    cout << "Press enter between lines if necessary!" << endl << endl;
    cout << "\x1b[34m";
    cout << passage << endl << endl;
    cout << "\x1b[32m";
    userInput = "";
    string input = "";
    //int errors = 0;
    int newLineCounter = 0;

    cout << "\033[s";
    cin.ignore();
    auto start = high_resolution_clock::now();
    while (getline(cin,input) && !input.empty()) {
        userInput += input; 
    }
    auto end = high_resolution_clock::now();
        cout << "\033[u";

        for (auto i(userInput.begin() ); i != userInput.end(); ++i){ // reads and compares the system prompt vs the user string
            if (*(passage.begin() + distance(userInput.begin() , i) + newLineCounter) == '\n')
            {
                cout << "\n";
                newLineCounter++;
            }
            if (*i != *(passage.begin() + distance(userInput.begin() , i) + newLineCounter)){ // if the current char (i) is not equal to the userString at i (beginning of userString (0) + distance of i)
                //++errors;
                cout << "\x1b[31m";
            }
            else{
                cout << "\x1b[32m";
            }
            cout << *i;
        }


        if((userInput.size() + newLineCounter) < passage.size())
        {
            cout << "\x1b[31m";
            for (auto j(passage.begin()+distance(userInput.begin(), userInput.end())); j != passage.end(); ++j)
            {
                if (*j == '\n')
                {
                    cout << "\n";
                }
                else
                {
                cout << "_";
                }
            }
        } 
        cout << endl;
    

    duration<double> timeInterval = end - start;
    /* duration<double> secondsInMinute = duration<double>(60.0);
    duration<double> numberOfWords = duration<double>(50.0);
    duration<double> WPM = duration<double>(numberOfWords / (timeInterval / secondsInMinute));
    
    cout << "\x1b[37mTime taken: " << timeInterval.count() << endl;
    cout << "WPM: " << WPM.count() << endl;
    cout << "Accuracy: " << static_cast<double>(passage.size() - errors) / passage.size()  * 100 << " %" << endl;
    cout << "Errors: " << errors << endl; */

    cout << "\x1b[37m";

    this_thread::sleep_for(milliseconds(500));
    


    return timeInterval.count();

    
}

double TextDisplay::lifeDisplay(vector<string>& userInput, int& score, vector<string>& wordList) {
    this->wordListSelect(wordList);
    userInput = {};
    string input = "";
    int errors = 0;
    score = 0;
    int lives = 3;
    milliseconds timeout(5000); // 10 second timeout
    //duration<double> totalTime;
    cout << "\x1b[H\x1b[2J";
    cout << "Press enter key after each word!! :)" << endl;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < wordList.size(); ++i) {
        /* int countdown = 10;
        int counter = 0; */
        input = "";
        /* cout << "\x1b[6B\x1b[37m" << "Countdown = " << countdown;
        cout << "\x1b[H"; */
        cout << "\x1b[34m";
        cout << wordList.at(i) << endl << endl;
        cout << "\x1b[32m";
        cout << "\033[s";

        //auto start = high_resolution_clock::now();
        
        bool thread_terminated = false; //check for thread termination
        thread t1([&]() {
        cin >> input;
        thread_terminated = true;
        });

        auto t_handle = t1.native_handle();
        auto startTime = now_ms();
        t1.detach();

        while(now_ms() - startTime < timeout && input.empty()) {
            this_thread::sleep_for(milliseconds(100));
            /* counter++;
            if ((counter % 10) == 0)
            {
                countdown--;
                cout << "\x1b[4B\x1b[37m" << "countdown = " << countdown;
                cout << "\x1b[4A";
            } */
        }

        if(! thread_terminated) {
            pthread_cancel(t_handle);
        }

        /* auto end = high_resolution_clock::now();

        duration<double> tempInterval = end - start;
        totalTime += tempInterval; */
        userInput.push_back(input);

        cout << "\033[u\033[0K";

    if (!input.empty()) {
        for (auto j(input.begin() ); j != input.end(); ++j){ // reads and compares the system prompt vs the user string
            if (*j != *(wordList.at(i).begin() + distance(input.begin() , j))){ // if the current char (i) is not equal to the userString at i (beginning of userString (0) + distance of i)
                //++errors;
                cout << "\x1b[31m";
            } 
            else{
                cout << "\x1b[32m";
            }
            cout << *j;
        }
        if(input.size() < wordList.at(i).size())
        {
            int counter = static_cast<int>(wordList.at(i).size() - input.size());
            {
                while (counter > 0)
                {
                    cout << "\x1b[31m" << "_";
                    counter--;
                }
            }
        }
    }
    else {
        cout << "\x1b[31m\x1b[9m" << wordList.at(i);
        cout << "\x1b[29m";
    }

        cout << endl;
        if (input != wordList.at(i))
        {
            lives = lives - 1;
        }
        else
        {
            score++;
        }

        if (score + (3 - lives) >= 100)
        {
            cout << "\x1b[33m" << "Congratulations!!! You have no life but you did manage to complete 100 words..." << endl;
            cout << "So let's celebrate that I guess. Seriously, find something better to do <3 :)" << endl;
            this_thread::sleep_for(milliseconds(2000));
            cout << "\x1b[37m";
        }

        string temp;
        getline(cin, temp);
        if (cin.fail()) { 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (lives <= 0)
        {
            break;
        }

        this_thread::sleep_for(milliseconds(500));
        cout << "\x1b[H\x1b[2J";
    }

    auto end = high_resolution_clock::now();

    duration<double> tempInterval = end - start;

    cout << "\x1b[37m";
    return tempInterval.count();
} 

void TextDisplay::passageSelect(string& passage, int& count) {
    string theme = "na";
    char difficulty = 'n'; 
    bool valid;
    cout << "\x1b[H\x1b[2J";

    do {
    valid = true;
    cout << "Enter the number of words you want for your test out of these options (10, 25, 50): ";
    cin >> count;
    cout << endl;
    if (count != 10 && count != 25 && count != 50)
    {
        valid = false;
        cout << "Incorrect word count. Try again!" << endl;
    }
    else {
        cout << count << "-word test chosen. Please select further customization before starting test." << endl;
    }
    } while (!valid);

    wordOptions(difficulty, theme);

    passage = word::generatePassage(count, difficulty, theme);
    passage = word::generatePassage(count, difficulty, theme);
}
    
void TextDisplay::wordListSelect(vector<string>& wordList) {
    string theme = "na";
    char difficulty = 'n';
    cout << "\x1b[H\x1b[2J";
    wordOptions(difficulty, theme);
    wordList = word::generateWordList(difficulty, theme);
}

void TextDisplay::wordOptions(char& difficulty, string& theme){
    char temp, temp2;
    string tempIn;
    bool valid;
    difficulty = 'n';
    theme = "na";

    do {
    valid = true;
    tempIn = "";


    cout << "Enter: 0 if you'd like to choose a difficulty level" << endl; 
    cout << "       1 if you want to select a theme" << endl;
    cout << "       2 if you'd like all default options" << endl;
    cin >> temp;
    if (temp == '0')
    {
        cout << endl;
        cout << "Enter e for easy, m for medium, or h for hard: ";
        cin >> temp2;
        switch (temp2){
            case 'e':
                difficulty = 'e';
                break;
            case 'm':
                difficulty = 'm';
                break;
            case 'h':
                difficulty = 'h';
                break;
            default:
                valid = false;
                cout << endl << "Invalid choice for difficulty entered! Please try again." << endl;
        }
    }
    else if (temp == '1')
    {
        cout << endl;
        cout << "Enter one of the following choices: " << endl;
        cout << "sp - space" << endl;
        cout << "sh - superhero" << endl;
        cout << "di - disney" << endl;
        cout << "vg - video games" << endl;
        cout << "lt - literature" << endl;
        cout << "fd - food" << endl;
        cout << "mu - music" << endl;
        cin >> tempIn;
        if (tempIn == "sp"){
            theme = "sp";
        }
        else if (tempIn == "sh"){
            theme = "sh";
        }
        else if (tempIn == "di"){
            theme = "di";
        }
        else if (tempIn == "vg"){
            theme = "vg";
        }
        else if (tempIn == "lt"){
            theme = "lt";
        }
        else if (tempIn == "fd"){
            theme = "fd";
        }
        else if (tempIn == "mu"){
            theme = "mu";
        }
        else {
                valid = false;
                cout << endl << "Invalid choice for theme entered! Please try again." << endl;
        }
    }
    else if (temp == '2')
    {
        break;
    }
    else {
        valid = false;
        cout << endl << "Invalid choice. Please try again." << endl;
    }
    } while (!valid);
}


/* int main () {

    TextDisplay testing;
    string userInput = "";
    string passage = "";
    cout << testing.timedDisplay(userInput, passage) << endl;
    cout << userInput << endl;
    this_thread::sleep_for(milliseconds(5000));
    int score = 0;
    vector<string> userIn = {};
    vector<string> wordList = {};
    double time = testing.lifeDisplay(userIn, score, wordList);
    cout << time;
    cout << endl << "score = " << score << endl;
    cout << "word list: ";
    for (auto j(userIn.begin() ); j != userIn.end(); ++j){
    cout << *j << " ";
    }

    cout << endl << "Word list size: " << userIn.size() << endl;  
}
 */
//#endif 