#include "../src/ProfileUpdater.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace std;

TEST(ProfileUpdaterTest, setStats0) {
    ProfileUpdater test;
    string name = "jason";
    test.switchProfile(name);
    EXPECT_NO_THROW(test.setStats(0, 0, 0, 0, 0, 0));
    ifstream out("../data/jason.txt");
    string check;
    int counter = 0;
    while (getline(out, check))
    {
        EXPECT_TRUE(check == "0");
        counter++;
    }
    EXPECT_EQ(counter, 6);
}

TEST(ProfileUpdaterTest, setStatsTypical) {
    ProfileUpdater test;
    string name = "jason";
    test.switchProfile(name);
    EXPECT_NO_THROW(test.setStats(92.2, 97.8, 32.5, 6, 1, 4));
    ifstream out("../data/jason.txt");
    double WPM;
    double accuracy;
    double time;
    int errors;
    int attScore;
    int testCount;
    out >> WPM >> accuracy >> time >> errors >> attScore >> testCount;
    EXPECT_DOUBLE_EQ(WPM, 92.2);
    EXPECT_DOUBLE_EQ(accuracy, 97.8);
    EXPECT_DOUBLE_EQ(time, 32.5);
    EXPECT_EQ(errors, 6);
    EXPECT_EQ(attScore, 1);
    EXPECT_EQ(testCount, 4);
}

TEST(ProfileUpdaterTest, outputDefaultProfile) {
    ProfileUpdater test;
    string name = "jason";
    test.switchProfile(name);
    EXPECT_NO_THROW(test.setStats(0, 0, 0, 0, 0, 0));
    ofstream out("out.txt");
    auto coutbuf = cout.rdbuf(out.rdbuf());
    test.outputProfile();
    cout.rdbuf(coutbuf);
    out.close();
    ifstream in("out.txt");
    string temp;
    getline(in, temp);
    EXPECT_EQ(temp, "Time taken for test: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Accuracy: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "WPM: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Number of errors: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Attrition score: 0");
    getline(in, temp);
    EXPECT_EQ(temp, "Total number of tests taken: 0");
}

TEST(ProfileUpdaterTest, outputUserProfile) {
    ProfileUpdater test;
    string name = "jason";
    test.switchProfile(name);
    ofstream out("out.txt");
    EXPECT_NO_THROW(test.setStats(92.2, 97.8, 32.5, 6, 1, 4));
    auto coutbuf = cout.rdbuf(out.rdbuf());
    test.outputProfile();
    cout.rdbuf(coutbuf);
    out.close();
    ifstream in("out.txt");
    string temp;
    getline(in, temp);
    EXPECT_EQ(temp, "Time taken for test: 32.5");
    getline(in, temp);
    EXPECT_EQ(temp, "Accuracy: 97.8");
    getline(in, temp);
    EXPECT_EQ(temp, "WPM: 92.2");
    getline(in, temp);
    EXPECT_EQ(temp, "Number of errors: 6");
    getline(in, temp);
    EXPECT_EQ(temp, "Attrition score: 1");
    getline(in, temp);
    EXPECT_EQ(temp, "Total number of tests taken: 4");
}

TEST(ProfileUpdaterTest, outputEmptyProfile) {
    ProfileUpdater test;
    string name = "leo";
    test.switchProfile(name);
    ofstream out("out.txt");
    auto coutbuf = cout.rdbuf(out.rdbuf());
    test.outputProfile();
    cout.rdbuf(coutbuf);
    out.close();
    ifstream in("out.txt");
    string temp;
    getline(in, temp);
    EXPECT_EQ(temp, "Data file not created yet!");
}