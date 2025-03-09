#include "../src/TextDisplay.h"

#include <gtest/gtest.h>

using namespace std;

TEST(DisplayTest, benchmark10) {
    TextDisplay test;
    double time;
    string userInput = "";
    string passage = "";
    int count = 0;
    EXPECT_NO_THROW(time = test.timedDisplay(userInput, passage, count));
    EXPECT_TRUE(time < 10.0);
    EXPECT_TRUE(count == 10);
    EXPECT_TRUE(userInput == passage);

}

TEST(DisplayTest, benchmark25e) {
    TextDisplay test;
    double time;
    string userInput = "";
    string passage = "";
    int count = 0;
    EXPECT_NO_THROW(time = test.timedDisplay(userInput, passage, count));
    EXPECT_TRUE(time < 15.0);
    EXPECT_TRUE(count == 25);
    EXPECT_TRUE(userInput == passage);
}

TEST(DisplayTest, benchmark50sp) {
    TextDisplay test;
    double time;
    string userInput = "";
    string passage = "";
    int count = 0;
    EXPECT_NO_THROW(time = test.timedDisplay(userInput, passage, count));
    EXPECT_TRUE(time > 15.0);
    EXPECT_TRUE(count == 50);
    EXPECT_TRUE(userInput == passage);
}

TEST(DisplayTest, benchmarkInvalidInput) {
    TextDisplay test;
    double time;
    string userInput = "";
    string passage = "";
    int count = 0;
    EXPECT_NO_THROW(time = test.timedDisplay(userInput, passage, count));
    EXPECT_TRUE(time < 5.0);
    EXPECT_TRUE(count == 50);
    EXPECT_TRUE(userInput == "e");
    EXPECT_FALSE(userInput == passage);
}


TEST(DisplayTest, attrition0) {
    TextDisplay test;
    double time;
    vector<string> userInput = {};
    vector<string> wordList = {};
    int score = 0;
    EXPECT_NO_THROW(time = test.lifeDisplay(userInput, score, wordList)); // 2, default
    EXPECT_TRUE(time < 10.0);
    EXPECT_TRUE(score == 0);
    EXPECT_EQ(userInput.size(), 3);
    EXPECT_EQ(wordList.size(), 100);
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_FALSE(userInput.at(i) == wordList.at(i));
    }

}

TEST(DisplayTest, attrition5) {
    TextDisplay test;
    double time;
    vector<string> userInput = {};
    vector<string> wordList = {};
    int score = 0;
    EXPECT_NO_THROW(time = test.lifeDisplay(userInput, score, wordList)); // 1, theme
    EXPECT_TRUE(time < 20.0);
    EXPECT_TRUE(score == 5);
    EXPECT_EQ(userInput.size(), 8);
    EXPECT_EQ(wordList.size(), 100);
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_TRUE(userInput.at(i) == wordList.at(i));
    }
    for (int i = 5; i < 8; ++i)
    {
        EXPECT_FALSE(userInput.at(i) == wordList.at(i));
    }
}

TEST(DisplayTest, attritionTimeOut) {
    TextDisplay test;
    double time;
    vector<string> userInput = {};
    vector<string> wordList = {};
    int score = 0;
    EXPECT_NO_THROW(time = test.lifeDisplay(userInput, score, wordList)); //0 , difficulty
    EXPECT_TRUE(time > 15.0);
    EXPECT_TRUE(score == 0);
    EXPECT_EQ(userInput.size(), 3);
    EXPECT_EQ(wordList.size(), 100);
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_FALSE(userInput.at(i) == wordList.at(i));
    }
}

