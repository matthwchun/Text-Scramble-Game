#include "../src/Benchmark.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace std;

TEST(BenchmarkTest, b10) {
    Benchmark test;
    test.BenchmarkStart();
    EXPECT_TRUE(test.getTime() < 10.0);
}


TEST(BenchmarkTest, b25) {
    Benchmark test;
    test.BenchmarkStart();
    EXPECT_TRUE(test.getTime() < 20.0);
}

TEST(BenchmarkTest, b50) {
    Benchmark test;
    test.BenchmarkStart();
    EXPECT_TRUE(test.getTime() > 10.0);
}

TEST(BenchmarkTest, calcWPM) {
    Benchmark test;
    test.BenchmarkStart();
    EXPECT_TRUE(test.getTime() < 15.0);
    EXPECT_TRUE(test.calcWPM() > 20);

    test.BenchmarkStart();
    EXPECT_TRUE(test.getTime() > 15.0);
    EXPECT_TRUE(test.calcWPM() < 13);
}


TEST(BenchmarkTest, calcAccuracy100) {
    Benchmark test;
    test.BenchmarkStart();
    EXPECT_TRUE(test.calcAccuracy() == 100.0);
}


TEST(BenchmarkTest, calcHalfWrong) {
    Benchmark test;
    test.BenchmarkStart();
    EXPECT_TRUE(test.calcAccuracy() == 50.0);
}

TEST(BenchmarkTest, calcErrors3) {
    Benchmark test;
    test.BenchmarkStart();
    test.addErrors();
    EXPECT_TRUE(test.getErrors() == 3);
}

TEST(BenchmarkTest, calcErrors0) {
    Benchmark test;
    test.BenchmarkStart();
    test.addErrors();
    EXPECT_TRUE(test.getErrors() == 0);
}