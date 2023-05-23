#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


class RigidBody
{
public:
    RigidBody(Vector2 position,Vector2 accel,Vector2 velo) {
        m_position = position;
        m_acceleration = accel;
        m_displacement = m_position;
        m_velocity = velo;
    }

    ~RigidBody() {}

    Vector2 GetPosition()
    {

        return m_position;
    }

    Vector2 GetVelocity()
    {
        return m_velocity;
    }

private:
    Vector2 m_position;
    Vector2 m_velocity;
    Vector2 m_acceleration;
    Vector2 m_displacement;

};

Vector2 WrapAroundScreen(Vector2 position)
{
    Vector2 outposition =
    {
       (int) (position.x + SCREEN_WIDTH) % SCREEN_WIDTH,
        (int)(position.y + SCREEN_HEIGHT)%SCREEN_HEIGHT,
    };
    return outposition;
}

Vector2 Floor(Vector2 position,Vector2& velocity)
{
    Vector2 FloorV =
    {
        position.x,
        position.y,
    };

    if (FloorV.y > SCREEN_HEIGHT - 45)
    {
        FloorV.y = SCREEN_HEIGHT - 45;
        velocity.y = 0;
    }
    return FloorV;
}




int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(60);

    Vector2 position = { 500,0 };//in px
    Vector2 velocity = { 0,0 }; //In px/s
    float maxSpeed = 1000;
    float maxAccel = 250;
    Vector2 acceleration = { 0,25 }; //In px/s/s

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
            rlImGuiBegin();

        const float dt = GetFrameTime();
    

         //   ImGui::SliderFloat2("Acceleration", &(acceleration.x), -maxAccel, maxAccel);




            Vector2 displacement;

            displacement = velocity * dt; //In px/s * s, which cancels out the seconds and is just Px. So the displacement becomes the position on screen.


            velocity = velocity + acceleration * dt;

            //position is where the object is going to be after all the relevent information is calculated


            Vector2 deltaV = acceleration * dt; // px/s/s * s = px/s
            position = position + velocity;

            //velocity = velocity + deltaV;



            position = Floor(position,velocity);

            ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
            ImGui::SliderFloat2("velocity", &(velocity.x), -maxSpeed, maxSpeed);

            DrawCircleV(GetMousePosition(), 30, BLACK);
            DrawCircleV(position, 45, RED);

        rlImGuiEnd();
        EndDrawing();
    }

    CloseWindow();
    return 0;

}