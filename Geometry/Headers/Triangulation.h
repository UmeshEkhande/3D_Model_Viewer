#pragma once
#include <vector>
#include "Triangle.h"
#include "pch.h"

    class GEOMETRY_API Triangulation
    {
    public:
        Triangulation(std::vector<Triangle> triangles);
        ~Triangulation();
        std::vector<Triangle> getTriangles() const;
    private:
        std::vector<Triangle> mTriangles;
    };

