#include "my.h"

// Calcule la taille d'un dossier SANS créer de nœuds (très rapide)
long long get_path_size(const char *path)
{
    struct stat st;
    if (lstat(path, &st) == -1) return 0;
    if (S_ISREG(st.st_mode)) return st.st_size;
    
    DIR *dir = opendir(path);
    if (!dir) return 0;

    struct dirent *entry;
    long long total = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        
        // FILTRAGE : On ignore les dossiers qui font freezer (proc, sys...)
        if (strcmp(entry->d_name, "proc") == 0 || strcmp(entry->d_name, "sys") == 0 ||
            strcmp(entry->d_name, "dev") == 0 || strcmp(entry->d_name, "run") == 0 ||
            strcmp(entry->d_name, "timeshift") == 0) continue;

        char sub[1024];
        snprintf(sub, 1024, "%s/%s", strcmp(path, "/") == 0 ? "" : path, entry->d_name);
        total += get_path_size(sub);
    }
    closedir(dir);
    return total;
}

file_node_t *create_node(const char *path, const char *name)
{
    file_node_t *node = malloc(sizeof(file_node_t));
    struct stat st;
    if (lstat(path, &st) == -1) return NULL;

    strcpy(node->name, name);
    strcpy(node->path, path);
    node->is_dir = S_ISDIR(st.st_mode);
    
    // On ne calcule la taille ICI que si on est au premier niveau
    node->size = 0; 
    node->is_expanded = false;
    node->children = NULL;
    node->children_count = 0;
    return node;
}

void expand_node(file_node_t *node)
{
    if (!node || !node->is_dir || node->is_expanded) return;

    DIR *dir = opendir(node->path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        if (strcmp(entry->d_name, "proc") == 0 || strcmp(entry->d_name, "sys") == 0) continue;

        char sub[1024];
        if (strcmp(node->path, "/") == 0) snprintf(sub, 1024, "/%s", entry->d_name);
        else snprintf(sub, 1024, "%s/%s", node->path, entry->d_name);

        file_node_t *child = create_node(sub, entry->d_name);
        if (child) {
            // ON CALCULE LA TAILLE DU DOSSIER UNIQUEMENT À L'EXPANSION
            child->size = get_path_size(child->path); 
            node->children = realloc(node->children, sizeof(file_node_t*) * (node->children_count + 1));
            node->children[node->children_count++] = child;
        }
    }
    closedir(dir);
    node->is_expanded = true;
}

void launch_scan(void)
{
    file_node_t *root = create_node("/", "Root (/)");
    root->size = get_path_size("/"); // Seul gros calcul au début
    display_results_graphically(root);
}
