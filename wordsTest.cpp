#include "../src/words.h"

#include <gtest/gtest.h>

using namespace std;

TEST(WordTest, passageCountCorrect) {
    int temp = 0;
    word::getTotalPassageNumber(temp);
    EXPECT_EQ(temp,111);
}

TEST(WordTest, fileCheckValid) {
    string temp = "../text/10/words10_di_0.txt";
    EXPECT_TRUE(word::fileCheck(temp));
    temp = "../text/25/words25_e_0.txt";
    EXPECT_TRUE(word::fileCheck(temp));
    temp = "../text/50/words50_0.txt";
    EXPECT_TRUE(word::fileCheck(temp));
}

TEST(WordTest, fileCheckInvalid) {
    string temp = "../text/10/words50_di_0.txt";
    EXPECT_FALSE(word::fileCheck(temp));
    temp = "../text/25/words10_e_0.txt";
    EXPECT_FALSE(word::fileCheck(temp));
    temp = "../text/50/words25_0.txt";
    EXPECT_FALSE(word::fileCheck(temp));
}

TEST(WordTest, passageGen) {
    string temp = word::generatePassage(10, 't', "na");
    EXPECT_EQ(temp, "Testing testing.");
}

TEST(WordTest, wordListGen) {
    vector<string> temp = word::generateWordList('t', "na");
    EXPECT_EQ(temp.size(), 3);
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_EQ(temp.at(i), "testing");
    }
}

TEST(WordTest, genFileName) {
    string temp;
    temp = word::generateFileName(10, 'n', "na", 0);
    EXPECT_EQ(temp, "../text/10/words10_0.txt");
    temp = word::generateFileName(25, 'h', "na", 0);
    EXPECT_EQ(temp, "../text/25/words25_h_0.txt");
    temp = word::generateFileName(50, 'n', "sh", 0);
    EXPECT_EQ(temp, "../text/50/words50_sh_0.txt");
    temp = word::generateFileName(100, 't', "na", 0);
    EXPECT_EQ(temp, "../text/100/words100_t_0.txt");
}

TEST(WordTest, countPassageGroup) {
    int temp;
    temp = word::countPassageGroup(10, 'n', "na");
    EXPECT_EQ(temp, 5);
    temp = word::countPassageGroup(25, 'h', "na");
    EXPECT_EQ(temp, 3);
    temp = word::countPassageGroup(50, 'n', "sh");
    EXPECT_EQ(temp, 3);
    temp = word::countPassageGroup(100, 't', "na");
    EXPECT_EQ(temp, 1);
}