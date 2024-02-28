#include "Point3D.h"
#include "Triangle.h"
#include "Triangulation.h"

#include <vector>

Shapes3D::Triangulation::Triangulation() {}

Shapes3D::Triangulation::~Triangulation() {}

// vector for storing unique points
std::vector<Geometry::Point3D> Shapes3D::Triangulation::uniquePoints() const
{
    return mUniquePoints;
}

// vector for storing triangles
std::vector<Geometry::Triangle> Shapes3D::Triangulation::triangles() const
{
    return mTriangles;
}

// adds a point to mUniquePoints vector
void Shapes3D::Triangulation::addUniquePointToTriangulation(const Geometry::Point3D inPoint)
{
    mUniquePoints.push_back(inPoint);
}

// adds a triangle to mTriangles vector
void Shapes3D::Triangulation::addTriangleToTriangulation(const Geometry::Triangle inTriangle)
{
    mTriangles.push_back(inTriangle);
}
