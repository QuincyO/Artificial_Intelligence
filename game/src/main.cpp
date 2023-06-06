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

bool CheckCollisionLineCircle(Vector2 agentPosition,Vector2 obstaclePosition,Vector2 lineToCheckAgainst,float circleRadius)
{
    Vector2 nearestPointC = NearestPoint(agentPosition, agentPosition + lineToCheckAgainst, obstaclePosition);

    float distanceFromObstacleToPoint = Distance(nearestPointC, obstaclePosition);
    return  (distanceFromObstacleToPoint <= circleRadius);
}

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




float AngleFromVector(Vector2 direction)
{
    float angle = atan2f(direction.y, direction.x) * RAD2DEG;
    angle = fmodf(angle + 360, 360.0f);
    return angle;
}

Vector2 VectorFromAngleDegrees(float angleDegrees)
{
    return Vector2{ cosf(angleDegrees * DEG2RAD),sinf(angleDegrees * DEG2RAD) };
}



int main(void)
{
    std::vector<Agent*> agents;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(60);

    float timer = 0;

    const float radius = 65.f;
    const float whiskerLength = 300;


    Vector2 position = { SCREEN_WIDTH/2,SCREEN_HEIGHT/2 };//in px
    Vector2 velocity = { 0,0 }; //In px/s
    float maxSpeed = 10;
    float maxAccel = 150;
    Vector2 acceleration = { 0,0 }; //In px/s/s
    Vector2 direction = { 0.0f,1.0f };


    Vector2 mousePOS = { 0,0 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
            rlImGuiBegin();

           const float dt = GetFrameTime();
    


            mousePOS = GetMousePosition();
    


     //    direction =
     //    {
     //        mousePOS.x - position.x,    
     //       mousePOS.y - position.y
     //    };
        
        direction = Normalize(direction);

        float angle = AngleFromVector(direction);

        float wiskerAngleLeft = fmodf(angle-30+360,360.0f);
        float wiskerAngleRight = fmodf(angle+30+360,360.0f);

        Vector2 wiskerLeft = VectorFromAngleDegrees(wiskerAngleLeft) * whiskerLength;
        Vector2 wiskerRight = VectorFromAngleDegrees(wiskerAngleRight) * whiskerLength;




    //  ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
    //  ImGui::SliderFloat2("velocity", &(velocity.x), -maxSpeed, maxSpeed);
    //  ImGui::SliderFloat2("Acceleration", &(acceleration.x), -maxAccel, maxAccel);
    //  ImGui::SliderFloat("Max Acceleration", &maxAccel, 1, 1500); 
    //  ImGui::SliderFloat("Max Speed", &maxSpeed, -1, 1500);
            





            position = WrapAroundScreen(position);
            DrawCircleV(mousePOS, radius, RED);
            DrawCircleV(position, 25, BLUE);
            

            DrawLineV(position, position + Vector2{100,0}, BLACK);
            DrawLineV(position, position + direction *100, PINK);
            DrawLineV(position, position + wiskerLeft, (rightCollision) ? RED : GREEN);
            DrawLineV(position, position + wiskerRight, GREEN);
            DrawCircleV(nearestPointC, 5, BLACK);

            DrawText(TextFormat("Angle: %f.1", angle),200, position.y + 45, 20, RED);
            DrawText(TextFormat("Wisker Angle Green : %f.1", wiskerAngleLeft),200, position.y + 65, 20, RED);
            DrawText(TextFormat("Wisker Angle Blue : %f.1", wiskerAngleRight),200, position.y + 85, 20, RED);

          //  DrawLineV(position, position + acceleration, RED);
          //  DrawLineV(position, position + desiredVelocity, PURPLE);



        timer += dt;
        rlImGuiEnd();
        EndDrawing();
    }

    CloseWindow();
    return 0;

}