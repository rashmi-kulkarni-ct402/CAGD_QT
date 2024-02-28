#pragma once
#include "Point3D.h"
#include "Triangle.h"

#include <vector>

namespace Shapes3D
{
    class Triangulation
    {
    public:
        Triangulation();
       ~Triangulation();

        std::vector<Geometry::Point3D> uniquePoints() const;
        std::vector<Geometry::Triangle> triangles() const;
        void addUniquePointToTriangulation(const Geometry::Point3D inPoint);
        void addTriangleToTriangulation(const Geometry::Triangle inTriangle);

    private:
        std::vector<Geometry::Point3D> mUniquePoints;
        std::vector<Geometry::Triangle> mTriangles;
    };
}