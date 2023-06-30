#include "rlImGui.h"
#include "Math.h"
#include "TileMap.h"
#include <iostream>
#include <vector>
#include "Pathfinder.h"


//        position = position + (m_fish->GetVelocity() * deltaTime) + ((acceleration * 0.5f) * deltaTime * deltaTime);
//        position = WrapAroundScreen(position);
//        m_fish->SetPosition(position);
//        m_fish->SetVelocity(m_fish->GetVelocity() + acceleration * deltaTime);

bool CheckCollisionLineCircle(Vector2 agentPosition,Vector2 obstaclePosition,Vector2 lineToCheckAgainst,float circleRadius)
{
    Vector2 NearestPointOnVector = NearestPoint(agentPosition, agentPosition + lineToCheckAgainst, obstaclePosition);

    float distanceFromObstacleToPoint = Distance(NearestPointOnVector, obstaclePosition);
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

struct RigidBody
{
    Vector2 pos = {SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
    Vector2 accel = {};
    Vector2 velo = {};
    Vector2 dir = {};
    float rotation;
    float angularSpeed;
};






int main(void)
{
    bool startSelected = false;
    bool endSelected = false;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(60);
    Tilemap map("../game/assets/p1_walk01.png");
    map.player.SetSize(64, 64);
    float timer = 0;
    TileCoord startNode = {};
    TileCoord endNode = {};
    int wallChance = 20;


    map.RegnerateLevel(wallChance);
    bool imGui = false;




    Vector2 mousePOS = { 0,0 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
            rlImGuiBegin();

            if (IsKeyPressed(KEY_GRAVE)) imGui = !imGui;
            if (imGui)
            {
                ImGui::SliderInt("Wall%", &wallChance, 0, 100, NULL);
                ImGui::Text("Start Coord = %d : %d",startNode.x , startNode.y);
                ImGui::Text("End Coord = %d : %d",endNode.x , endNode.y);
                if (ImGui::Button("Regenerate Level"))
                {
                    map.RegnerateLevel(wallChance);
                }
            }

            if (startSelected == false)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    startNode = map.ScreenPosToTilePos(GetMousePosition());
                    startSelected = true;
                }

            }

             else if (endSelected == false)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    endNode = map.ScreenPosToTilePos(GetMousePosition());
                    endSelected = true;
                }

            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                startNode = {};
                endNode = {};
                startSelected = false;
                endSelected = false;
            }


            Pathfinder brain(&map, startNode, endNode);

            brain.GetLowestCostFromNeihbors();

            if (IsKeyPressed(KEY_W)) map.MoveSpriteUp();
            if (IsKeyPressed(KEY_S)) map.MoveSpriteDown();
            if (IsKeyPressed(KEY_A)) map.MoveSpriteLeft();
            if (IsKeyPressed(KEY_D)) map.MoveSpriteRight();
            




        const float dt = GetFrameTime();
        mousePOS = GetMousePosition();
        map.DrawTiles();
        map.DrawBorders();
        map.DrawNodes();
        map.DrawSprite();



        timer += dt;
        rlImGuiEnd();
        EndDrawing();
    }

    CloseWindow();
    //If you are curious about what numbers the hash function produces, try puttin this block of test code in main
    return 0;

}