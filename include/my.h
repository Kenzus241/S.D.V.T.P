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

    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "raylib.h"
    #include <stdarg.h>

int process_launch(void);
int game_loop(void);
int launch_scan(void);

#endif /*MY_H*/
