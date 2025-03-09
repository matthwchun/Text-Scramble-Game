#include "../src/ProfileManager.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace std;

TEST(ProfileTest, chooseProfile) {
    ProfileUpdater tester;
    ProfileManager test(tester);
    EXPECT_NO_THROW(test.chooseProfile()); // check that username file is created, hood
    EXPECT_EQ(test.getUsername(), "Hood");
    test.createProfile(); // create jason
    test.chooseProfile();
    EXPECT_EQ(test.getUsername(), "Jason");
}

TEST(ProfileTest, getUsername) {
    ProfileUpdater tester;
    ProfileManager test(tester);
    EXPECT_EQ(test.getUsername(), "");
    test.chooseProfile(); //choose jason
    EXPECT_EQ(test.getUsername(), "Jason");
    string name = "Jason";
    test.deleteProfile(name); // delete jason
    test.chooseProfile(); // choose hood
    EXPECT_EQ(test.getUsername(), "Hood");
}

TEST(ProfileTest, getUserFileName) {
    ProfileUpdater tester;
    ProfileManager test(tester);
    test.createProfile(); //create jason
    test.chooseProfile(); //choose jason
    EXPECT_EQ(test.getUsername(), "Jason");
    EXPECT_EQ(test.getUserFileName("Jason"), "../data/Jason.txt");
}


TEST(ProfileTest, switchUsername) {
    ProfileUpdater tester;
    ProfileManager test(tester);
    test.chooseProfile(); //choose jason
    string newName = "Roy";
    test.switchUsername(newName);
    EXPECT_EQ(test.getUsername(), "Roy");
    EXPECT_EQ(test.getUserFileName("Roy"), "../data/Roy.txt");
    newName = "Hood";
    test.switchUsername(newName);
    EXPECT_EQ(test.getUsername(), "Roy");
    EXPECT_EQ(test.getUserFileName("Roy"), "../data/Roy.txt");
}

TEST(Profile, printNames) {
    ProfileUpdater tester;
    ProfileManager test(tester);
    test.chooseProfile(); // choose roy
    ofstream out("out.txt");
    auto coutbuf = cout.rdbuf(out.rdbuf());
    test.printNames();
    cout.rdbuf(coutbuf);
    out.close();
    ifstream in("out.txt");
    string temp;
    getline(in, temp);
    EXPECT_EQ(temp, "Hood");
    getline(in, temp);
    EXPECT_EQ(temp, "Roy");
}

TEST(ProfileTest, deleteProfile) {
    ProfileUpdater tester;
    ProfileManager test(tester);
    test.chooseProfile();
    string deleteName = "Hood";
    test.deleteProfile(deleteName);
    deleteName = "Roy";
    test.deleteProfile(deleteName);
    test.createProfile();
    test.chooseProfile();
}