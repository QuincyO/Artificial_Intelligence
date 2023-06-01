#include "rlImGui.h"
#include "Math.h"
#include <iostream>
#include <vector>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

//        position = position + (m_fish->GetVelocity() * deltaTime) + ((acceleration * 0.5f) * deltaTime * deltaTime);
//        position = WrapAroundScreen(position);
//        m_fish->SetPosition(position);
//        m_fish->SetVelocity(m_fish->GetVelocity() + acceleration * deltaTime);



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

    Vector2 m_position;
    Vector2 m_velocity;
    Vector2 m_acceleration;
    Vector2 m_displacement;
private:

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

    void Update(float deltaTime)
    {
        m_fish->m_velocity.x += m_fish->m_acceleration.x * deltaTime;
        m_fish->m_velocity.y += m_fish->m_acceleration.y * deltaTime;

        m_fish->m_position.x += m_fish->m_velocity.x * deltaTime;
        m_fish->m_position.y += m_fish->m_velocity.y * deltaTime;
        m_fish->SetPosition(WrapAroundScreen(m_fish->GetPosition()));

    }

    

    Vector2 Seek(Vector2& targetPosition, float deltaTIme)
    {
        Vector2 desiredVelocity = Normalize(targetPosition - m_fish->GetPosition()) * m_maxSpeed;
        
        Vector2 deltaAccel = desiredVelocity - m_fish->GetVelocity();
        m_fish->SetAcceleration(deltaAccel);
        Update(deltaTIme);
        m_fish->SetAcceleration({ 0, 0 });
        return deltaAccel;
         
    }

    Vector2 GetPosition()
    {
        return m_fish->GetPosition();
    }

    void Flee(float deltaTime, Vector2 targetPosition)
    {
        Vector2 VectorToMouse =
        {
            targetPosition.x - m_fish->GetPosition().x,
           targetPosition.y - m_fish->GetPosition().y
        };
        VectorToMouse = Normalize(VectorToMouse) * -1;

        Vector2 position = m_fish->GetPosition();

        Vector2 desiredVelocity = VectorToMouse * m_maxSpeed;

        Vector2 deltaVelocity = desiredVelocity - m_fish->GetVelocity();

        Vector2 acceleration = (Normalize(deltaVelocity) * m_maxAacceleration);

        float MagOfVelo = sqrt((m_fish->GetVelocity().x * m_fish->GetVelocity().x) + (m_fish->GetVelocity().y * m_fish->GetVelocity().y));

        if (MagOfVelo > MagOfVelo)
        {
            m_fish->SetVelocity(
                m_fish->GetVelocity() * (m_maxSpeed / MagOfVelo));
        };
        position = position + (m_fish->GetVelocity() * deltaTime) + ((acceleration * 0.5f) * deltaTime * deltaTime);
        position = WrapAroundScreen(position);
        m_fish->SetPosition(position);
        m_fish->SetVelocity(m_fish->GetVelocity() + acceleration * deltaTime);

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

    Agent* Fish1 = new Agent({ 400,400 }, { 0,0 }, { 0,0 }, 200, 200);
    Agent* Fish2 = new Agent({ 400,400 }, { 0,0 }, { 0,0 }, 150, 100);
    Agent* Fish3 = new Agent({ 400,400 }, { 0,0 }, { 0,0 }, 150, 300);

    agents.push_back(Fish1);
    agents.push_back(Fish2);
    agents.push_back(Fish3);

    float timer = 0;

    Vector2 position = { 500,250 };//in px
    Vector2 velocity = { 0,0 }; //In px/s
    float maxSpeed = 10;
    float maxAccel = 150;
    Vector2 acceleration = { 0,0 }; //In px/s/s


    Vector2 mousePOS = { 0,0 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
            rlImGuiBegin();

           const float dt = GetFrameTime();
    

           if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
           {
            mousePOS = GetMousePosition();

           }
           else
           {
                mousePOS = Fish1->GetPosition();
           }

    


        Vector2 VectorToMouse =
        {
            mousePOS.x - position.x,    
           mousePOS.y - position.y
        };
        VectorToMouse = Normalize(VectorToMouse);
        Vector2 desiredVelocity = VectorToMouse * maxSpeed;

        Vector2 deltaVelocity = desiredVelocity - velocity;

        acceleration = (Normalize(deltaVelocity) * maxAccel) ;
      //  acceleration = VectorToMouse * maxAccel;

        float MagOfVelo = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));

        
            if(MagOfVelo > MagOfVelo)
            {
                velocity = velocity * (maxSpeed / MagOfVelo);
             
            }
        
        position = position + (velocity *dt) + ((acceleration * 0.5f) * dt * dt);

        velocity = velocity + acceleration * dt;
         

      ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
      ImGui::SliderFloat2("velocity", &(velocity.x), -maxSpeed, maxSpeed);
      ImGui::SliderFloat2("Acceleration", &(acceleration.x), -maxAccel, maxAccel);
      ImGui::SliderFloat("Max Acceleration", &maxAccel, 1, 1500); 
      ImGui::SliderFloat("Max Speed", &maxSpeed, -1, 1500);
            

      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      {
          for (Agent* i : agents)
          {
              i->Seek(mousePOS, dt);
          }
      }
      else {
          for (Agent* i : agents)
          {
              i->Flee(dt,position);// (dt, position);
         }
      }
      for (Agent* i : agents)
      {
          i->Draw();
      }

            position = WrapAroundScreen(position);
            DrawCircleV(mousePOS, 30, RED);
            DrawCircleV(position, 45, BLACK);


            DrawLineV(position, position + velocity, GREEN);
            DrawLineV(position, position + acceleration, RED);
            DrawLineV(position, position + desiredVelocity, PURPLE);



            timer += dt;
        rlImGuiEnd();
        EndDrawing();
    }

    CloseWindow();
    return 0;

}