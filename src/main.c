/*
** EPITECH PROJECT, 2026
** S.D.V.T.P
** File description:
** main
*/
#include "my.h"

void print_usage(void)
{
    printf("    Usage: " COLOR_GRN "./S.D.V.T.P\n" COLOR_RESET);
    printf(COLOR_RED " Or\n" COLOR_RESET);
    printf("    Usage: " COLOR_GRN "./S.D.V.T.P" COLOR_RESET COLOR_YEL " -h (-h = help)\n" COLOR_RESET);
}

void print_subject(void)
{
    printf(COLOR_GRN " SUBJECT:\n" COLOR_RESET);
    printf("The aim of this project is to ");
    printf("enable\nusers to view the space taken up");
    printf("\nby each file and folder on the disk\nin a ");
    printf("recursive manner, using an\n");
    printf("intuitive and easy-to-use graphical interface.\n\n");
}

int check_flag_h(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printf(COLOR_GRN "Project:" COLOR_RESET COLOR_YEL " S.D.V.T.P\n\n" COLOR_RESET);
        print_subject();
        printf(COLOR_GRN " USAGE:\n" COLOR_RESET);
        print_usage();
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (check_flag_h(argc, argv) == 1)
        return 0;
    if (argc > 2) {
        printf(COLOR_RED "Error!!!\n" COLOR_RESET);
        print_usage();
        return 84;
    }
    process_launch();
    return 0;
}
