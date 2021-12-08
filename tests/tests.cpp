#include "radioData.cpp"
#include "gtest/gtest.h"


TEST (ExampleTest, PositiveNos) {
    EXPECT_EQ (1, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
