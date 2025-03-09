#include "words.h"

namespace word {

void getTotalPassageNumber(int &listSize)
{
    // possible counts: 10, 25, 50 (int)
    // possible difficulty: e, m, h, n (char)
    // possible themes: sp, di, sh, fd, vg, lt, mu, na (string)

    int count = 0;
    char difficulty = 'n';
    std::string theme = "";
    int temp = 0;

    for (int i = 0; i < 3; ++i) //set up possible counts
    {
        if (i == 0)
        {
            count = 10;
        }
        if (i == 1)
        {
            count = 25;
        }
        if (i == 2)
        {
            count = 50;
        }

        

        for (int j = 0; j < 4; ++j) //possible difficulties
        {
            if (j == 0)
            {
                difficulty = 'n';
            }
            if (j == 1)
            {
                difficulty = 'e';
            }
            if (j == 2)
            {
                difficulty = 'm';
            }
            if (j == 3)
            {
                difficulty = 'h';
            }
            
            for (int k = 0; k < 8; ++k) //possible themes
            {
                if (k == 0)
                {
                    theme = "na";
                }
                if (k == 1)
                {
                    theme = "sp";
                }
                if (k == 2)
                {
                    theme = "di";
                }
                if (k == 3)
                {
                    theme = "sh";
                }
                if (k == 4)
                {
                    theme = "fd";
                }
                if (k == 5)
                {
                    theme = "vg";
                }
                if (k == 6)
                {
                    theme = "lt";
                }
                if (k == 7)
                {
                    theme = "mu";
                }
                temp = countPassageGroup(count, difficulty, theme);
                listSize += temp;
            }
        }
    }
}

std::string generatePassage(int wordCount, char diff = 'n', std::string theme = "na")
{
    int possibleMax = countPassageGroup(wordCount, diff, theme);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distMax(0,possibleMax-1);

    int pickPassage = distMax(rng);

    std::string fName = generateFileName(wordCount, diff, theme, pickPassage);

    std::ifstream passage(fName);
    if (!passage.is_open()) {
        std::cout << "Error in opening file!";
        return "";
    }
    else {
        std::string retPassage( (std::istreambuf_iterator<char>(passage) ),
                       (std::istreambuf_iterator<char>()    ) );
        return retPassage;
    }

    return "";

    
} // use options to choose passage

std::vector<std::string> generateWordList(char diff = 'n', std::string theme = "na")
{
    std::string fName = generateFileName(100, diff, theme, 0);
    std::vector<std::string> wordList;

    std::ifstream passage(fName);
    if (!passage.is_open()) {
        std::cout << "Error in opening file!";
        return std::vector<std::string>();
    }
    else {
        std::string line;
        while(getline(passage, line))
        {
            std::istringstream store(line);
            while (store) {
                std::string word;
                store >> word;
                if (word != "") {
                wordList.push_back(word);
                }
            }
        }
    }


    std::shuffle(std::begin(wordList), std::end(wordList), std::random_device());

    return wordList;
} // create word list for game mode

bool fileCheck(std::string &fileName)
{
    struct stat check;
    bool exist = (stat(fileName.c_str(), &check) == 0); // .c_str converts string to char array and stat will return 0 if no error occurs (i.e. file exists and can be accessed)
    return exist;
}

int countPassageGroup(int cnt, char diff, std::string theme)
{
    int passageCount = 0;
    int max = 10;
    std::string fName = "";

    for (int i = 0; i < max; ++i)
    {
        fName = generateFileName(cnt, diff, theme, i);
        bool open = fileCheck(fName);

        passageCount = i;

        if (!open)
        {
            break;
        }
    }

    return passageCount;
}

std::string generateFileName(int cnt, char diff, std::string theme, int passNumber) {
    std::string dir = "../text/";
    std::string prefix = "words";
    std::string extension = ".txt";
    std::string count = std::to_string(cnt);
    std::string difficulty = "";
    std::string type = "";
    std::string number = std::to_string(passNumber);
    if (diff != 'n')
    {
        difficulty = "_";
        difficulty += diff;
    }
    if (theme != "na")
    {
        type = "_";
        type += theme;
    }

    std::string fName = "";
    fName += dir;
    fName += count;
    fName += '/';
    fName += prefix;
    fName += count;
    fName += difficulty;
    fName += type;
    fName += '_';
    fName += number;
    fName += extension;

    return fName;
}

}


/* using namespace word;

int main () {
    std::srand(time(NULL));
    int size = 0;
    getTotalPassageNumber(size);
    //size = countPassageGroup(50, 'n', "sp");
    std::cout << size << std::endl;
    std::string name = "../text/25/words25_di_0.txt";
    if (fileCheck(name)) { std::cout << "file exists" << std::endl;}
    else { std::cout << "doesn't exist" << std::endl;}  

    char difficulty = 'n';
    std::string theme = "di";

     std::string test = generatePassage(25, 'n', "di");

    std::cout << "Test is \"" << test << "\"" << std::endl;

    
    
   std::vector<std::string> testList = generateWordList(difficulty, theme);

    std::cout << "Size of list is " << testList.size() << std::endl;
    std::cout << "list: ";

    for (int i = 0; i < testList.size(); ++i) {
        std::cout << testList.at(i) << std::endl;
    }  
};  */


