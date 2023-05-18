#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(240);

    Vector2 position = { 100,100 };
    Vector2 velocity = { 10,0 };
    float maxSpeed = 1000;

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

            rlImGuiBegin();

            ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
            ImGui::SliderFloat2("velocity", &(velocity.x), -maxSpeed, maxSpeed);



            rlImGuiEnd();

            Vector2 displacement;
            displacement = velocity * dt;

            position = position + displacement;


            DrawCircleV(position, 45, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}