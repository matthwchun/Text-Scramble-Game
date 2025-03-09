#include "ModeSelect.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;


void ModeSelect::computeAvg(Stats &curr, Stats& result) {
    if (runCount <= 0)
    {
      cout << "no tests have been run yet ..." << endl;
      return;
    }
    result.numErrors = result.numErrors * (runCount-1);
    result.numErrors += curr.numErrors;
    result.numErrors = result.numErrors/runCount;

    result.accuracy = result.accuracy * (runCount-1);
    result.accuracy += curr.accuracy;
    result.accuracy = result.accuracy/runCount;

    result.WPM = result.WPM * (runCount-1);
    result.WPM += curr.WPM;
    result.WPM = result.WPM/runCount;

    result.timeTaken = result.timeTaken * (runCount-1);
    result.timeTaken += curr.timeTaken;
    result.timeTaken = result.timeTaken/runCount;

    result.attritionScore = result.attritionScore * (runCount-1);
    result.attritionScore += curr.attritionScore;
    result.attritionScore = result.attritionScore/runCount;
  }

void ModeSelect::compareStats(Stats &curr, Stats& best) {
  if (curr.accuracy > best.accuracy)
  {
    best.setAccuracy(curr.accuracy);
  }
  if ((curr.numErrors < best.numErrors) && (curr.numErrors != 0))
  {
    best.setNumErrors(curr.numErrors);
  }
  if (curr.WPM > best.WPM)
  {
    best.WPM = curr.WPM;
  }
  if ((curr.timeTaken < best.timeTaken) && (curr.timeTaken != 0.0))
  {
    best.setTimeTaken(curr.timeTaken);
  }
  if (curr.attritionScore > best.attritionScore)
  {
    best.setAttritionScore(curr.attritionScore);
  }
}

void ModeSelect::mainMenu() {
      char input;
      bool done = false;
      do {
      cout << "\x1b[H\x1b[2J";
      cout << "-----------\nMENU\n-----------\n";
      cout << "p - Profile Editor\na - Attrition Game Mode\nb - Benchmark Mode\n";
      cout << "s - Stat History\nq - Quit\n\nChoose an option: ";
      cin >> input;
      if (input == 'p') // profile editor
      {
         ProfileEditor();
      }
      else if (input == 'a') // attrition
      {
        AttritionMode();
      }
      else if (input == 'b')  // benchmark
      {
        BenchmarkMode();
      }
      else if (input == 's')  // stat display
      {
        displayStats();
      }
      else if (input == 'q')
      {
        Quit();
        done = true;
      }
      else
      {
        cout << endl;
        cout << "\x1b[31m Invalid input detected. Please try again! :)";
        cout << "\x1b[37m";
        cout << endl;
        this_thread::sleep_for(milliseconds(1000));
      }
   } while (!done);

}

void ModeSelect::ProfileEditor() {
      char input;
      bool done = false;
      do {
        cout << "\x1b[H\x1b[2J";
      cout << "-----------------\nMENU FOR " + currProfile->getUsername() + "\n-----------------\n";
      cout << "s - select new profile\nc - change current username\nn - create new profile\nd - delete profile\n";
      cout << "p - display possible profiles\nw - Write stats to file\nr - read and display user stats from file\n";
      cout << "q - close editor\n\nChoose an option: ";
      cin >> input;
      if (input == 's') // profile select
      {
        cin.ignore();
        currProfile->chooseProfile();
      }
      else if (input == 'c') // username change
      {
        string newUser;
        cout << "Please enter new username: ";
        cin.ignore();
        getline(cin, newUser);
        currProfile->switchUsername(newUser);
      }
      else if (input == 'd')  // delete prof
      {
        string deleteUser;
        currProfile->printNames();
        cout << "Please enter the user you wish to delete: ";
        cin.ignore();
        getline(cin, deleteUser);
        currProfile->deleteProfile(deleteUser);
        ifstream checkEmpty("../data/usernamesFile.txt");
        if (checkEmpty.peek() == ifstream::traits_type::eof()) {   
            cin.ignore(); 
            currProfile->createProfile();
        }
        if (deleteUser == currProfile->getUsername())
        {
          cout << "Press enter to confirm!" << endl;
          cin.ignore();
          currProfile->chooseProfile();
        }
      }
      else if (input == 'n')  // new prof
      {
        cin.ignore();
        currProfile->createProfile();
      }
      else if (input == 'p')  // username list 
      {
        currProfile->printNames();
        cout << "Press enter when done looking!";
        string temp;
        cin.ignore();
        while (getline(cin,temp)) {
          if (temp.empty())
          {
            break;
          }
        }
      }
      else if (input == 'w') // write stats
      {
        int statChoice = 0;
        bool invalid = false;
        do {
        cout << "Select 1 for current run stats, 2 for average stats, or 3 for your best stats!";
        cout << endl;
        cin >> statChoice;
        cout << endl;
        if (statChoice == 1)
        {
          invalid = false;
          currProfile->writeStat(currentStats,runCount);
        }
        else if (statChoice == 2)
        {
          invalid = false;
          currProfile->writeStat(avgStats,runCount);
        }
        else if (statChoice == 3)
        {
          invalid = false;
          currProfile->writeStat(bestStats,runCount);
        }
        else {
          invalid = true;
        }
        } while (invalid);
      }
      else if (input == 'r') // read stats
      {
        currProfile->readProf();
        cout << "Press enter when done looking!";
        string temp;
        cin.ignore();
        while (getline(cin,temp)) {
          if (temp.empty())
          {
            break;
          }
        }
      }
      else if (input == 'q') // quit
      {
        done = true;
      }
      else
      {
        cout << endl;
        cout << "\x1b[31m Invalid input detected. Please try again! :)";
        cout << "\x1b[37m";
        cout << endl;
        this_thread::sleep_for(milliseconds(1000));
      }
   } while (!done);
}

void ModeSelect::AttritionMode() {
    Attrition currMode;
    char input;
    bool invalid = false;
    bool done = false;
    do {
    runCount++;
    currMode.AttritionStart();

    currentStats.setTimeTaken(currMode.getTime());
    currentStats.setAttritionScore(currMode.getScore());
    currentStats.setWPM(currMode.calcWPM());
    currentStats.setAccuracy(currMode.calcAccuracy());
    currentStats.setNumErrors(currMode.calcErrors());

    if (runCount == 1) {
      bestStats = currentStats;
      avgStats = currentStats;
    }
    else {
      computeAvg(currentStats, avgStats);
      compareStats(currentStats, bestStats);
    }

    cout << currentStats;
    cout << "Press enter to continue!" << endl;
    string temp;
    cin.ignore();
    while (getline(cin,temp)) {
      if (temp.empty())
      {
      break;
      }
    }
    
    cout << "\x1b[H\x1b[2J";
    do {
    cout << "Press y to play again or n to return to menu: ";
    cin >> input;
    if (input == 'y') {
      invalid = false;
    }
    else if (input == 'n')
    {
      invalid = false;
      done = true;
    }
    else {
      invalid = true;
    }
    } while (invalid);

    } while (!done);

}

void ModeSelect::BenchmarkMode() {
    Benchmark currMode;
    char input;
    bool invalid = false;
    bool done = false;
    do {
    runCount++;
    currMode.BenchmarkStart();

    currentStats.setTimeTaken(currMode.getTime());
    currentStats.setAttritionScore(0);
    currentStats.setWPM(currMode.calcWPM());
    currentStats.setAccuracy(currMode.calcAccuracy());
    currentStats.setNumErrors(currMode.getErrors());

    if (runCount == 1) {
      bestStats = currentStats;
      avgStats = currentStats;
    }
    else {
      computeAvg(currentStats, avgStats);
      compareStats(currentStats, bestStats);
    }

    cout << currentStats;
    cout << "Press enter to continue!" << endl;
    string temp;
    cin.ignore();
    while (getline(cin,temp)) {
      if (temp.empty())
      {
      break;
      }
    }

    cout << "\x1b[H\x1b[2J";
    do {
    cout << "Press y to play again or n to return to menu: ";
    cin >> input;
    if (input == 'y') {
      invalid = false;
    }
    else if (input == 'n')
    {
      invalid = false;
      done = true;
    }
    else {
      invalid = true;
    }
    } while (invalid);

    } while (!done);
}

void ModeSelect::displayStats() {
  int input;
  char again;
  bool done = false;
  bool invalid =  false;
  do {
  cout << "\x1b[H\x1b[2J";
  cout << "Select 1 for current run stats, 2 for average stats, 3 for your best stats, or 4 to see how many tests you've done!";
  cout << endl;
  cin >> input;
  cout << endl;
  if (input == 1)
  {
    cout << currentStats;
  }
  if (input == 2)
  {
    cout << avgStats;
  }
  if (input == 3)
  {
    cout << bestStats;
  }
  if (input == 4)
  {
    cout << "number of tests taken: " << runCount << endl;
  }

  do {
  cout << "Do you want to see more stats (y or n): ";
  cin >> again;
  cout << endl;
  if (again == 'n') {
    invalid = false;
    done = true;
  } 
  else if (again == 'y') {
    invalid = false;
  }
  else {
    invalid = true;
  }
  } while (invalid);

  } while (!done);
}

void ModeSelect::Quit() {
    cout << "\x1b[H\x1b[2J";
    cout << "\x1b[31mTh\x1b[33manks \x1b[32mfor \x1b[34mplay\x1b[35ming\x1b[37m\x1b[3m " << currProfile->getUsername() << "!" << endl;
    cout << "\x1b[23m";
    cout << "In this session, you completed " << runCount << " tests." << endl << endl;
    cout << "\x1b[36m";
    cout << "Your best stats were: " << endl;
    cout << bestStats;
    cout << "\x1b[35m";
    cout << "Your average stats were: " << endl;
    cout << avgStats;
    cout << "\x1b[31mCo\x1b[33mme \x1b[32mback \x1b[34many\x1b[35mtime \x1b[37m:)" << endl;
    
}