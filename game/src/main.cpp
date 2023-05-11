#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


//Tests comment
Vector2 Third = { SCREEN_WIDTH / 3,SCREEN_HEIGHT / 3 };
Vector2 mousePOS;
Vector2 centerScreen = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        mousePOS = GetMousePosition();
        //Draw Pixel??
        DrawPixel(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RED);

        //DrawPixelV
        DrawPixelV(Third, BLUE);
        
        //DrawLine
       // DrawLineEx(GetMousePosition(), centerScreen, 10, DARKPURPLE);
    
        /* void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);
        void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);                   // Draw a line using cubic-bezier curves in-out
        void DrawLineBezierQuad(Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thick, Color color); // Draw line using quadratic bezier curves with a control point
        void DrawLineBezierCubic(Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thick, Color color); // Draw line using cubic bezier curves with 2 control points
        */
            //DrawLineBezier(mousePOS, centerScreen, 10, DARKPURPLE);
            //
            //DrawLineBezierQuad(mousePOS, centerScreen, { 200,200 }, 10, DARKPURPLE);
            //
            //DrawLineBezierCubic(mousePOS, centerScreen, { 100,300 }, { 100,700 }, 10, DARKPURPLE);
     //***********************************************************************************************************************************************************
        
            
            /*
        void DrawCircle(int centerX, int centerY, float radius, Color color);                                                   // Draw a color-filled circle
        void DrawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);       // Draw a piece of a circle
        void DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);  // Draw circle sector outline
        void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2);                            // Draw a gradient-filled circle
        void DrawCircleV(Vector2 center, float radius, Color color);                                                            // Draw a color-filled circle (Vector version)
        void DrawCircleLines(int centerX, int centerY, float radius, Color color);                                              // Draw circle outline
            */
       
                        //DrawCircle(650, 650, 30, RED);
                        //
                        //Vector2 Circle2 = mousePOS;
                        //Vector2 Circle3 = mousePOS;
                        //Vector2 Circle4 = mousePOS;
                        //Vector2 Circle5 = mousePOS;
                        //Vector2 Circle6 = mousePOS;
                        //
                        //Circle2.x += 200;
                        //Circle3.x += 400;
                        //Circle4.x += 600;
                        //Circle5.x -= 200;
                        //Circle6.x -= 400;
                        //
                        //DrawCircleSector(mousePOS, 100, 90,180,5, DARKBLUE);
                        //
                        //
                        //DrawCircleSectorLines(Circle2,100 , 0, 90, 2, RED);
                        //
                        //DrawCircleGradient(Circle3.x, Circle3.y, 90, BLUE, RED);
                        //
                        //DrawCircleV(Circle4, 100, GREEN);
                        //
                        //DrawCircleLines(Circle5.x, Circle5.y, 100, PURPLE);
     //***********************************************************************************************************************************************************


        /*
            void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);             // Draw ellipse
            void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color);        // Draw ellipse outline
        */

                    //Vector2 ellipse = mousePOS;
                    //Vector2 ellipse2 = mousePOS;
                    //
                    //ellipse2.x += 200;
                    //DrawEllipse(ellipse.x, ellipse.y, 100, 200, GREEN);
                    //
                    //DrawEllipseLines(ellipse2.x, ellipse.y, 100, 100, PURPLE);
     //***********************************************************************************************************************************************************



        //void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color); // Draw ring

        
                            //Vector2 ring = mousePOS;
                            //DrawRing(ring, 75, 100, 0,270, 6, RED);
     //***********************************************************************************************************************************************************





        /*
  void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);    // Draw ring outline
    void DrawRectangle(int posX, int posY, int width, int height, Color color);                        // Draw a color-filled rectangle
    void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  // Draw a color-filled rectangle (Vector version)
    void DrawRectangleRec(Rectangle rec, Color color);                                                 // Draw a color-filled rectangle
    void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);                 // Draw a color-filled rectangle with pro parameters
    void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);// Draw a vertical-gradient-filled rectangle
    void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);// Draw a horizontal-gradient-filled rectangle
    void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);       // Draw a gradient-filled rectangle with custom vertex colors
    void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
    void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color);                            // Draw rectangle outline with extended parameters
    void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);              // Draw rectangle with rounded edges
    void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color); // Draw rectangle with rounded edges outline
    
      */
     
        Vector2 rect = mousePOS;
        Vector2 rect2 = mousePOS;
        Vector2 rect3 = mousePOS;
        Vector2 rect4 = mousePOS;
        Vector2 rect5 = mousePOS;
        Vector2 rect6 = mousePOS;
        Vector2 rect7 = mousePOS;
        Vector2 rect8 = mousePOS;
        Vector2 rect9 = mousePOS;
        Vector2 rect10 = mousePOS;
        Vector2 rect11 = mousePOS;
        Vector2 rect12 = mousePOS;

        DrawRectangle(rect.x-10, rect.y-25, 20, 50, GREEN);


         EndDrawing();
    }

    CloseWindow();
    return 0;
}