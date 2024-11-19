#include <gtest/gtest.h>
#include "container.h"

struct MyStruct {
    int a;
    double b;
    char c;

    MyStruct(int a, double b, char c) : a(a), b(b), c(c) {}

    bool operator==(const MyStruct& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};

TEST(MyContainerTest, TestPushBackAndAccess) {
    MemoryResource resource;
    DynamicArray<int> container(&resource);

    container.push_back(10);
    container.push_back(20);

    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 10);
    EXPECT_EQ(container[1], 20);
}

TEST(MyContainerTest, TestResize) {
    MemoryResource resource;
    DynamicArray<int> container(&resource);

    for (int i = 0; i < 15; ++i) {
        container.push_back(i);
    }

    EXPECT_EQ(container.size(), 15);
    EXPECT_GE(container.get_capacity(), 20);

    for (int i = 0; i < 15; ++i) {
        EXPECT_EQ(container[i], i);
    }
}

TEST(MyContainerTest, TestCustomType) {
    MemoryResource resource;
    DynamicArray<MyStruct> container(&resource);

    container.push_back(MyStruct(1, 2.2, 'a'));
    container.push_back(MyStruct(3, 4.4, 'b'));

    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], MyStruct(1, 2.2, 'a'));
    EXPECT_EQ(container[1], MyStruct(3, 4.4, 'b'));
}

TEST(MyContainerTest, TestIterator) {
    MemoryResource resource;
    DynamicArray<int> container(&resource);

    for (int i = 0; i < 5; ++i) {
        container.push_back(i);
    }

    int expected_value = 0;
    for (auto it = container.begin(); it != container.end(); ++it) {
        EXPECT_EQ(*it, expected_value); 
        ++expected_value;
    }

    expected_value = 0;
    for (int value : container) {
        EXPECT_EQ(value, expected_value);
        ++expected_value;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}