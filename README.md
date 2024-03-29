# Computer Graphics Projects (QT - OpenGL Shape Viewer-Implementation of QT)
This project demonstrates a basic OpenGL window using Qt. It includes classes for reading STL files, writing data and rendering triangles. The project was configured in Qt Creator and then exported to Visual Studio using a .pro file, allowing for visualization of 3D shapes in an OpenGL window using Visual Studio. The main components of the project are:

## Classes
### Point3D:
1. Represents a 3D point with x, y, and z coordinates.
2. Provides basic functionality for representing a point in 3D space.
### Triangle:
1. Represents a triangle with three vertex indices.
2. Provides methods to access and set vertex indices.
### Triangulation:
1. Stores unique points and triangles.
2. Provides methods to access and add points and triangles.
### StlReader:
1. Reads STL files and populates a Triangulation object.
### Writer:
1. Writes data to a vector.
### TriangleWindow:
1. Inherits from: QOpenGLWindow
2. Represents the OpenGL window for rendering triangles.
   
  #### Methods:
   1. initialize(): Initializes the OpenGL window and shaders. It also reads an STL file and stores triangulated shapes.
   2. render(): Renders the OpenGL scene. It sets up the viewport, clears the buffers, and renders the triangles from the STL file using the provided shaders.

## Usage
To use the project, run the main function in main.cpp. This will create an OpenGL window showing a 3D shape loaded from an STL file.

## Output

1. Cube:
https://github.com/rashmi-kulkarni-ct402/CAGD_QT/assets/158051740/e6e580d4-b68e-4c51-be47-20b55d165dc0

2. Sphere:
https://github.com/rashmi-kulkarni-ct402/CAGD_QT/assets/158051740/3c98234a-dffe-4d1a-8cf7-52785cb8adcd

4. RandomShape:
https://github.com/rashmi-kulkarni-ct402/CAGD_QT/assets/158051740/1cfd5f9b-e18a-40f5-bdac-0ec7d67c53dd
