#include "rlImGui.h"
#include "Math.h"
#include <iostream>
#include <vector>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


Vector2 WrapAroundScreen(Vector2 position)
{
    Vector2 outPosition =
    {
        fmodf(position.x + SCREEN_WIDTH,SCREEN_WIDTH),
        fmodf(position.y + SCREEN_HEIGHT,SCREEN_HEIGHT)
    };
    return outPosition;
}

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

    Vector2 GetAcceleration()
    {
        return m_acceleration;
    }

    void SetVelocity(Vector2 Velo)
    {
        m_velocity = Velo;
    }

    void SetPosition(Vector2 position)
    {
        m_position = position;
    }

    void SetAcceleration(Vector2 Accel)
    {
        m_acceleration = Accel;
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

    Vector2 Update(float dt,Vector2& pos,Vector2& accel,Vector2& velo)
    {
        Vector2 velocity = velo;
        Vector2 position = pos;
        Vector2 accleration = accel;
        Vector2 displacement = velocity * dt;

        position = position + displacement + ((accleration*0.5f) * dt * dt);

        velocity = velocity + accleration * dt;


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
        desiredVel.x = Clamp(desiredVel.x, -m_maxSpeed, m_maxSpeed);
        desiredVel.y = Clamp(desiredVel.y, -m_maxSpeed, m_maxSpeed);

        //std::cout << "Norm To Mouse:" << desiredVel.x <<" : "<< desiredVel.y << std::endl;
        Vector2 deltaVel = desiredVel - m_fish->GetVelocity();

        Vector2 deltaAccel = Normalize(deltaVel) * m_maxAacceleration;

        newVelo = m_fish->GetVelocity() + deltaAccel * deltaTime;

        

        newPosition = m_fish->GetPosition() + newVelo;

       // std::cout << "Norm To Mouse:" << deltaVel.x <<" : "<< deltaVel.y << std::endl;
        deltaAccel.x = Clamp(deltaAccel.x, -m_maxAacceleration, m_maxAacceleration);
        deltaAccel.y = Clamp(deltaAccel.x, -m_maxAacceleration, m_maxAacceleration);
        m_fish->SetAcceleration(deltaAccel);
        m_fish->SetVelocity(newVelo);
        newPosition = WrapAroundScreen(newPosition);
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
        desiredVel.x = Clamp(desiredVel.x, -m_maxSpeed, m_maxSpeed);
        desiredVel.y = Clamp(desiredVel.y, -m_maxSpeed, m_maxSpeed);
        //std::cout << "Norm To Mouse:" << desiredVel.x <<" : "<< desiredVel.y << std::endl;
        Vector2 deltaVel = desiredVel - m_fish->GetVelocity();

        Vector2 deltaAccel = Normalize(deltaVel) * m_maxAacceleration *-1;

        newVelo = m_fish->GetVelocity() + deltaAccel * deltaTime;



        newPosition = m_fish->GetPosition() + newVelo;

        // std::cout << "Norm To Mouse:" << deltaVel.x <<" : "<< deltaVel.y << std::endl;
        deltaAccel.x = Clamp(deltaAccel.x, -m_maxAacceleration, m_maxAacceleration);
        deltaAccel.y = Clamp(deltaAccel.x, -m_maxAacceleration, m_maxAacceleration);
        Clamp(newPosition.y, -m_maxAacceleration, m_maxAacceleration);
        m_fish->SetAcceleration(deltaAccel);
        m_fish->SetVelocity(newVelo);
        newPosition = WrapAroundScreen(newPosition);
        m_fish->SetPosition(newPosition);
       
    }


    void Draw()
    {

            DrawCircleV(m_fish->GetPosition(), 45, RED);
            DrawLineV(m_fish->GetPosition(), m_fish->GetPosition() + m_fish->GetVelocity(), BLACK);
            DrawLineV(m_fish->GetPosition(), m_fish->GetPosition() + m_fish->GetAcceleration(), GREEN);

        
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
    Vector2 acceleration = { 0,10 }; //In px/s/s

    //agents.push_back(new Agent(position, acceleration, velocity, 5, 5));
    agents.push_back(new Agent(5,10));
    agents.push_back(new Agent(7, 10));
    

    Agent* fish = new Agent(position, acceleration, velocity,3,100);
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
                for (Agent* agent : agents)
                {
                    agent->Flee(dt, agent->GetPosition());
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