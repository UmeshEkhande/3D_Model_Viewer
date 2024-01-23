// Triangle class's Function's unit Testing

#include "pch.h"
#include "Triangle.h"
#include "gtest/gtest.h"
#include "Point3D.h"

Point3D p1(1.0f, 2.0f, 3.0f);
Point3D p2(4.0f, 5.0f, 6.0f);
Point3D p3(7.0f, 8.0f, 9.0f);

Triangle triangle(p1, p2, p3);

// Unit Testing of Constructor and Getters
TEST(TriangleTest, ConstructorAndGetters) {


    EXPECT_EQ(triangle.p1(), p1);
    EXPECT_EQ(triangle.p2(), p2);
    EXPECT_EQ(triangle.p3(), p3);
    EXPECT_EQ(triangle.normal(), Point3D(0, 0, 0)); 
}

// Unit Testing of SetNoraml Function
TEST(TriangleTest, SetNormal) {
    Point3D normal(1.0f, 2.0f, 3.0f);
    triangle.setNormal(normal);
    EXPECT_EQ(triangle.normal(), normal);
}