/*
** PROJECT, 2026
** S.D.V.T.P
** File description:
** my
*/

#ifndef _MY_H
    #define _MY_H
    #define COLOR_RED "\033[31m"
    #define COLOR_GRN "\033[32m"
    #define COLOR_YEL "\033[33m"
    #define COLOR_RESET "\033[0m"
    #define MAX_TOP_FILES 100
    #define MAX_ITEMS 200

    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <string.h>
    #include "raylib.h"
    #include <stdarg.h>

typedef struct file_node_s {
    char name[256];
    char path[1024];
    long long size;
    bool is_dir;
    bool is_expanded;
    struct file_node_s **children;
    int children_count;
} file_node_t;

int game_loop(void);
void launch_scan(void);
void display_results_graphically(file_node_t *root);
file_node_t *create_node(const char *path, const char *name);
void expand_node(file_node_t *node);
long long get_path_size(const char *path);
char *format_size(long long size);
int process_launch(void);
#endif /*MY_H*/
