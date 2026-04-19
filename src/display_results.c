/*
** PROJECT, 2026
** S.D.V.T.P
** File description:
** display_results
*/

#include "my.h"

char *format_size(long long size)
{
    static char buffer[32];
    if (size > 1024LL*1024LL*1024LL) sprintf(buffer, "%.2f GB", (double)size / (1024*1024*1024));
    else if (size > 1024*1024) sprintf(buffer, "%.2f MB", (double)size / (1024*1024));
    else sprintf(buffer, "%.2f KB", (double)size / 1024);
    return buffer;
}

void draw_tree_recursive(file_node_t *node, int level, int *y_offset, long long root_size)
{
    if (!node || *y_offset > 850) return;

    Rectangle row = { 10, (float)*y_offset, 1180, 30 };
    
    // Interaction sécurisée
    if (CheckCollisionPointRec(GetMousePosition(), row)) {
        DrawRectangleRec(row, ColorAlpha(SKYBLUE, 0.2f));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && node->is_dir) {
            expand_node(node); // L'expansion est maintenant plus safe
            node->is_expanded = !node->is_expanded;
        }
    }

    // Rendu (style WizTree comme sur ton image)
    int x_indent = 20 + (level * 25);
    DrawRectangle(x_indent, *y_offset + 8, 14, 12, node->is_dir ? GOLD : BLUE);
    
    char *label = node->is_dir ? (node->is_expanded ? "[-] " : "[+] ") : "    ";
    DrawText(TextFormat("%s%s", label, node->name), x_indent + 20, *y_offset + 7, 16, WHITE);
    DrawText(format_size(node->size), 600, *y_offset + 7, 16, LIGHTGRAY);

    // Barre de % (WizTree)
    float pct = (root_size > 0) ? (float)node->size / root_size : 0;
    DrawRectangle(800, *y_offset + 10, 150, 10, DARKGRAY);
    DrawRectangle(800, *y_offset + 10, (int)(150 * pct), 10, MAGENTA);

    *y_offset += 32;

    if (node->is_expanded && node->children) {
        for (int i = 0; i < node->children_count; i++) {
            draw_tree_recursive(node->children[i], level + 1, y_offset, root_size);
        }
    }
}

void display_results_graphically(file_node_t *root)
{
    InitWindow(1200, 900, "S.D.V.T.P - Tree View Explorer");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground((Color){25, 25, 30, 255});
            
            // Header
            DrawRectangle(0, 0, 1200, 50, (Color){35, 35, 45, 255});
            DrawText("FILE NAME", 40, 15, 18, MAGENTA);
            DrawText("SIZE", 600, 15, 18, MAGENTA);
            DrawText("% OF DRIVE", 800, 15, 18, MAGENTA);

            int y_start = 60;
            draw_tree_recursive(root, 0, &y_start, root->size);

            DrawRectangle(0, 870, 1200, 30, BLACK);
            DrawText("L-Click: Expand/Collapse | ESC: Exit", 20, 878, 12, GRAY);
        EndDrawing();
    }
    CloseWindow();
}
