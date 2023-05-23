#include "rlImGui.h"
#include "Math.h"
#include <iostream>
#include <vector>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


class RigidBody
{
public:

    RigidBody()
        :m_position{ 0,0 },
        m_acceleration{ 0,0 },
        m_displacement{ 0,0 },
        m_velocity{ 0,0 }
    {}


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
    Agent(float maxAccel,float maxSpeed)
        :m_maxAacceleration{maxAccel},
        m_maxSpeed{ maxSpeed }
    {
        m_fish = new RigidBody();
    }

    Agent(Vector2 position, Vector2 accel, Vector2 velo,float maxAccel,float maxSpeed)
    {
        m_fish = new RigidBody(position, accel, velo);
        m_maxAacceleration = maxAccel;
        m_maxSpeed = maxSpeed;
    }

    ~Agent()
    {
        delete m_fish;
        m_fish = nullptr;
    }

    void Seek(float deltaTime,Vector2 mousePOS)
    {
        Vector2 newPosition = m_fish->GetPosition();
        Vector2 newVelo = m_fish->GetVelocity();
        Vector2 PosToMouse = mousePOS;
        PosToMouse =
        {
            PosToMouse.x = PosToMouse.x - m_fish->GetPosition().x,
            PosToMouse.y = PosToMouse.y - m_fish->GetPosition().y
        };
        PosToMouse = Normalize(PosToMouse);
        //std::cout << "Norm To Mouse:" << PosToMouse.x <<" : "<< PosToMouse.y << std::endl;

        Vector2 desiredVel = PosToMouse * m_maxSpeed;

        //std::cout << "Norm To Mouse:" << desiredVel.x <<" : "<< desiredVel.y << std::endl;
        Vector2 deltaVel = desiredVel - m_fish->GetVelocity();

        Vector2 deltaAccel = Normalize(deltaVel) * m_maxAacceleration;

        newVelo = m_fish->GetVelocity() + deltaAccel * deltaTime;

        

        newPosition = m_fish->GetPosition() + newVelo;

       // std::cout << "Norm To Mouse:" << deltaVel.x <<" : "<< deltaVel.y << std::endl;
        m_fish->SetVelocity(newVelo);
        m_fish->SetPosition(newPosition);
    }

    Vector2 GetPosition()
    {
        return m_fish->GetPosition();
    }

    void Flee(float deltaTime, Vector2 ObjectToFleeFrom)
    {
        Vector2 newPosition = m_fish->GetPosition();
        Vector2 newVelo = m_fish->GetVelocity();
        Vector2 PosToMouse = ObjectToFleeFrom;
        PosToMouse =
        {
            PosToMouse.x = PosToMouse.x - m_fish->GetPosition().x,
            PosToMouse.y = PosToMouse.y - m_fish->GetPosition().y
        };
        PosToMouse = Normalize(PosToMouse);
        //std::cout << "Norm To Mouse:" << PosToMouse.x <<" : "<< PosToMouse.y << std::endl;

        Vector2 desiredVel = PosToMouse * m_maxSpeed;

        //std::cout << "Norm To Mouse:" << desiredVel.x <<" : "<< desiredVel.y << std::endl;
        Vector2 deltaVel = desiredVel - m_fish->GetVelocity();

        Vector2 deltaAccel = Normalize(deltaVel) * m_maxAacceleration *-1;

        newVelo = m_fish->GetVelocity() + deltaAccel * deltaTime;



        newPosition = m_fish->GetPosition() + newVelo;

        // std::cout << "Norm To Mouse:" << deltaVel.x <<" : "<< deltaVel.y << std::endl;
        m_fish->SetVelocity(newVelo);
        m_fish->SetPosition(newPosition);
    }


    void Draw()
    {
        DrawCircleV(m_fish->GetPosition(), 45, RED);
    }


private:
    float m_maxSpeed; // 350 Px/s 
    float m_maxAacceleration; // 50 Px/s /s

    RigidBody* m_fish;

};










int main(void)
{
    std::vector<Agent*> agents;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(60);

    float timer = 0;

    Vector2 position = { 500,250 };//in px
    Vector2 velocity = { 0,0 }; //In px/s
    float maxSpeed = 10;
    float maxAccel = 40;
    Vector2 acceleration = { 0,25 }; //In px/s/s

    agents.push_back(new Agent(position, acceleration, velocity, 50, 5));
    agents.push_back(new Agent(100,5));
    agents.push_back(new Agent(250, 5));
    

    Agent* fish = new Agent(position, acceleration, velocity,60,50);
    agents.push_back(fish);

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
    HideCursor();
        ClearBackground(RAYWHITE);
            rlImGuiBegin();

        const float dt = GetFrameTime();
    

        Vector2 mousePOS = GetMousePosition();


            

            DrawCircleV(mousePOS, 30, BLACK);

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                for (Agent* agent : agents)
                {
                    agent->Seek(dt, mousePOS);
                }
            }
            else
            {

                    for (Agent* agent2 : agents)
                    {
                        agent2->Flee(dt, agent2->GetPosition());
                   
                    }
            }

            for (Agent* agent : agents)
            {
                agent->Draw();
            }


        rlImGuiEnd();
        EndDrawing();
    }

    CloseWindow();
    return 0;

}