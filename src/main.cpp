#include <raylib.h>
#include <sstream>
#include <iomanip>

#define Font XFont
#include <X11/Xlib.h>
#include <X11/keysym.h>
#undef Font


float secs = 0;
int mins = 0;

bool timerOn = false;

int main(void)
{
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        printf("Failed to open X display\n");
        return 1;
    }
    Window root = DefaultRootWindow(display);

    // Grab keys globally (Numpad 1 and Numpad 2)
    int np1Key = XKeysymToKeycode(display, XK_KP_1);
    int np2Key = XKeysymToKeycode(display, XK_KP_2);

    XGrabKey(display, np1Key, AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, np2Key, AnyModifier, root, True, GrabModeAsync, GrabModeAsync);

    XSelectInput(display, root, KeyPressMask);

    // --- Raylib setup ---
    int screenWidth = 250;
    int screenHeight = 50;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_WINDOW_MOUSE_PASSTHROUGH);
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags(FLAG_WINDOW_TOPMOST);

    InitWindow(screenWidth, screenHeight, "Simple Timer");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // --- Check global hotkeys ---
        while (XPending(display)) {
            XEvent event;
            XNextEvent(display, &event);
            if (event.type == KeyPress) {
                int keycode = event.xkey.keycode;
                if (keycode == np1Key) {
                    timerOn = !timerOn;   // Toggle pause/start
                }
                else if (keycode == np2Key) {
                    timerOn = false;      // Reset
                    secs = 0;
                    mins = 0;
                }
            }
        }

        if (timerOn) secs += GetFrameTime();

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

    XCloseDisplay(display);
    CloseWindow();

    return 0;
}
