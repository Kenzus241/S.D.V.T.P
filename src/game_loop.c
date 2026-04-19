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
            // 1. On dessine l'écran de chargement
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("CALCUL DE LA RACINE EN COURS...", 200, 210, 20, WHITE);
            DrawText("Veuillez patienter...", 320, 240, 15, WHITE);
            EndDrawing(); // On force l'envoi à l'écran ICI
            // 2. On laisse une micro-seconde au système pour afficher la fenêtre
            // sans ça, le message n'apparaît jamais avant le freeze
            WaitTime(0.1); 
            // 3. MAINTENANT on lance le calcul lourd
            launch_scan(); 
            break; 
            } else {
                if (GuiButton(btnScan, "Lancer le Scan")) {
                    should_start_scan = true;
                }
            }
        if (!should_start_scan) EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
    return 0;
}
