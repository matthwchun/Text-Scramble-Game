#include "../src/ModeSelect.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace std;

TEST(modeTest, profileEditorTest) {
    char input;
    ProfileUpdater files;
    ProfileManager user(files);
    user.chooseProfile();
    ModeSelect profEdit(user);
    profEdit.ProfileEditor();
    EXPECT_CALL(user, user.chooseProfile())
        .Times(1);
    EXPECT_CALL(user, user.switchUsername())
        .Times(1);
    EXPECT_CALL(user, user.deleteUser())
        .Times(1);
    EXPECT_CALL(user, user.deleteUser())
        .Times(1);
    EXPECT_CALL(user, user.chooseProfile())
        .Times(1);
    EXPECT_CALL(user, user.createProfile())
        .Times(1);
    EXPECT_CALL(user, user.printNames())
        .Times(1);
    EXPECT_CALL(user, user.writeStat())
        .Times(1);
    EXPECT_CALL(user, readProf())
        .Times(1);
}

TEST(modeTest, attritionTest) {
    char input;
    ProfileUpdater files;
    ProfileManager user(files);
    user.chooseProfile();
    ModeSelect attGame(user);
    attGame.AttritionMode();
    EXPECT_CALL(attGame, attGame.computeAvg())
        .Times(1);
    EXPECT_CALL(attGame, attGame.compareStats())
        .Times(1);
}


TEST(modeTest, BenchmarkTest) {
    char input;
    ProfileUpdater files;
    ProfileManager user(files);
    user.chooseProfile();
    ModeSelect bench(user);
    bench.BenchmarkMode();
    EXPECT_CALL(bench, bench.computeAvg())
        .Times(1);
    EXPECT_CALL(bench, bench.compareStats())
        .Times(1);
}

TEST(modeTest, StatOutputTest) {
    char input;
    ProfileUpdater files;
    ProfileManager user(files);
    user.chooseProfile();
    ModeSelect attGame(user);
    attGame.AttritionMode();
   EXPECT_NO_THROW(attGame.displayStats());
}

TEST(modeTest, quitTest) {
    char input;
    ProfileUpdater files;
    ProfileManager user(files);
    user.chooseProfile();
    ModeSelect attGame(user);
    attGame.AttritionMode();
    attGame.Quit();
}

TEST(modeTest, MenuTest) {
    char input;
    ProfileUpdater files;
    ProfileManager user(files);
    user.chooseProfile();
    ModeSelect mainMen(user);
    EXPECT_NO_THROW(mainMen.mainMenu());
    EXPECT_CALL(mainMen, mainMen.AttritionMode())
        .Times(1);
    EXPECT_CALL(mainMen, mainMen.BenchmarkMode())
        .Times(1);
    EXPECT_CALL(mainMen, mainMen.displayStats())
        .Times(1);
    EXPECT_CALL(mainMen, mainMen.ProfileEditor())
        .Times(1);
    EXPECT_CALL(mainMen, mainMen.Quit())
        .Times(1);
}

