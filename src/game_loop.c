/*
** EPITECH PROJECT, 2026
** S.D.V.T.P
** File description:
** game_loop
*/
#include "my.h"

bool GuiButton(Rectangle bounds, const char *text) {
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
    DrawText(text, (int)(bounds.x + (bounds.width/2 - textWidth/2)), 
             (int)(bounds.y + (bounds.height/2 - 10)), 20, BLACK);
    return clicked;
}

int game_loop(void)
{
    Rectangle btnScan = { 300.0f, 180.0f, 200.0f, 60.0f };
    bool should_start_scan = false;
    Texture2D background;

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
            DrawText("Scan en cours...", 330, 300, 20, RED);
        } else {
            if (GuiButton(btnScan, "Lancer le Scan")) {
                should_start_scan = true;
            }
        }
        EndDrawing();
        if (should_start_scan) {
            WaitTime(0.5); 
            break;
        }
    }

    UnloadTexture(background);
    CloseWindow();

    if (should_start_scan) {
        launch_scan();
    }
    return 0;
}
