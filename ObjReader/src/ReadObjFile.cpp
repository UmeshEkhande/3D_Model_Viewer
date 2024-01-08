#include "pch.h"
#include "ReadObjFile.h"

ReadObjFile::ReadObjFile()
{
}

ReadObjFile::~ReadObjFile()
{
}

std::vector<Point3D> ReadObjFile::getVertices()
{
    return mVertices;
}

std::vector<Point2D> ReadObjFile::getTextureCoords()
{
    return mTextureCoords;
}

std::vector<Point3D> ReadObjFile::getNormals()
{
    return mNormals;
}

std::vector<Face> ReadObjFile::getFaces()
{
    return mFaces;
}

void ReadObjFile::readObjFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }

    file.close();
}

void ReadObjFile::parseLine(const std::string& line)
{
    std::istringstream iss(line);
    std::string token;
    iss >> token;

    if (token == "v") {
        Point3D vertex;
        float x, y, z;
        iss >> x >> y >> z;
        vertex.setX(x);
        vertex.setY(y);
        vertex.setZ(z);
        mVertices.push_back(vertex);
    }
    else if (token == "vt") {
        Point2D texCoord;
        float u, v;
        iss >> u >> v;
        texCoord.setX(u);
        texCoord.setY(v);
        mTextureCoords.push_back(texCoord);
    }
    else if (token == "vn") {
        Point3D normal;
        float nx, ny, nz;
        iss >> nx >> ny >> nz;
        normal.setX(nx);
        normal.setY(ny);
        normal.setZ(nz);
        mNormals.push_back(normal);
    }
    else if (token == "f") {
        Face face;
        char slash;
        for (int i = 0; i < 3; ++i) {
            iss >> face.vIndex >> slash >> face.vtIndex >> slash >> face.vnIndex;
            mFaces.push_back(face);
        }
    }
}