#include "Writer.h"
#include "Triangulation.h"

FileWriter::Writer::Writer() {}
FileWriter::Writer::~Writer() {}


std::vector<double> FileWriter::Writer::write(const Shapes3D::Triangulation& triangulation)
{
    // getting values of uniquePoints, triangles and assigning to new vectors -> points, triangles.
    std::vector<Geometry::Point3D> points = triangulation.uniquePoints();
    std::vector<Geometry::Triangle> triangles = triangulation.triangles();

    std::vector<double> coordinates;

    // iterating each triangle from traingles vector to write points
    for(const auto& triangle : triangles)
    {
        coordinates.push_back(points[triangle.index1()].x());
        coordinates.push_back(points[triangle.index1()].y());
        coordinates.push_back(points[triangle.index1()].z());

        coordinates.push_back(points[triangle.index2()].x());
        coordinates.push_back(points[triangle.index2()].y());
        coordinates.push_back(points[triangle.index2()].z());

        coordinates.push_back(points[triangle.index3()].x());
        coordinates.push_back(points[triangle.index3()].y());
        coordinates.push_back(points[triangle.index3()].z());
    }
    return coordinates;
}
