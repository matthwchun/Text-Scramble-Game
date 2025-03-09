#include "../src/stats.h"

#include <string>
#include <fstream>
#include <gtest/gtest.h>

using namespace std;

TEST(StatTest, defaultConstructor) {
    EXPECT_NO_THROW (Stats());
}

TEST(StatTest, defaultValues) {
    Stats test;
    EXPECT_DOUBLE_EQ(test.WPM, 0);
    EXPECT_DOUBLE_EQ(test.accuracy, 0);
    EXPECT_DOUBLE_EQ(test.timeTaken, 0);
    EXPECT_EQ(test.numErrors, 0);
    EXPECT_EQ(test.attritionScore, 0);
}


TEST(StatTest, defaultOutput) {
    Stats test;
    ofstream out("out.txt");
    out << test;
    ifstream in("out.txt");
    string temp;
    getline(in, temp);
    EXPECT_EQ(temp, "Time taken for test: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Accuracy: 0%");
    getline(in, temp);
    EXPECT_EQ(temp, "WPM: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Number of errors: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Attrition score: 0");
}

TEST(StatTest, typicalOutput) {
    Stats test;
    test.setAccuracy(32.2);
    test.setAttritionScore(16);
    test.setNumErrors(2);
    test.setTimeTaken(23.8);
    test.setWPM(95.3);
    ofstream out("out.txt");
    out << test;
    ifstream in("out.txt");
    string temp;
    getline(in, temp);
    EXPECT_EQ(temp, "Time taken for test: 23.8");
    getline(in, temp);
    EXPECT_EQ(temp, "Accuracy: 32.2%");
    getline(in, temp);
    EXPECT_EQ(temp, "WPM: 95.3");
    getline(in, temp);
    EXPECT_EQ(temp, "Number of errors: 2");
    getline(in, temp);
    EXPECT_EQ(temp, "Attrition score: 16");
}


TEST(StatTest, negativeOutput) {
    Stats test;
    test.setAccuracy(-32.2);
    test.setAttritionScore(-16);
    test.setNumErrors(-2);
    test.setTimeTaken(-23.8);
    test.setWPM(-95.3);
    ofstream out("out.txt");
    out << test;
    ifstream in("out.txt");
    string temp;
    getline(in, temp);
    EXPECT_EQ(temp, "Time taken for test: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Accuracy: 0%");
    getline(in, temp);
    EXPECT_EQ(temp, "WPM: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Number of errors: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Attrition score: 0");
}