/*
** EPITECH PROJECT, 2026
** S.D.V.T.P
** File description:
** launch_scan
*/

#include "my.h"

int compare_files(const void *a, const void *b)
{
    file_info_t *fileA = (file_info_t *)a;
    file_info_t *fileB = (file_info_t *)b;

    if (fileB->size > fileA->size) return 1;
    if (fileB->size < fileA->size) return -1;
    return 0;
}

void scan_directory(const char *dir_path, file_info_t *top_files, int *count)
{
    DIR *dir = opendir(dir_path);
    struct dirent *entry;
    struct stat st;
    char path[1024];

    if (!dir)
        return;
    while ((entry = readdir(dir)) != NULL) {
        // 1. Ignorer les liens vers soi-même et le parent
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        // 2. FILTRAGE CRITIQUE : Ignorer les dossiers système virtuels AVANT d'y entrer
        // On vérifie le nom de l'entrée pour ne pas scanner /proc, /sys, etc.
        if (strcmp(entry->d_name, "proc") == 0 || strcmp(entry->d_name, "sys") == 0 || 
            strcmp(entry->d_name, "dev") == 0 || strcmp(entry->d_name, "run") == 0 ||
            strcmp(entry->d_name, "snap") == 0) // Optionnel: snap crée souvent des doublons
            continue;
        // 3. Construction du chemin complet
        // On utilise un format propre pour éviter les doubles slashes (//)
        if (strcmp(dir_path, "/") == 0)
            snprintf(path, sizeof(path), "/%s", entry->d_name);
        else
            snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        // 4. Récupération des infos (lstat pour ne pas suivre les liens symboliques)
        if (lstat(path, &st) == -1)
            continue;
        if (S_ISDIR(st.st_mode)) {
            // C'est un dossier : on descend dedans
            scan_directory(path, top_files, count);
        } else if (S_ISREG(st.st_mode)) {
            // C'est un vrai fichier : logique de mise à jour du TOP
            if (*count < MAX_TOP_FILES) {
                strncpy(top_files[*count].path, path, 1024);
                top_files[*count].size = st.st_size;
                (*count)++;
                qsort(top_files, *count, sizeof(file_info_t), compare_files);
            } else if (st.st_size > top_files[MAX_TOP_FILES - 1].size) {
                strncpy(top_files[MAX_TOP_FILES - 1].path, path, 1024);
                top_files[MAX_TOP_FILES - 1].size = st.st_size;
                qsort(top_files, MAX_TOP_FILES, sizeof(file_info_t), compare_files);
            }
        }
    }
    closedir(dir);
}

void launch_scan(void)
{
    file_info_t top_files[MAX_TOP_FILES];
    int file_count = 0;

    memset(top_files, 0, sizeof(file_info_t) * MAX_TOP_FILES);
    printf("\n");
    printf("--- Analyse du disque entier (/) en cours ---\n");
    printf("  ....Cela peut prendre du temps....\n");
    
    // Scan à partir de la racine
    scan_directory("/", top_files, &file_count);

    printf("\nTOP 10 DES FICHIERS LES PLUS LOURDS DU SYSTEME :\n");
    for (int i = 0; i < (file_count < 10 ? file_count : 10); i++) {
        double size_gb = (double)top_files[i].size / (1024.0 * 1024.0 * 1024.0);
        printf("%d. [%.2f Go] %s\n", i + 1, size_gb, top_files[i].path);
    }

    display_results_graphically(top_files, file_count);
}
