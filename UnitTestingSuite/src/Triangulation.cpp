// Triangulation class's Function's unit Testing

#include "pch.h"
#include "Triangulation.h"
#include "gtest/gtest.h"

// Unit Testing of constructor and GetTriangles Function
TEST(TriangulationTest, ConstructorAndGetTriangles) {

    Triangle triangle1(Point3D(1.0f, 2.0f, 3.0f), Point3D(4.0f, 5.0f, 6.0f), Point3D(7.0f, 8.0f, 9.0f));
    Triangle triangle2(Point3D(10.0f, 11.0f, 12.0f), Point3D(13.0f, 14.0f, 15.0f), Point3D(16.0f, 17.0f, 18.0f));

    std::vector<Triangle> triangles = { triangle1, triangle2 };
    Triangulation triangulation(triangles);

    EXPECT_EQ(triangulation.getTriangles(), triangles);
}