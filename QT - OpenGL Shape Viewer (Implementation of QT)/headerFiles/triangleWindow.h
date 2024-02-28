#pragma once
#include "OpenGLWindow.h"
#include "Triangulation.h"

#include <QOpenGLShaderProgram>
#include <vector>

namespace Graphics
{
    class TriangleWindow : public OpenGLWindow
    {
    public:     
        using OpenGLWindow::OpenGLWindow;

        TriangleWindow();
        ~TriangleWindow();

        void initialize() override;
        void render() override;

    private:
        GLint m_posAttr = 0;
        GLint m_colAttr = 0;
        GLint m_matrixUniform = 0;

        QOpenGLShaderProgram* m_program = nullptr;
        int m_frame = 0;

        // creating triangulation object as a member variable for storing 3D shape
        Shapes3D::Triangulation mTriangulation;
    };
}