/*
** EPITECH PROJECT, 2026
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

    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <string.h>
    #include "raylib.h"
    #include <stdarg.h>

typedef struct {
    char path[1024];
    long long size;
} file_info_t;

int process_launch(void);
int game_loop(void);
void display_results_graphically(file_info_t *files, int count);
void launch_scan(void);

#endif /*MY_H*/
