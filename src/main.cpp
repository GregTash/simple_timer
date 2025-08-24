#include <raylib.h>
#include <sstream>
#include <iomanip>

float secs = 0;
int mins = 0;

int main(void)
{
    int screenWidth = 250;
    int screenHeight = 50;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_WINDOW_MOUSE_PASSTHROUGH);
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags(FLAG_WINDOW_TOPMOST);
    InitWindow(screenWidth, screenHeight, "Simple Timer");

    SetTargetFPS(60);

    std::ostringstream stream;
    stream.precision(2);
    stream << std::fixed << secs;

    while (!WindowShouldClose())
    {
        secs += GetFrameTime();

        SetWindowPosition(GetMonitorWidth(0)/2 - screenWidth/2, 0);

        if (secs >= 60) {
            secs = 0;
            mins += 1;
        }

        std::ostringstream stream;
        stream.precision(2);

        stream
           << std::setfill('0') << std::setw(2) << mins << ":"
           << std::fixed << secs;
        
        BeginDrawing();
        Color col = {0,0,0,150};
            ClearBackground(col);
            DrawText(stream.str().c_str(), 0, 0, screenHeight, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}