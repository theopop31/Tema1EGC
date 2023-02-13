#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        glm::mat3 modelMatrix;
        glm::mat3 matrix;

        float translateX, translateY; // translation for objects
        float angularStep; // wing rotation angle
        float xInit, yInit; // starting position
        float randomAngle; // takeoff angle
        float totalTime; // duck time on screen
        float scaleScore; // score scaling factor
        float rotateGun;

        // object dimentions
        float lifeRadius;
        float bodyLength, wingLength, beakLength;
        float headRadius;
        float bulletWidth, bulletLength;
        float boxLength, boxWidth;
        float squareSide;

        std::string duckState;

        // object coords
        glm::vec3 bodyMiddle;
        glm::vec3 wingStart;
        glm::vec3 headCenter;
        glm::vec3 beakMiddle;
        glm::vec3 boxCorner;
        glm::vec3 squareCenter;
        glm::vec3 gunCorner;

        int numDucks;
        int numBullets;
        int numLives;
        int tX, tY; // target translation
        int speedFactor;
        
        bool upDown; // wing rotation

    };
}   // namespace m1
