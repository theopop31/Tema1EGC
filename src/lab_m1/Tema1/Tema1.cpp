#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2DTema.h"
#include "lab_m1/Tema1/utils.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

Tema1::Tema1()
{
    xInit = utils::getRandomNumber(250, 800);
    yInit = 0;
    
    bodyLength = 100;
    wingLength = 50;
    beakLength = 15;
    angularStep = 0;
    headRadius = 30;
    upDown = true;
    translateX = 0;
    translateY = 0;
    totalTime = 0;
    duckState = "onScreen";
    numDucks = 0;
    lifeRadius = 20;
    bulletWidth = 40;
    bulletLength = 20;
    numBullets = 3;
    numLives = 3;
    scaleScore = 0;
    speedFactor = 200;
    squareSide = 2 * bodyLength;

    bodyMiddle = glm::vec3(xInit, yInit, -1);
    wingStart = bodyMiddle + glm::vec3(0, 4.0 / 3.0 * bodyLength, -2);
    headCenter = bodyMiddle + glm::vec3(0, 2 * bodyLength, 0);
    beakMiddle = headCenter + glm::vec3(0, headRadius, 0);
    squareCenter = bodyMiddle + glm::vec3(0, bodyLength, 0);

    randomAngle = utils::getRandomNumber(-1, 1, 0.1);
    
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

    // create objects
    {
        Mesh* body = object2DTema::CreateTriangle("body", bodyMiddle, bodyLength, glm::vec3(0.5, 0.25, 0), true);
        AddMeshToList(body);

        Mesh* wingR = object2DTema::CreateWing("wingR", wingStart, wingLength, glm::vec3(0.5, 0.5, 0), true, true);
        AddMeshToList(wingR);

        Mesh* wingL = object2DTema::CreateWing("wingL", wingStart, wingLength, glm::vec3(0.5, 0.5, 0), true, false);
        AddMeshToList(wingL);

        Mesh* head = object2DTema::CreateCircle("head", headCenter, headRadius, glm::vec3(0, 0.5, 0), true);
        AddMeshToList(head);

        Mesh* beak = object2DTema::CreateTriangle("beak", beakMiddle, beakLength, glm::vec3(1, 1, 0), true);
        AddMeshToList(beak);

        Mesh* life1 = object2DTema::CreateCircle("life1", glm::vec3(resolution.x - 5 * lifeRadius - 30, resolution.y - 30, 10), lifeRadius, glm::vec3(1, 0, 0), true, 20);
        AddMeshToList(life1);

        Mesh* life2 = object2DTema::CreateCircle("life2", glm::vec3(resolution.x - 3 * lifeRadius - 20, resolution.y - 30, 10), lifeRadius, glm::vec3(1, 0, 0), true, 20);
        AddMeshToList(life2);

        Mesh* life3 = object2DTema::CreateCircle("life3", glm::vec3(resolution.x - lifeRadius - 10, resolution.y - 30, 10), lifeRadius, glm::vec3(1, 0, 0), true, 20);
        AddMeshToList(life3);

        Mesh* bullet1 = object2DTema::CreateRectangle("bullet1", glm::vec3(resolution.x - 6 * lifeRadius - 60 - 3 * bulletLength, resolution.y - 50, 10), bulletLength, bulletWidth, glm::vec3(0, 0, 1), true);
        AddMeshToList(bullet1);

        Mesh* bullet2 = object2DTema::CreateRectangle("bullet2", glm::vec3(resolution.x - 6 * lifeRadius - 50 - 2 * bulletLength, resolution.y - 50, 10), bulletLength, bulletWidth, glm::vec3(0, 0, 1), true);
        AddMeshToList(bullet2);

        Mesh* bullet3 = object2DTema::CreateRectangle("bullet3", glm::vec3(resolution.x - 6 * lifeRadius - 40 - bulletLength, resolution.y - 50, 10), bulletLength, bulletWidth, glm::vec3(0, 0, 1), true);
        AddMeshToList(bullet3);

        Mesh* scoreOutline = object2DTema::CreateRectangle("scoreOutline", glm::vec3(resolution.x - 6 * lifeRadius - 60 - 3 * bulletLength, resolution.y - 100, 10), 240, 40, glm::vec3(1, 1, 1));
        AddMeshToList(scoreOutline);

        Mesh* score = object2DTema::CreateRectangle("score", glm::vec3(resolution.x - 6 * lifeRadius - 60 - 3 * bulletLength, resolution.y - 100, 10), 2, 40, glm::vec3(1, 1, 1), true);
        AddMeshToList(score);

        Mesh* background = object2DTema::CreateRectangle("background", glm::vec3(0, 0, -10), 1280, 720, glm::vec3(0, 1, 1), true);
        AddMeshToList(background);

        Mesh* grass = object2DTema::CreateRectangle("grass", glm::vec3(0, 0, 10), 1280, 150, glm::vec3(0, 1, 0.5), true);
        AddMeshToList(grass);

        Mesh* targetInner = object2DTema::CreateCircle("targetInner", glm::vec3(0, 0, 50), 10, glm::vec3(1, 0, 0));
        AddMeshToList(targetInner);

        Mesh* targetOuter = object2DTema::CreateCircle("targetOuter", glm::vec3(0, 0, 50), 20, glm::vec3(1, 0, 0));
        AddMeshToList(targetOuter);

        Mesh* square = object2DTema::CreateSquare("square", squareCenter, squareSide , glm::vec3(0, 1, 1));
        AddMeshToList(square);

    }
    
    printf("%d\n", (int)resolution.y);
    printf("%d\n", (int)resolution.x);

}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
    
}



void Tema1::Update(float deltaTimeSeconds)
{

    modelMatrix = glm::mat3(1);
    totalTime += deltaTimeSeconds;

    if (numBullets == 0 && duckState.compare("onScreen") == 0) {
        duckState = "escaped";
        numBullets = 3;
    }

    if (totalTime > 7 && duckState.compare("shot") != 0) {
        duckState = "escaped";
        numBullets = 3;
    }

    // compute wing rotation angle
    {
        if (angularStep < 0.1) {
            upDown = true;
        }
        if (angularStep > 0.43) {
            upDown = false;
        }

        if (upDown) {
            angularStep += deltaTimeSeconds;
        }
        else {
            angularStep = 0;
        }
    }

   // reflection off the sides of the screen
    if (duckState.compare("onScreen") == 0) {
        
        if (headCenter.x + translateX <= 30 || headCenter.x + translateX >= window->GetResolution().x) {
            randomAngle = -randomAngle;
        }

        if (headCenter.y + translateY <= 0 || headCenter.y + translateY >= window->GetResolution().y) {
            randomAngle = PI - randomAngle;
        }
       
    }

    if (duckState.compare("escaped") == 0) {
        randomAngle = 0; // escape straight up
        // if duck is no longer on screen, reset it
        if (bodyMiddle.y + translateY > 720) {
            numLives -= 1; // lost a life
            ++numDucks; // counts number of ducks that were on screen
            // increase speed factor, max speed is limited
            if (numDucks % 5 == 0 && speedFactor < 500) {
                speedFactor += 100;
            }
            duckState = "onScreen";
            totalTime = 0;
            translateY = 0;
            translateX = utils::getRandomNumber(100, 500);
            randomAngle = utils::getRandomNumber(-1, 1, 0.1); 
        }
    }

    if (duckState.compare("shot") == 0) {
        randomAngle = PI; // fall straight down
        // if duck is no longer on screen, reset it
        if (bodyMiddle.y + translateY < -bodyLength) {
            numBullets = 3;
            duckState = "onScreen";
            totalTime = 0;
            translateY = 0;
            translateX = utils::getRandomNumber(100, 500);
            randomAngle = utils::getRandomNumber(-1, 1, 0.1);
        }
    }

    // construct transformation matrix
    translateX -= speedFactor * deltaTimeSeconds * sinf(randomAngle);
    translateY += speedFactor * deltaTimeSeconds * cosf(randomAngle);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(bodyMiddle.x, bodyMiddle.y + bodyLength);
    modelMatrix *= transform2D::Rotate(randomAngle);
    modelMatrix *= transform2D::Translate(-bodyMiddle.x, -bodyMiddle.y - bodyLength);

    // render Objects
    {
        // render objects that don't require extra transformations
        RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["boundingBox"], shaders["VertexColor"], modelMatrix);

        // render wings
        {
            modelMatrix *= transform2D::Translate(wingStart.x, wingStart.y);
            modelMatrix *= transform2D::Rotate(angularStep);
            modelMatrix *= transform2D::Translate(-wingStart.x, -wingStart.y);
            RenderMesh2D(meshes["wingR"], shaders["VertexColor"], modelMatrix);

            modelMatrix *= transform2D::Translate(wingStart.x, wingStart.y);
            modelMatrix *= transform2D::Rotate(-2 * angularStep);
            modelMatrix *= transform2D::Translate(-wingStart.x, -wingStart.y);
            RenderMesh2D(meshes["wingL"], shaders["VertexColor"], modelMatrix);
        }

        // render background and grass
        modelMatrix = glm::mat3(1); // reset transformation matrix
        RenderMesh2D(meshes["background"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);


        // render lives and bullets accordingly
        {
            string aux = "life";
            for (int i = 1; i <= numLives; ++i) {
                RenderMesh2D(meshes[aux + std::to_string(i)], shaders["VertexColor"], modelMatrix);
            }
            aux = "bullet";
            for (int i = 1; i <= numBullets; ++i) {
                RenderMesh2D(meshes[aux + std::to_string(i)], shaders["VertexColor"], modelMatrix);
            }
  
        }

        // render score
        {
            RenderMesh2D(meshes["scoreOutline"], shaders["VertexColor"], modelMatrix);
            // scale score around bottom left corner on OX axis only, then translate it backwards to keep it in place
            modelMatrix *= transform2D::Translate(-scaleScore, 0);
            modelMatrix *= transform2D::Translate(window->GetResolution().x - 6 * lifeRadius - 60 - 3 * bulletLength - 1, window->GetResolution().y - 120);
            modelMatrix *= transform2D::Scale(scaleScore, 1);
            modelMatrix *= transform2D::Translate(-window->GetResolution().x + 6 * lifeRadius + 60 + 3 * bulletLength + 1, -window->GetResolution().y + 120);
            RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);
        }

        // render axis aligned bounding box
        modelMatrix = glm::mat3(1);
        matrix *= transform2D::Translate(translateX, translateY);
        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

        // render simple target
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(tX, tY);
        RenderMesh2D(meshes["targetInner"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["targetOuter"], shaders["VertexColor"], modelMatrix);

    } 
     
}


void Tema1::FrameEnd()
{
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
    // target translation
    tX = mouseX;
    tY = window->GetResolution().y - mouseY;

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        
        if (numBullets > 0 && duckState.compare("onScreen") == 0) {
            --numBullets; // use bullet
            // check if mouse is inside bounding box
            if (utils::isInBox(mouseX, window->GetResolution().y - mouseY, squareCenter, squareSide, translateX, translateY )) {                
                printf("It's a hit!\n");
                duckState = "shot";
                ++numDucks;
                if (numDucks % 5 == 0 && speedFactor < 500) {
                    speedFactor += 150; // increase speed
                }
                scaleScore += 10; // increase score
            }
            else {
                printf("It's a miss!\n");
            }
        }
        
    }

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
