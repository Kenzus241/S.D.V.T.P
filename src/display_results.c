/*
** EPITECH PROJECT, 2026
** S.D.V.T.P
** File description:
** display_results
*/

#include "my.h"

void display_results_graphically(file_info_t *files, int count)
{
    InitWindow(1000, 600, "S.D.V.T.P - Top Files Results");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){ 20, 20, 25, 255 }); // Fond très sombre

        DrawText("S.D.V.T.P - ANALYSE SYSTEME", 20, 20, 24, MAGENTA);
        DrawLine(20, 55, 980, 55, PURPLE);

        for (int i = 0; i < (count < 15 ? count : 15); i++) {
            float ratio = (float)files[i].size / files[0].size;
            int barWidth = (int)(ratio * 550); // Max 550px
            int yPos = 80 + (i * 32);
            
            // Barre de taille
            DrawRectangle(300, yPos, barWidth, 22, ColorLerp(PURPLE, BLUE, ratio));
            DrawRectangleLines(300, yPos, barWidth, 22, ColorAlpha(WHITE, 0.3f));

            // Texte : Taille (Mo/Go)
            char sizeText[32];
            if (files[i].size > 1024LL*1024LL*1024LL)
                sprintf(sizeText, "%.2f Go", (double)files[i].size / (1024*1024*1024));
            else
                sprintf(sizeText, "%.2f Mo", (double)files[i].size / (1024*1024));
                
            DrawText(sizeText, 210, yPos + 4, 16, WHITE);
            
            // Texte : Nom du fichier (tronqué si trop long)
            const char *fileName = GetFileName(files[i].path);
            DrawText(TextSubtext(fileName, 0, 25), 20, yPos + 4, 16, LIGHTGRAY);
        }

        DrawText("Appuyez sur ESC pour quitter", 400, 570, 14, GRAY);
        EndDrawing();
    }
    CloseWindow();
}
