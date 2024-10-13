#include <gtest/gtest.h>
#include "array.h"
#include "rectangle.h"
#include "square.h"
#include "trapeze.h"

TEST(SquareTest, AreaTest) {
    std::array<std::pair<double, double>, 4> arr = {std::make_pair(0.0, 0.0), std::make_pair(0.0, 2.0),
        std::make_pair(2.0, 2.0),std::make_pair(2.0, 0.0)};
    Square sq(arr);
    EXPECT_DOUBLE_EQ(double(sq), 4.0);
}

TEST(SquareTest, AreaWithZeroesTest) {
    Square sq;
    EXPECT_DOUBLE_EQ(double(sq), 0);
}

TEST(SquareTest, CenterTest) {
    std::array<std::pair<double, double>, 4> arr = {std::make_pair(0.0, 0.0), std::make_pair(0.0, 2.0),
        std::make_pair(2.0, 2.0),std::make_pair(2.0, 0.0)};
    Square sq(arr);
    auto center = sq.center();
    EXPECT_DOUBLE_EQ(center.first, 1);
    EXPECT_DOUBLE_EQ(center.second, 1);
}

TEST(RectangleTest, AreaTest) {
    std::array<std::pair<double, double>, 4> arr = {std::make_pair(0.0, 0.0), std::make_pair(0.0, 3.0),
        std::make_pair(4.0, 3.0),std::make_pair(4.0, 0.0)};
    Rectangle rect(arr);
    EXPECT_DOUBLE_EQ(double(rect), 12.0);
}

TEST(RectangleTest, CenterTest) {
    std::array<std::pair<double, double>, 4> arr = {std::make_pair(0.0, 0.0), std::make_pair(0.0, 3.0),
        std::make_pair(4.0, 3.0),std::make_pair(4.0, 0.0)};
    Rectangle rect(arr);
    auto center = rect.center();
    EXPECT_DOUBLE_EQ(center.first, 2);
    EXPECT_DOUBLE_EQ(center.second, 1.5);
}

TEST(TrapezeTest, AreaTest) {
    std::array<std::pair<double, double>, 4> arr = {std::make_pair(0.0, 0.0), std::make_pair(1.0, 3.0),
        std::make_pair(4.0, 3.0),std::make_pair(5.0, 0.0)};
    Trapeze trap(arr);
    EXPECT_DOUBLE_EQ(double(trap), 12);
}

TEST(TrapezeTest, CenterTest) {
    std::array<std::pair<double, double>, 4> arr = {std::make_pair(0.0, 0.0), std::make_pair(1.0, 3.0),
        std::make_pair(4.0, 3.0),std::make_pair(5.0, 0.0)};
    Trapeze trap(arr);
    auto center = trap.center();
    EXPECT_DOUBLE_EQ(center.first, 2.5);
    EXPECT_DOUBLE_EQ(center.second, 1.5);
}

TEST(Array, TotalArea) {
	std::array<std::pair<double, double>, 4> arr1 = {std::make_pair(0.0, 0.0), std::make_pair(0.0, 2.0),
        std::make_pair(2.0, 2.0),std::make_pair(2.0, 0.0)};
    Square sq(arr1);
    std::array<std::pair<double, double>, 4> arr2 = {std::make_pair(0.0, 0.0), std::make_pair(0.0, 3.0),
        std::make_pair(4.0, 3.0),std::make_pair(4.0, 0.0)};
    Rectangle rect(arr2);
    std::array<std::pair<double, double>, 4> arr3 = {std::make_pair(0.0, 0.0), std::make_pair(1.0, 3.0),
        std::make_pair(4.0, 3.0),std::make_pair(5.0, 0.0)};
    Trapeze trap(arr3);

    Array figures(3);
    figures.add(0, &sq);
    figures.add(1, &rect);
    figures.add(2, &trap);
	EXPECT_DOUBLE_EQ(figures.total_area(), 28);
}
