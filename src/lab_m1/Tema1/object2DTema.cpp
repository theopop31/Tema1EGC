#include "object2DTema.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2DTema::CreateTriangle(
    const std::string &name,
    glm::vec3 baseMiddle,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 middle = baseMiddle;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(middle - glm::vec3(length / 2, 0, 0), color),
        VertexFormat(middle + glm::vec3(length / 2, 0, 0), color),
        VertexFormat(middle + glm::vec3(0, 2 * length, 0), color)

    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2DTema::CreateWing(
    const std::string& name,
    glm::vec3 topLeft,
    float length,
    glm::vec3 color,
    bool fill,
    bool side)
{
    glm::vec3 corner = topLeft;

    std::vector<VertexFormat> vertices1 =
    {
        VertexFormat(corner, color),
        VertexFormat(corner - glm::vec3(0, length, 0), color),
        VertexFormat(corner + glm::vec3(2 * length, -length, 0), color)

    };

    std::vector<VertexFormat> vertices2 =
    {
        VertexFormat(corner, color),
        VertexFormat(corner - glm::vec3(0, length, 0), color),
        VertexFormat(corner - glm::vec3(2 * length, length, 0), color)

    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices1 = { 0, 1, 2 };
    std::vector<unsigned int> indices2 = { 0, 2, 1 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    if (side) {
        triangle->InitFromData(vertices1, indices1); // wing right
    }
    else {
        triangle->InitFromData(vertices2, indices2); // wing left
    }
    
    return triangle;
}



Mesh* object2DTema::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    bool fill,
    int noTriangles)
{

    std::vector<VertexFormat> vertices;
    float increment = 2.0f * PI / noTriangles;
    glm::vec3 point;

    for (float i = 0.0f; i <= 2.0f * PI; i += increment) {
        point = glm::vec3(radius * cos(i) + center.x, radius * sin(i) + center.y, 0);
        vertices.push_back(VertexFormat(point, color));
    }

    std::vector<unsigned int> indices;

    for (int i = 0; i < noTriangles; ++i) {
        indices.push_back(i);
    }

    Mesh* circle = new Mesh(name);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        circle->SetDrawMode(GL_TRIANGLE_FAN);
    }

    circle->InitFromData(vertices, indices);

    return circle;

}

Mesh* object2DTema::CreateRectangle(
    const std::string& name,
    glm::vec3 bottomLeft,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = bottomLeft;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(bottomLeft, color),
        VertexFormat(bottomLeft + glm::vec3(length, 0, 0), color),
        VertexFormat(bottomLeft + glm::vec3(length, width, 0), color),
        VertexFormat(bottomLeft + glm::vec3(0, width, 0), color)

    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    
    
    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2DTema::CreateSquare(
    const std::string& name,
    glm::vec3 centerP,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 center = centerP;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-length / 2, -length / 2, 0), color),
        VertexFormat(center + glm::vec3(length / 2, -length / 2, 0), color),
        VertexFormat(center + glm::vec3(length / 2, length / 2, 0), color),
        VertexFormat(center + glm::vec3(-length / 2, length / 2, 0), color)

    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }

    square->InitFromData(vertices, indices);
    return square;
}


