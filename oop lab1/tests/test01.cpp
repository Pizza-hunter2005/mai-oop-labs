#include <gtest/gtest.h>
#include "../include/trololo.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(trololo("Hahaha looser!")=="Hhh lsr!");
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(trololo("FFFFF!")=="FFFFF!");
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(trololo("aaaAAAaEEEE")=="");
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(trololo("aeuoiqwerty")=="qwrty");
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}