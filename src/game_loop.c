/*
** PROJECT, 2026
** S.D.V.T.P
** File description:
** game_loop
*/
#include "my.h"

bool GuiButton(Rectangle bounds, const char *text)
{
    Vector2 mousePoint = GetMousePosition();
    bool clicked = false;
    Color color = MAGENTA;
    float roundness = 0.3f;
    int segments = 10;
    int textWidth = MeasureText(text, 20);

    if (CheckCollisionPointRec(mousePoint, bounds)) {
        color = BLUE;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clicked = true;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            color = DARKGRAY;
        }
    }
    DrawRectangleRounded(bounds, roundness, segments, color);
    DrawRectangleRoundedLines(bounds, roundness, segments, PURPLE);
    DrawText(text, (int)(bounds.x + (bounds.width / 2 - textWidth / 2)),
             (int)(bounds.y + (bounds.height / 2 - 10)), 20, BLACK);
    return clicked;
}

int game_loop(void)
{
    Rectangle btnScan = { 300.0f, 299.0f, 200.0f, 60.0f };
    bool should_start_scan = false;
    Texture2D background;

    SetTraceLogLevel(LOG_WARNING);
    InitWindow(800, 450, "S.D.V.T.P");
    background = LoadTexture("lib/my/image/S.D.V.T.P_icone.png");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(background,
                (Rectangle){ 0, 0, background.width, background.height },
                (Rectangle){ 0, 0, 800, 450 },
                (Vector2){ 0, 0 }, 0.0f, WHITE);

            if (should_start_scan) {
                // Draw loading screen
                ClearBackground(BLACK);
                DrawText("CALCUL DE LA RACINE EN COURS...", 200, 210, 20, WHITE);
                DrawText("Veuillez patienter...", 320, 240, 15, WHITE);
                EndDrawing();
                // Let system display the loading message
                WaitTime(0.1);
                // Close window before launching scan
                UnloadTexture(background);
                CloseWindow();
                // Now launch the scan with its own window
                launch_scan();
                return 0;
            } else {
                if (GuiButton(btnScan, "Lancer le Scan")) {
                    should_start_scan = true;
                }
            }
        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
    return 0;
}
