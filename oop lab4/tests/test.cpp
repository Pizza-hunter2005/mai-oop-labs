#include <gtest/gtest.h>
#include "array.h"
#include "point.h"
#include "rectangle.h"
#include "square.h"
#include "trapeze.h"


// Тест площади для квадрата
TEST(SquareTest, AreaTest) {
    std::array<Point<double>, 4> points = {
        Point<double>(0.0, 0.0), Point<double>(0.0, 2.0),
        Point<double>(2.0, 2.0), Point<double>(2.0, 0.0)
    };
    Square<double> sq(points);
    EXPECT_DOUBLE_EQ(double(sq), 4.0);
}

// Тест площади для квадрата с нулевыми координатами
TEST(SquareTest, AreaWithZeroesTest) {
    Square<double> sq;
    EXPECT_DOUBLE_EQ(double(sq), 0);
}

// Тест центра квадрата
TEST(SquareTest, CenterTest) {
    std::array<Point<double>, 4> points = {
        Point<double>(0.0, 0.0), Point<double>(0.0, 2.0),
        Point<double>(2.0, 2.0), Point<double>(2.0, 0.0)
    };
    Square<double> sq(points);
    Point<double> center = sq.center();
    EXPECT_DOUBLE_EQ(center.getx(), 1.0);
    EXPECT_DOUBLE_EQ(center.gety(), 1.0);
}

// Тест площади для прямоугольника
TEST(RectangleTest, AreaTest) {
    std::array<Point<double>, 4> points = {
        Point<double>(0.0, 0.0), Point<double>(0.0, 3.0),
        Point<double>(4.0, 3.0), Point<double>(4.0, 0.0)
    };
    Rectangle<double> rect(points);
    EXPECT_DOUBLE_EQ(double(rect), 12.0);
}

// Тест центра прямоугольника
TEST(RectangleTest, CenterTest) {
    std::array<Point<double>, 4> points = {
        Point<double>(0.0, 0.0), Point<double>(0.0, 3.0),
        Point<double>(4.0, 3.0), Point<double>(4.0, 0.0)
    };
    Rectangle<double> rect(points);
    auto center = rect.center();
    EXPECT_DOUBLE_EQ(center.getx(), 2.0);
    EXPECT_DOUBLE_EQ(center.gety(), 1.5);
}

// Тест площади для трапеции
TEST(TrapezeTest, AreaTest) {
    std::array<Point<double>, 4> points = {
        Point<double>(0.0, 0.0), Point<double>(1.0, 3.0),
        Point<double>(4.0, 3.0), Point<double>(5.0, 0.0)
    };
    Trapeze<double> trap(points);
    EXPECT_DOUBLE_EQ(double(trap), 12.0);
}

// Тест центра трапеции
TEST(TrapezeTest, CenterTest) {
    std::array<Point<double>, 4> points = {
        Point<double>(0.0, 0.0), Point<double>(1.0, 3.0),
        Point<double>(4.0, 3.0), Point<double>(5.0, 0.0)
    };
    Trapeze<double> trap(points);
    auto center = trap.center();
    EXPECT_DOUBLE_EQ(center.getx(), 2.5);
    EXPECT_DOUBLE_EQ(center.gety(), 1.5);
}

// Тест подсчета общей площади массива фигур с базовым типом Figure<double>
TEST(ArrayTest, BaseTypeFigureDoublePointer) {
    std::array<Point<double>, 4> squarePoints = {
        Point<double>(0.0, 0.0), Point<double>(0.0, 2.0),
        Point<double>(2.0, 2.0), Point<double>(2.0, 0.0)
    };
    auto square = std::make_shared<Square<double>>(squarePoints);

    std::array<Point<double>, 4> rectPoints = {
        Point<double>(0.0, 0.0), Point<double>(0.0, 3.0),
        Point<double>(4.0, 3.0), Point<double>(4.0, 0.0)
    };
    auto rectangle = std::make_shared<Rectangle<double>>(rectPoints);

    std::array<Point<double>, 4> trapPoints = {
        Point<double>(0.0, 0.0), Point<double>(1.0, 3.0),
        Point<double>(4.0, 3.0), Point<double>(5.0, 0.0)
    };
    auto trapeze = std::make_shared<Trapeze<double>>(trapPoints);
    Array<double, Figure<double>> arr(3);
    std::cout << arr.size();
    arr.add(0, square);
    arr.add(1, rectangle);
    arr.add(2, trapeze);

    EXPECT_DOUBLE_EQ(arr.total_area(), 28.0);
}
// Тест подсчета площади массива Array с базовым типом Figure<int>
TEST(ArrayTest, BaseTypeFigureIntPointer) {
    Array<int, Figure<int>> arr(2);

    auto squarePoints = std::array<Point<int>, 4>{ 
        Point<int>(0, 0), Point<int>(0, 2), 
        Point<int>(2, 2), Point<int>(2, 0) 
    };
    auto square = std::make_shared<Square<int>>(squarePoints);

    auto rectPoints = std::array<Point<int>, 4>{ 
        Point<int>(0, 0), Point<int>(0, 3), 
        Point<int>(4, 3), Point<int>(4, 0) 
    };
    auto rectangle = std::make_shared<Rectangle<int>>(rectPoints);

    arr.add(0, square);
    arr.add(1, rectangle);

    EXPECT_DOUBLE_EQ(arr.total_area(), 16.0);
}

// Тест использования шаблона Array с типом наследника Square
TEST(ArrayTest, DerivedTypeSquare) {

    Array<int, Square<int>> arr(2);

    auto squarePoints1 = std::array<Point<int>, 4>{ 
        Point<int>(0, 0), Point<int>(0, 2), 
        Point<int>(2, 2), Point<int>(2, 0) 
    };
    Square<int> square1(squarePoints1);

    auto squarePoints2 = std::array<Point<int>, 4>{ 
        Point<int>(0, 0), Point<int>(0, 4), 
        Point<int>(4, 4), Point<int>(4, 0) 
    };
    Square<int> square2(squarePoints2);

    arr.add(0, std::make_shared<Square<int>>(square1));
    arr.add(1, std::make_shared<Square<int>>(square2));

    EXPECT_DOUBLE_EQ(arr.total_area(), 20.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}