#include "TriangleWindow.h"
#include "StlReader.h"
#include "Writer.h"

#include <QMatrix4x4>
#include <QScreen>
#include <QtMath>
#include <random>


Graphics::TriangleWindow::TriangleWindow() {}
Graphics::TriangleWindow::~TriangleWindow()
{
    delete m_program;
}

static const char* vertexShaderSource =
"attribute highp vec4 posAttr;\n"
"attribute lowp vec4 colAttr;\n"
"varying lowp vec4 col;\n"
"uniform highp mat4 matrix;\n"
"void main() {\n"
"   col = colAttr;\n"
"   gl_Position = matrix * posAttr;\n"
"}\n";

static const char* fragmentShaderSource =
"varying lowp vec4 col;\n"
"void main() {\n"
"   gl_FragColor = col;\n"
"}\n";

void Graphics::TriangleWindow::initialize()
{
    // enables depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();

    // checks if shader program is linked successfully
    if (!m_program->isLinked()) {
        qWarning() << "Shader program failed to link:" << m_program->log();
        return;
    }

    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = m_program->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);

    // reads STL file and stores triangulated shapes
    FileReader::StlReader stlReader;
    stlReader.read("D:/rashmi_workspace/CAGD_QT/openglwindow/sphere.stl", mTriangulation);
}

void Graphics::TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    // clears color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.scale(0.15f);
    matrix.rotate(10.0f * m_frame / screen()->refreshRate(), 1, 0, 0);
    matrix.rotate(10.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    matrix.rotate(10.0f * m_frame / screen()->refreshRate(), 0, 0, 1);  

    m_program->setUniformValue(m_matrixUniform, matrix);

    // writes STL file in coordinates vector
    FileWriter::Writer writer;
    std::vector<double> coordinates = writer.write(mTriangulation);

    /*static const GLfloat colors[] = {
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f
    };*/

    // generates random colors
    std::random_device random;
    std::mt19937 generate(random());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    
    GLfloat* colors = new GLfloat[coordinates.size()];
    for (int i = 0; i < coordinates.size(); ++i) 
    {
        colors[i] = distribution(generate);
    }

    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, coordinates.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    // draws triangles
    glDrawArrays(GL_TRIANGLES, 0, coordinates.size() / 3);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    ++m_frame;
}