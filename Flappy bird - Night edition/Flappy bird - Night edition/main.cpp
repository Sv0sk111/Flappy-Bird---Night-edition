#include <iostream>
#include <raylib.h>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 700;
int mouseX = GetMouseX();
int mouseY = GetMouseY();
bool start = false;
bool lose = false;
bool reset = false;
int startX;

class Background
{
public:
    const int cityX = 395;
    const int cityY = 370;
    const int starsY = 9;
    const int starsX = 400;
    Texture2D texture;
    Texture2D texture2;

    void loadBackgroundTexture()
    {
        Image image = LoadImage("Textures/City.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);

        Image image2 = LoadImage("Textures/stars.png");
        texture2 = LoadTextureFromImage(image2);
        UnloadImage(image2);
    }
    ~Background()
    {
        UnloadTexture(texture);
        UnloadTexture(texture2);
    }
    void draw()
    {
        float scale = 18.0f;
        float scale2 = 15.0f;

        DrawTexturePro(texture, {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
        {static_cast<float>(cityX), static_cast<float>(cityY), static_cast<float>(texture.width * scale), static_cast<float>(texture.height * scale)},
        {static_cast<float>(texture.width * scale / 2), static_cast<float>(texture.height * scale / 2)}, 0,WHITE);

        DrawTexturePro(texture2, {0, 0, static_cast<float>(texture2.width), static_cast<float>(texture2.height)},
        {static_cast<float>(starsX), static_cast<float>(starsY), static_cast<float>(texture2.width * scale2), static_cast<float>(texture2.height * scale2)},
        {static_cast<float>(texture2.width * scale2 / 2), static_cast<float>(texture2.height * scale2 / 2)}, 0,WHITE);
    }
};

class Pillars
{
public:
    int pillarX;
    const int pillarWidth = 90;
    const int minDistance = 150;
    int space;
    int topPillarHeight;
    int bottomPillarY;
    const float movePillarX = -3.7f;
    const int lineWidth = 5;

    const int boxWidth = 110;
    const int boxHeight = 25;
    bool passed;


    Pillars(int startX)
    {
        if(reset == false)
        {
            generateRandomValues();
            pillarX = startX;
            passed = false;
        } 
    }

    void generateRandomValues()
    {
        const int minHeight = 100;
        const int maxHeight = 700;
        const int minBottom = 500;
        const int maxBottom = screenHeight - 300;

        topPillarHeight = GetRandomValue(minHeight, maxHeight);
        bottomPillarY = GetRandomValue(minBottom, maxBottom);

        while (bottomPillarY - topPillarHeight < minDistance)
        {
            topPillarHeight = GetRandomValue(minHeight, maxHeight);
            bottomPillarY = GetRandomValue(minBottom, maxBottom);
        }
    }

    void movePillarsLeft()
    {
        if(!reset)
        {
            pillarX += static_cast<int>(movePillarX);
        }
        else if(true)
        {
            pillarX -= 500;
        }
    }

    void draw()
    {
            DrawRectangle(pillarX, 0, pillarWidth, topPillarHeight, DARKGREEN);
            DrawRectangle(pillarX, bottomPillarY, pillarWidth, screenHeight - bottomPillarY, DARKGREEN);
            
            DrawRectangle(pillarX - lineWidth, 0, lineWidth, topPillarHeight, DARKBROWN);
            DrawRectangle(pillarX + pillarWidth, 0, lineWidth, topPillarHeight, DARKBROWN);
            DrawRectangle(pillarX - lineWidth, bottomPillarY, lineWidth, screenHeight - bottomPillarY, DARKBROWN);
            DrawRectangle(pillarX + pillarWidth, bottomPillarY, lineWidth, screenHeight - bottomPillarY, DARKBROWN);

            DrawRectangle(pillarX - lineWidth + 5, bottomPillarY, lineWidth - 2, screenHeight - bottomPillarY, GREEN);
            DrawRectangle(pillarX - lineWidth + 5, 0, lineWidth - 2, topPillarHeight, GREEN);


            DrawRectangle(pillarX - lineWidth - 4, topPillarHeight, boxWidth, boxHeight, DARKGREEN);
            DrawRectangle(pillarX - lineWidth - 5, bottomPillarY - 25, boxWidth, boxHeight, DARKGREEN);

            DrawRectangle(pillarX - lineWidth - 6, topPillarHeight, lineWidth, boxHeight, DARKBROWN);
            DrawRectangle(pillarX - lineWidth - 5, bottomPillarY - 25, lineWidth, boxHeight, DARKBROWN);
            DrawRectangle(pillarX - lineWidth + 100, topPillarHeight, lineWidth, boxHeight, DARKBROWN);
            DrawRectangle(pillarX - lineWidth + 100, bottomPillarY - 25, lineWidth, boxHeight, DARKBROWN);


            DrawRectangle(pillarX - lineWidth - 6, topPillarHeight + 25, boxWidth, 4, DARKBROWN);
            DrawRectangle(pillarX - lineWidth - 5, bottomPillarY - 25, boxWidth, 4, DARKBROWN);
    }
};

class Gui
{
public:
    int buttonWidth = 150;
    int buttonHeight = 50;
    const int buttonX = 270;
    const int buttonY = 500;
    const float cornerRadius = 0.5f;
    const int alpha1 = 140;
    const int alpha2 = 199;
    Color darkRed = {55, 0, 0};

    void detection()
    {
            if ((mouseX >= buttonX) && (mouseX <= buttonX + buttonWidth) && (mouseY >= buttonY) && (mouseY <= buttonY + buttonHeight))
            {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    start = true;
                }
            }
            else if (IsKeyPressed(KEY_ENTER))
            {
                start = true;
            }
            else
            {
                SetMouseCursor(MOUSE_CURSOR_ARROW);
            }
        }

    void draw()
    {
        int buttonWidth = 150;
        int buttonHeight = 50;
        Rectangle roundedRect = {(float)buttonX, (float)buttonY, (float)buttonWidth, (float)buttonHeight};
        DrawRectangleRounded(roundedRect, cornerRadius, 0, BLUE);

        DrawText("Start", buttonX + 31, buttonY + 10, 30, BLACK);
        DrawText("FLAPPY", 80, 80, 50, BLACK);
        DrawText("BIRD", 80, 130, 50, BLACK);
        DrawText("NIGHT EDITION", 80, 180, 50, BLACK);
    }

    void loseScreen()
    {
        SetMouseCursor(MOUSE_CURSOR_ARROW);
        lose = true;
        DrawText("YOU LOST!", 200, 300, 70, RED);
        buttonWidth = 210;
        buttonHeight = 60;
        Rectangle roundedRect = {(float)buttonX, (float)buttonY, (float)buttonWidth, (float)buttonHeight};
        DrawRectangleRounded(roundedRect, cornerRadius, 0, RED);
        DrawText("Start Screen", buttonX + 15, buttonY + 10, 27, BLACK);

        if ((mouseX >= buttonX) && (mouseX <= buttonX + buttonWidth) && (mouseY >= buttonY) && (mouseY <= buttonY + buttonHeight))
        {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                lose = false;
                start = false;
                reset = true;
            }   
        }
        else if(IsKeyPressed(KEY_ENTER))
        {
            lose = false;
            start = false;
            reset = true;
        }
        else
        {
            SetMouseCursor(MOUSE_CURSOR_ARROW);
        }
    }
};

class Bird
{
public:
    int birdX = 100;
    int birdY = 300;
    float velocityY = 0.0f;
    const float gravityForce = 0.30f;
    const float jumpForce = -7.0f;
    Texture2D texture;
    Gui gui;
    int points;

    Bird() : points(0) {}

    void incrementPoints()
    {
        if(reset)
        {
            points = 0;
        }
        else
        {
        points++;
        }
    }

    void loadBirdTexture()
    {
        Image image = LoadImage("Textures/flappyBird.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    ~Bird()
    {
        UnloadTexture(texture);
    }

    void resetBird()
    {
        velocityY = 0.0f;
        birdY = 300;
    }

    void gravity()
    {
        if (birdY <= 700)
        {
            velocityY += gravityForce;
            birdY += static_cast<int>(velocityY);
            if (birdY > 700)
            {
                birdY = 700;
                gui.loseScreen();
            }
        }
    }

    void collision(const std::vector<Pillars> &pillars)
    {
        for (const Pillars &pillar : pillars)
        {
            if (CheckCollisionPointRec({ static_cast<float>(birdX), static_cast<float>(birdY) },
            { static_cast<float>(pillar.pillarX), 0, static_cast<float>(pillar.pillarWidth), 
            static_cast<float>(pillar.topPillarHeight + 50) }) ||CheckCollisionPointRec({ static_cast<float>(birdX), static_cast<float>(birdY) },
            { static_cast<float>(pillar.pillarX), static_cast<float>(pillar.bottomPillarY - 40), static_cast<float>(pillar.pillarWidth), 
            static_cast<float>(screenHeight - pillar.bottomPillarY) }))
            {
                lose = true;
                birdY = 0;
            }
        }
    }

    void movement()
    {
        SetMouseCursor(MOUSE_CURSOR_ARROW);
        if (IsKeyPressed(KEY_SPACE) && birdY >= 40)
        {
            velocityY = jumpForce;
        }
    }

    void draw()
    {
        float scale = 4.5f;

        float rotation = 0.0f;
        const float maxRotation = 45.0f;

        if (velocityY > 0.0f)
        {
            rotation = (velocityY / 10.0f) * maxRotation;
        }
        else if (velocityY < 0.0f)
        {
            rotation = (velocityY / (-9.0f)) * maxRotation;
        }

        if (rotation > maxRotation)
        {
            rotation = maxRotation;
        }
        else if (rotation < -maxRotation)
        {
            rotation = -maxRotation;
        }

        DrawTexturePro(texture, {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
        {static_cast<float>(birdX), static_cast<float>(birdY), static_cast<float>(texture.width * scale), static_cast<float>(texture.height * scale)},
        {static_cast<float>(texture.width * scale / 2), static_cast<float>(texture.height * scale / 2)}, rotation, WHITE);

        DrawText(TextFormat("POINTS: %d", points), 100, 20, 40, BLACK);


    }
};

class Program
{
private:
    Bird flappyBird;
    std::vector<Pillars> pillars;
    Gui gui;
    Background background;

public:
    Program() : flappyBird(), background()
    {
        flappyBird.loadBirdTexture();
        Pillars initialPillar(screenWidth);
        pillars.push_back(initialPillar);
        background.loadBackgroundTexture();
    }

    void update()
    {
        if(lose == false)
        {
            mouseX = GetMouseX();
            mouseY = GetMouseY();
            if(start == true)
            {
                background.draw();
                for (size_t i = 0; i < pillars.size(); ++i)
                {
                    pillars[i].movePillarsLeft();
                    pillars[i].draw();
                }

                if (pillars.back().pillarX <= screenWidth - 400)
                {
                    Pillars newPillar(screenWidth);
                    pillars.push_back(newPillar);
                }

                for (size_t i = 0; i < pillars.size(); ++i)
                {
                    pillars[i].movePillarsLeft();
                    pillars[i].draw();

                    if (!pillars[i].passed && pillars[i].pillarX + pillars[i].pillarWidth < flappyBird.birdX - flappyBird.texture.width / 2)
                    {
                        pillars[i].passed = true;
                        flappyBird.incrementPoints();
                    }

                    if(reset)
                    {
                        pillars[i].movePillarsLeft();
                    }
                }

                flappyBird.movement();
                flappyBird.gravity();
                flappyBird.draw();
                flappyBird.collision(pillars);

                if (reset)
                {
                    pillars.clear();
                    flappyBird.resetBird();
                    Pillars newPillar(startX);
                    pillars.push_back(newPillar);
                    reset = false;
                }
            }
            else if(start == false)
            {
                background.draw();
                gui.draw();
                gui.detection();
            }
        }
        else if(lose == true)
        {
            background.draw();
            gui.loseScreen();
        }
    }
};

int main()
{
    InitWindow(screenWidth, screenHeight, "Flappy bird - Night edition");
    SetTargetFPS(60);
    Program program;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        program.update();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}














