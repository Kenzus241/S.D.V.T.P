/*
** EPITECH PROJECT, 2026
** S.D.V.T.P
** File description:
** my
*/

#ifndef _MY_H
    #define _MY_H
    #define RED "\033[31m"
    #define GRN "\033[32m"
    #define YEL "\033[33m"
    #define RESET "\033[0m"

    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "raylib.h"
    #include <stdarg.h>

int process_launch(void);
int game_loop(void);

#endif /*MY_H*/
