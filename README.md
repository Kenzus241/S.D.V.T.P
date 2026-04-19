S.D.V.T.P (C / Linux)
Une reproduction légère et performante de l'utilitaire WizTree, développée en C pour les systèmes GNU/Linux. Ce projet permet de visualiser instantanément l'occupation de l'espace disque sous forme de Treemap interactive.

🚀 Objectifs du Projet
L'objectif principal est de fournir un outil graphique permettant de repérer les fichiers et dossiers les plus volumineux pour optimiser le stockage de son système.

Analyse rapide : Scan récursif du système de fichiers via les appels système POSIX (stat, readdir).

Visualisation interactive : Rendu graphique d'une "Squarified Treemap" pour une compréhension visuelle des données.

Performance : Utilisation d'un arbre n-aire pour une gestion efficace de la hiérarchie des fichiers en mémoire.

🛠️ Stack Technique
Langage : C

Interface Graphique : Raylib

Système : Linux

🔧 Installation et Compilation
Assurez-vous d'avoir Raylib installé sur votre système.

# Cloner le dépôt
git clone https://github.com/Kenzus241/S.D.V.T.P.git
cd S.D.V.T.P

# Compiler le projet
make run

# Lancer l'application
./wiztree
