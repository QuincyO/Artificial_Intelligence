#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Vector2 WrapAroundScreen(Vector2 position)
{
    Vector2 outposition =
    {
        (int)(position.x + SCREEN_WIDTH) % SCREEN_WIDTH,
        (int)(position.y + SCREEN_HEIGHT)%SCREEN_HEIGHT,
    };
    return outposition;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(240);

    Vector2 position = { 100,100 };//in px
    Vector2 velocity = { 10,0 }; //In px/s
    float maxSpeed = 1000;
    float maxAccel = 50;
    Vector2 acceleration = { 0,50 }; //In px/s/s

    //Need three different parameters:
    /*
        Position-Location on screen, expressed as a displacement from some reference point (0,0).
            In raylib, its the top left, and we an use Pixels (px) as our unit for this.

        Velocity - Change in position over time. We can use px/sec as our unit for this

        Acceleration - Changes in velocity over time. We an use px/sec/sec as our unit for this.


    
    */


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);


        const float dt = GetFrameTime();
        Vector2 V2 = { 25,0 };
            rlImGuiBegin();

            ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
            ImGui::SliderFloat2("velocity", &(velocity.x), -maxSpeed, maxSpeed);
            ImGui::SliderFloat2("Acceleration", &(acceleration.x), -maxAccel, maxAccel);



            rlImGuiEnd();

            Vector2 displacement;
            displacement = velocity * dt; // px/s * s = px

            position = position + displacement + acceleration + 0.5f * dt * dt;

            Vector2 deltaV = acceleration * dt; // px/s/s * s = px/s

            velocity = deltaV + velocity;
            position = WrapAroundScreen(position);
            DrawCircleV(position, 45, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}