#pragma once

#include <string>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "utils.h"


namespace object2DTema
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateTriangle(const std::string &name, glm::vec3 baseMiddle, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateWing(const std::string& name, glm::vec3 topLeft, float length, glm::vec3 color, bool fill, bool side);
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false, int noTriangles = 20);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 bottomLeft, float length, float width, glm::vec3 color, bool fill = false);
    Mesh* CreateSquare(const std::string& name, glm::vec3 centerP, float length, glm::vec3 color, bool fill = false);

}
