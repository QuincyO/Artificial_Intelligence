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
        selected = false;
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
        //Shape 1 is a circle
        if (shape == 1)
        {
            //Drawing Cirle to Represent the coins. #1
            DrawCircle(position.x,position.y, radius, color);
            if (value == 200)
            {
                //This Circle is soley for the toonie, to have the smaller circle inside of the larger circle
                DrawCircle(position.x, position.y, radius * .66, GOLD);
            }

        }
        //Shape 2 is a Rectangle
        else if (shape ==2)
        {
            //Drawing Rectangle to represent the bills #2
            DrawRectangle(rect.x, rect.y, rect.width, rect.height, color); 
        }

        if (selected && shape==2 )
        {
            //Drawing an outline around the bills #3
            DrawRectangleLinesEx(this->rect, 5, BLACK);
        }
        else if (selected && shape == 1)
        {
            //Drawing Outline around the coins #4
            DrawRing(this->position, this->radius+1, this->radius - 5, 0, 360, 100, BLACK);

        }
    }

    void IsOn()
    {
        selected = true;
    }

    void IsOff()
    {
        selected = false;
    }



    Vector3 GetSize() const
    {
        Vector3 size = { rect.width,rect.height,radius };
        return size;
    }
    Vector2 GetCenter() const
    {
        return position;
    }

    float GetRadius() const
    {
        return radius;
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

    Rectangle ReturnRect() const
    {
        return rect;
    }

private:
    Vector2 position;
    Rectangle rect;
    bool selected;
    float radius;
    int value;
    int shape;
    int rotation;
};

class ADD_MINUS_Button
{
public:

    ADD_MINUS_Button()
    {
        this->multiplier = 0;
        this->position = {};
        this->v1 = v2 = v3 = {};
    }

    void Draw()
    {
       // DrawTriangle()
    }
private:
    Vector2 position;
    Vector2 v1;
    Vector2 v2;
    Vector2 v3;
    int multiplier;

};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");


    float buttonRadius = 50;

    Rectangle backScreen = Rectangle{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
    Rectangle readScreen = { backScreen.width * .025,backScreen.height * .11,backScreen.width * .95,130 };
    vector<currencyButton> buttons;


    currencyButton quarter(25, { 50,50,0,0 }, buttonRadius,1);
    currencyButton loonie(100, { 50,50,0,0 }, buttonRadius,1);
    currencyButton toonie(200, { 50,50,0,0 }, buttonRadius,1);
    currencyButton five(500, { 50,50,152,70 },0,2);
    currencyButton ten(1000, { 50,50,152,70 }, 0,2);
    currencyButton twenty(2000, { 50,50,152,70 }, 0,2);
    currencyButton fifty(5000, { 50,50,152,70 }, 0, 2);
    currencyButton hundred(10000, { 50,50,152,70 }, 0, 2);

    //Hiding Cursor so my mouse is represented by the circle #5
    HideCursor();



    quarter.SetPosition(SCREEN_WIDTH * .2, SCREEN_HEIGHT * .17);
    loonie.SetPosition(quarter.GetXPos() + (loonie.GetSize().z * 2) + 15, quarter.GetYPos());
    toonie.SetPosition(loonie.GetXPos() + (toonie.GetSize().z * 2) + 15, loonie.GetYPos());
    five.SetPosition(quarter.GetXPos() - (quarter.GetSize().z), quarter.GetYPos() + (five.GetSize().y * 2));
    ten.SetPosition(five.GetXPos(), five.GetYPos() + (five.GetSize().y + 15));
    twenty.SetPosition(ten.GetXPos(), ten.GetYPos() + (ten.GetSize().y + 15));
    fifty.SetPosition(twenty.GetXPos(), twenty.GetYPos() + (twenty.GetSize().y + 15));
    hundred.SetPosition(fifty.GetXPos(), fifty.GetYPos() + (fifty.GetSize().y + 15));
 

    buttons.push_back(quarter);
    buttons.push_back(loonie);
    buttons.push_back(toonie);
    buttons.push_back(five);
    buttons.push_back(ten);
    buttons.push_back(twenty);
    buttons.push_back(fifty);
    buttons.push_back(hundred);
    SetTargetFPS(60);

    int rotation;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);




        //Set Mouse Position x and y to new Var #6
        mousePOS = GetMousePosition();


        //Set which key is press to new Var #7
        int key = GetKeyPressed();
            

        switch (key)
        {
        case KEY_ONE:
            for (currencyButton& button : buttons)
            {
                button.IsOff();
            }
                buttons[3].IsOn();

            break;
        case KEY_TWO:
            for (currencyButton& button : buttons)
            {
                button.IsOff();
            }
            buttons[4].IsOn();
            break;
        case KEY_THREE:
            for (currencyButton& button : buttons)
            {
                button.IsOff();
            }
            buttons[5].IsOn();
            break;
        case KEY_FOUR:
            for (currencyButton& button : buttons)
            {
                button.IsOff();
            }
            buttons[6].IsOn();
            break;
        case KEY_FIVE:
            for (currencyButton& button : buttons)
            {
                button.IsOff();
            }
            buttons[7].IsOn();
            break;
        }



        buttons[0].Draw(LIGHTGRAY);
        buttons[1].Draw(BROWN);
        buttons[2].Draw(LIGHTGRAY);
        buttons[3].Draw(BLUE);
        buttons[4].Draw(PURPLE);
        buttons[5].Draw(GREEN);
        buttons[6].Draw(RED);
        buttons[7].Draw(BEIGE);

        for (int i = 0; i<buttons.size();i++)
        {
               //Checking if my mouse is hoving over a Rectangle or Circle. #8 and #9
            if (CheckCollisionCircles(buttons[i].GetCenter(), buttons[i].GetRadius(), mousePOS, 15) || CheckCollisionCircleRec(mousePOS,15,buttons[i].ReturnRect()))
            {
                //Filling in the circle of my mouse when the house is hoving over one of the objects. #10
                DrawCircleV(mousePOS, 10, BLACK);

                    //Checking if I clicked on one of the buttons, to selected and add an outline over the object. #11
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    for (currencyButton& button : buttons)
                    {
                        button.IsOff();
                    }
                    buttons[i].IsOn();
                }
            }
            else
            {
                //Drawing a circle outline at my mouse every frame, if im not hovering over one of the objects. #12
                DrawCircleLines(mousePOS.x, mousePOS.y, 10, BLACK);
            }
        }
        Vector2 v1 = { (five.GetXPos() - 30)-10,(five.GetYPos()) };
        Vector2 v2 = { v1.x-30,five.GetYPos()+five.GetSize().y};
        Vector2 v3 = { v1.x + 30,v2.y };


        //Testing Drawing a triangle
        DrawTriangle(v1,v2,v3,BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}