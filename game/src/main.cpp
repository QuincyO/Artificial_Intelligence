#include "rlImGui.h"
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800
#include <iostream>

using namespace std;
#include <vector>
#include <map>


//Tests comment
Vector2 centerScreen = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
Vector2 mousePOS;


class currencyButton
{
public:
    currencyButton(int coinValue, Rectangle rect,float radius,int shape)
    {
        this->value = coinValue;
        this->rect.x = rect.x;
        this->rect.y = rect.y;
        this->rect.width = rect.width;
        this->rect.height = rect.height;
        this->position.x = rect.x;
        this->position.y = rect.y;
        this->radius = radius;
        rotation = 0;
        this->shape = shape;
    };

    int Calculate(int multiplierAmount)
    {
        int tempValue = this->value;
        tempValue *= multiplierAmount;
        return tempValue;
    }

    void Draw(Color color)
    {
        if (shape == 1)
        {
            DrawCircle(position.x,position.y, radius, color);
            if (value == 200)
            {
                DrawCircle(position.x, position.y, radius * .66, GOLD);
            }
        }
        else if (shape ==2)
        {
            DrawRectangle(rect.x, rect.y, rect.width, rect.height, color); 
        }
    }

    Vector3 GetSize() const
    {
        Vector3 size = { rect.width,rect.height,radius };
        return size;
    }

    float GetXPos() const
    {
        return position.x;
    }
    float GetYPos() const
    {
        return position.y;
    }
  

    int GetValue()
    {
        return value;
    }

    void SetPosition(float xPos, float yPos)
    {
        position.x = xPos;
        position.y = yPos;
        rect.x = position.x;
        rect.y = position.y;
    }


    void SetRotation(float rotation)
    {
        this->rotation = rotation;
    }

private:
    Vector2 position;
    Rectangle rect;
    float radius;
    int value;
    int shape;
    int rotation;
};



int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");


    float buttonRadius = 50;

    Rectangle backScreen = Rectangle{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
    Rectangle readScreen = { backScreen.width * .025,backScreen.height * .11,backScreen.width * .95,130 };
    map<string, Vector3> button;

                    
    button["QUARTER"] = { 25,100,25 };
    button["LOONIE"] = { 10,0,0 };
    button["TOONIE"] = { 20,0,0 };
    button["FIVE"] = { 50,0,0 };
    button["TEN"] = { 100,0,0 };
    button["TWENTY"] = { 200,0,0 };
    button["FIFTY"] = { 500,0,0 };
    button["HUNDRED"] = { 1000,0,0 };


    button["nine"] = {};
    button["zero"] = {};
    button["equal"] = { 0,0 };
    button["minus"] = { 0,0 };
    button["plus"] = { 0,0 };
    button["multiply"] = { 0,0 };
    button["divide"] = { 0,0 };
    button["clear"] = { 0,0 };
    button["point"] = { 0,0 };

    currencyButton quarter(25, { 50,50,0,0 }, buttonRadius,1);
    currencyButton loonie(100, { 50,50,0,0 }, buttonRadius,1);
    currencyButton toonie(200, { 50,50,0,0 }, buttonRadius,1);
    currencyButton five(500, { 50,50,152,70 },0,2);
    currencyButton ten(1000, { 50,50,152,70 }, 0,2);
    currencyButton twenty(2000, { 50,50,152,70 }, 0,2);
    currencyButton fifty(5000, { 50,50,152,70 }, 0, 2);
    currencyButton hundred(10000, { 50,50,152,70 }, 0, 2);



 
    SetTargetFPS(60);

    int rotation;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawText("Hello World!", 16, 9, 20, RED);

        quarter.SetPosition(SCREEN_WIDTH * .2, SCREEN_HEIGHT * .17);
        loonie.SetPosition(quarter.GetXPos() + (loonie.GetSize().z * 2)+15, quarter.GetYPos());
        toonie.SetPosition(loonie.GetXPos() + (toonie.GetSize().z * 2) + 15, loonie.GetYPos());
        five.SetPosition(quarter.GetXPos()-(quarter.GetSize().z), quarter.GetYPos() + (five.GetSize().y*2));
        ten.SetPosition(five.GetXPos(), five.GetYPos() + (five.GetSize().y+15));
        twenty.SetPosition(ten.GetXPos(), ten.GetYPos() + (ten.GetSize().y +15));
        fifty.SetPosition(twenty.GetXPos(), twenty.GetYPos() + (twenty.GetSize().y + 15));
        hundred.SetPosition(fifty.GetXPos(), fifty.GetYPos() + (fifty.GetSize().y + 15));


        //Set Mouse Position x and y to new Var
        mousePOS = GetMousePosition();
        //Set which key is press to new Var
        int key = GetKeyPressed();


        quarter.Draw(LIGHTGRAY);
        loonie.Draw(BROWN);
        toonie.Draw(LIGHTGRAY);
        five.Draw(BLUE);
        ten.Draw(PURPLE);
        twenty.Draw(GREEN);
        fifty.Draw(RED);
        hundred.Draw(BEIGE);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}