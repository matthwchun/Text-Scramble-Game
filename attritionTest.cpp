#include "../src/Attrition.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace std;

TEST(attritionTest, setMaxScore) {
    Attrition test;
    test.setMaxScore(5);
    EXPECT_EQ(test.getMaxScore(), 5);
    test.setMaxScore(100);
    EXPECT_EQ(test.getMaxScore(), 100);
    test.setMaxScore(0);
    EXPECT_TRUE(test.getMaxScore() == 0);
}


TEST(attritionTest, getScore0) {
    Attrition test;
    test.AttritionStart();
    EXPECT_EQ(test.getScore(), 0);
    EXPECT_TRUE(test.getTime() < 10.0);
}


TEST(attritionTest, getScore5) {
    Attrition test;
    test.AttritionStart();
    EXPECT_EQ(test.getScore(), 5);
    EXPECT_TRUE(test.getTime() < 15.0);
}


TEST(attritionTest, getTimeOut) {
    Attrition test;
    test.AttritionStart();
    EXPECT_EQ(test.getScore(), 0);
    EXPECT_TRUE(test.getTime() > 15.0);
}


TEST(attritionTest, calcWPM) {
    Attrition test;
    test.AttritionStart();
    EXPECT_EQ(test.getScore(), 0);
    EXPECT_TRUE(test.getTime() < 15.0);
    EXPECT_TRUE(test.calcWPM() > 20);

    test.AttritionStart();
    EXPECT_EQ(test.getScore(), 0);
    EXPECT_TRUE(test.getTime() > 15.0);
    EXPECT_TRUE(test.calcWPM() < 13);
}


/* TEST(attritionTest, calcAccuracy100) {
    Attrition test;
    test.AttritionStart();
    EXPECT_EQ(test.getScore(), 100);
    EXPECT_TRUE(test.calcAccuracy() = 100.0);
} */


TEST(attritionTest, calcHalfWrong) {
    Attrition test;
    test.AttritionStart();
    EXPECT_TRUE(test.calcAccuracy() == 50.0);
}


/* TEST(attritionTest, calcErrors0) {
    Attrition test;
    test.AttritionStart();
    EXPECT_EQ(test.getScore(), 100);
    EXPECT_TRUE(test.calcErrors() = 0);
} */


TEST(attritionTest, calcErrors3) {
    Attrition test;
    test.AttritionStart();
    EXPECT_EQ(test.getScore(), 0);
    EXPECT_TRUE(test.calcErrors() == 3);
}