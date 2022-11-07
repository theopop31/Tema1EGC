#include "object2DTema.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2DTema::CreateTriangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length / 2, 2 * length, 0), color)

    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }

    triangle->InitFromData(vertices, indices);
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


