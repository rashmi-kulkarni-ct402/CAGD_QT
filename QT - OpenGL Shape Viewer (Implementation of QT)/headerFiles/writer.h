#pragma once
#include "Triangulation.h"

#include <vector>

namespace FileWriter
{
    class Writer
    {
    public:
        Writer();
        ~Writer();

        std::vector<double> write(const Shapes3D::Triangulation& triangulation);

    };
}