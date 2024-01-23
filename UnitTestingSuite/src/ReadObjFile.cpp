// ReadObjFile class's function's unit Testing

#include "pch.h"
#include "ReadObjFile.h"
#include "gtest/gtest.h"
#include <sstream>

ReadObjFile objFile;

// Unit Testing of Default Construcotr adn changing all the member variables are empty
TEST(ReadObjFileTest, DefaultConstructor) {
   
    EXPECT_TRUE(objFile.getVertices().empty());
    EXPECT_TRUE(objFile.getTextureCoords().empty());
    EXPECT_TRUE(objFile.getNormals().empty());
    EXPECT_TRUE(objFile.getFaces().empty());

}

// Unit Testing of ReadObjFile File
TEST(ReadObjFileTest, ReadObjFileAndAccessData) {
    const std::string objContent =
        "v 1.0 2.0 3.0\n"
        "vt 0.1 0.2\n"
        "vn 0.3 0.4 0.5\n"
        "f 1/1/1 2/2/2 3/3/3\n";

    std::istringstream objStream(objContent);

    objFile.readObjFileStream(objStream);


    EXPECT_FALSE(objFile.getVertices().empty());
    EXPECT_FALSE(objFile.getTextureCoords().empty());
    EXPECT_FALSE(objFile.getNormals().empty());
    EXPECT_FALSE(objFile.getFaces().empty());


    EXPECT_FLOAT_EQ(objFile.getVertices()[0].x(), 1.0f);
    EXPECT_FLOAT_EQ(objFile.getVertices()[0].y(), 2.0f);
    EXPECT_FLOAT_EQ(objFile.getVertices()[0].z(), 3.0f);

}

