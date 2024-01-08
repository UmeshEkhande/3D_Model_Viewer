#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "pch.h"
#include "Point2D.h"
#include "Point3D.h"

struct Face {
    int vIndex, vtIndex, vnIndex;
};

class GEOMETRY_API ReadObjFile
{
public:
    ReadObjFile();
    ~ReadObjFile();

    std::vector<Point3D> getVertices();
    std::vector<Point2D> getTextureCoords();
    std::vector<Point3D> getNormals();
    std::vector<Face> getFaces();
    void readObjFile(const std::string& filename);

private:
    std::vector<Point3D> mVertices;
    std::vector<Point2D> mTextureCoords;
    std::vector<Point3D> mNormals;
    std::vector<Face> mFaces;
    void parseLine(const std::string& line);
};
