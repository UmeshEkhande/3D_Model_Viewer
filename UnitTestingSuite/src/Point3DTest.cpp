// Point3D class's Functions Testing

#include "pch.h"
#include "Point3D.h"
#include "gtest/gtest.h"

// Unit Testing of default constructor
TEST(Point3DTest, DefaultConstructor) {
    Point3D point;
    EXPECT_FLOAT_EQ(point.x(), 0.0f);
    EXPECT_FLOAT_EQ(point.y(), 0.0f);
    EXPECT_FLOAT_EQ(point.z(), 0.0f);
}

// Unit Testing of Parametrized Constructor
TEST(Point3DTest, ParameterizedConstructor) {
    Point3D point(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(point.x(), 1.0f);
    EXPECT_FLOAT_EQ(point.y(), 2.0f);
    EXPECT_FLOAT_EQ(point.z(), 3.0f);
}

// Unit Testing of Setters and Getters
TEST(Point3DTest, SettersAndGetters) {
    Point3D point;

    point.setX(3.0f);
    point.setY(4.0f);
    point.setZ(5.0f);

    EXPECT_FLOAT_EQ(point.x(), 3.0f);
    EXPECT_FLOAT_EQ(point.y(), 4.0f);
    EXPECT_FLOAT_EQ(point.z(), 5.0f);
}

