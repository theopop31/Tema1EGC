#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2DTema.h"
#include "lab_m1/Tema1/geometry.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
    xInit = 0;
    yInit = 0;
    bodyLength = 100;
    wingLength = 50;
    beakLength = 10;
    angularStep = 1.57;
    scaleX = scaleY = 0.5;
    headRadius = 20;
    upDown = true;


    geometry::TriangleCenter(cx1, cy1, wingLength, xInit, yInit);
    geometry::TriangleCenter(cx2, cy2, beakLength, xInit, yInit);
    geometry::TriangleCenter(cx3, cy3, bodyLength, xInit, yInit);

}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    

    Mesh* body = object2DTema::CreateTriangle("body", glm::vec3(xInit, yInit, 0), bodyLength, glm::vec3(0, 1, 0), true);
    AddMeshToList(body);

    Mesh* wingR = object2DTema::CreateTriangle("wingR", glm::vec3(xInit, yInit, 0), wingLength, glm::vec3(0, 0, 1), true);
    AddMeshToList(wingR);
    
    Mesh* wingL = object2DTema::CreateTriangle("wingL", glm::vec3(xInit, yInit, 0), wingLength, glm::vec3(0, 0, 1), true);
    AddMeshToList(wingL);

    Mesh* head = object2DTema::CreateCircle("head", glm::vec3(xInit, yInit, 0), headRadius, glm::vec3(1, 0, 0), true);
    AddMeshToList(head);

    Mesh* beak = object2DTema::CreateTriangle("beak", glm::vec3(xInit, yInit, 0), beakLength, glm::vec3(1, 1, 0), true);
    AddMeshToList(beak);
    
    printf("%d\n", (int)resolution.y);
    printf("%f\n", cx1);
    printf("%f\n", cy1);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
    glDisable(GL_DEPTH_TEST);
}


void Tema1::Update(float deltaTimeSeconds)
{
    

    if (angularStep < 1.39) {
        upDown = true;
    }
    if (angularStep > 1.91) {
        upDown = false;
    }

    if (upDown) {
        angularStep += deltaTimeSeconds;
    }
    else {
        angularStep = 1.39;
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    modelMatrix *= transform2D::Translate(80, scaleY * 2 * bodyLength / 2);
    modelMatrix *= transform2D::Translate(cx1, cy1);
    
    modelMatrix *= transform2D::Rotate(-angularStep);
    //modelMatrix *= transform2D::Rotate(-0.5);
    modelMatrix *= transform2D::Translate(-cx1, -cy1);
    RenderMesh2D(meshes["wingR"], shaders["VertexColor"], modelMatrix);



    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    modelMatrix *= transform2D::Translate(-30, scaleY * 2 * bodyLength / 2);
    modelMatrix *= transform2D::Translate(cx1, cy1);
    modelMatrix *= transform2D::Rotate(angularStep);
    //modelMatrix *= transform2D::Rotate(-0.5);
    modelMatrix *= transform2D::Translate(-cx1, -cy1);
    RenderMesh2D(meshes["wingL"], shaders["VertexColor"], modelMatrix);

    /*for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%f ", modelMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/

    modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    //modelMatrix *= transform2D::Translate(cx3, cy3);
    //modelMatrix *= transform2D::Translate(xInit * scaleX, yInit * scaleY);
    //modelMatrix *= transform2D::Rotate(-0.5);
    //modelMatrix *= transform2D::Translate(-xInit * scaleX,  -yInit * scaleY);
    //modelMatrix *= transform2D::Translate(-cx3, -cy3);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(scaleX * xInit + (bodyLength * scaleX) / 2 - xInit,
                                          2 * bodyLength * scaleY - scaleY * yInit);
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cx2, cy2);
    modelMatrix *= transform2D::Translate(scaleX * xInit + (bodyLength * scaleX) / 2 - xInit - beakLength / 2,
                                          2 * bodyLength * scaleY - scaleY * yInit + 2 * beakLength);
    modelMatrix *= transform2D::Translate(-cx2, -cy2);
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
