#include "rlImGui.h"
#include "Math.h"
#include <iostream>
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

    void SetVelocity(Vector2 Velo)
    {
        m_velocity = Velo;
    }

    void SetPosition(Vector2 position)
    {
        m_position = position;
    }

private:
    Vector2 m_position;
    Vector2 m_velocity;
    Vector2 m_acceleration;
    Vector2 m_displacement;

};

class Agent
{
public:
    Agent(Vector2 position, Vector2 accel, Vector2 velo)
    {
        m_fish = new RigidBody(position, accel, velo);

    }

    ~Agent()
    {
        delete m_fish;
        m_fish = nullptr;
    }

    void Update(float deltaTime)
    {
        m_fish->GetPosition();
    }


private:
    float m_maxSpeed = 350; // 350 Px/s 
    float m_maxAacceleration; // 50 Px/s /s

    RigidBody* m_fish;

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

    float timer = 0;

    Vector2 position = { 500,250 };//in px
    Vector2 velocity = { 0,0 }; //In px/s
    float maxSpeed = 25;
    float maxAccel = 50;
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
    

        Vector2 circle2Pos = { 750,250 };



            Vector2 displacement;

            displacement = velocity * dt; //In px/s * s, which cancels out the seconds and is just Px. So the displacement becomes the position on screen.
            //velocity = velocity + acceleration * dt;

            //position is where the object is going to be after all the relevent information is calculated
            Vector2 deltaV = acceleration * dt; // px/s/s * s = px/s
          //  position = position + velocity;

            
            //velocity = velocity + deltaV;
         //   position = Floor(position,velocity);





            Vector2 posToAgent =
            {
                GetMousePosition().x - position.x,
                GetMousePosition().y - position.y
            };

            posToAgent = Normalize(posToAgent);
            
            Vector2 desiredVel = posToAgent * maxSpeed;

            Vector2 deltaVel = desiredVel - velocity;

            Vector2 DeltaAccel = Normalize(deltaVel) * maxAccel;

            velocity = velocity + DeltaAccel * dt;

            position = position + velocity;

            

            DrawCircleV(circle2Pos, 30, BLACK);
            DrawCircleV(position, 45, RED);

        rlImGuiEnd();
        EndDrawing();
    }

    CloseWindow();
    return 0;

}