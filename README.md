# CER-JO

## Table of Contents
1. [Project Description](#project-description)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [File Structure](#file-structure)
6. [Authors](#authors)


## Project Description

C’est bientôt les JO ! Le but de ce projet est de développer un programme permettant à l’entraîneur de l’équipe d’athlétisme de France de suivre l’évolution des performances de ses sportifs. Les performances des athlètes lors des entraînements seront stockées dans des fichiers. Le programme permet de mettre à jour les résultats, de consulter certains résultats et de produire des statistiques sur les athlètes.


## Features

- Gestion des épreuves suivantes :
  - 100 m
  - 400 m
  - 5000 m
  - Marathon
  - Relais 4x400 m
- Stockage des performances (entrainements) dans des fichiers individuels pour chaque athlète
- Enregistrement et sauvegarde des informations des entrainements
- Consultation de l’historique des entraînements par athlète, épreuve ou date
- Statistiques de performances :
  - Meilleur, pire temps et moyenne d’un athlète pour une épreuve donnée
  - Top 3 athlètes pour chaque discipline pour sélection aux JO
  - Progression des athlètes entre deux dates


## Installation

Pour installer et exécuter ce projet, suivez les étapes ci-dessous :

1. **Cloner le dépôt GitHub** :
    ```bash
    git clone https://github.com/charlyppr/CER-JO.git
    ```
2. **Accédez au répertoire du projet** :
    ```bash
    cd CER-JO
    ```
3. **Modifier le fichier constants.h** :
    - Ouvrez le fichier `constants.h` dans un éditeur de texte.
    - Modifiez la ligne définissant `PATH` pour qu'elle corresponde au chemin absolu du dossier où se trouvent vos fichiers. Par exemple :
      ```c
      #define PATH "/Users/Prenom/Documents/CER-JO"
      ```
4. **Compiler le programme** :
    ```bash
    make
    ```
5. **Nettoyer les fichiers objets** :
    ```bash
    make clean
    ```
6. **Exécuter le programme** :
    - 1ère option :
      ```bash
      ./cerjo
      ```
    - 2ème option :
      ```bash
      make run
      ```

Assurez-vous que le chemin dans `constants.h` est correct avant de compiler et d'exécuter le programme.


## Usage

Pour utiliser le programme, suivez les instructions ci-dessous :

1. **Ajouter/Supprimer/Modifier un athlète** : Entrez les informations demandées pour ajouter/supprimer/modifier un athlète.
2. **Ajouter/Supprimer/Modifier un entrainement** : Entrez les informations demandées pour ajouter/supprimer/modifier un entrainement d'un athlète existant.
3. **Voir l'historique des entrainements de l'athlète** : Choisissez un athlète, une épreuve ou une date pour afficher les entrainement correspondant.
4. **Consulter les statistiques** :
    - Voir les meilleurs, pires temps et moyennes d'un athlète pour une discipline.
    - Voir les trois meilleurs athlètes pour une discipline et savoir qui envoyer au JO.
    - Voir la progression d'un athlète entre deux dates pour une discipline.


## File Structure

Voici la structure des fichiers du projet :

CER-JO/
│
├── Athletes/
│ └── Athlete1.txt # Fichiers des entrainements d'Athlètes1
│ └── Athlete2.txt # Fichiers des entrainements d'Athlètes2
│ └── Athlete3.txt # Fichiers des entrainements d'Athlètes3
│ └── ...
│
├── Liste/
│ └── nomAthletes.txt # Fichiers des noms des athletes
│ └── nomEpreuve.txt # Fichiers des noms des épreuves
│ 
├── fichiers/
│ └── athlete.c # Fonctions pour gérer les athlètes
│ └── def.c # Fonctions 
│ └── entrainement.c # Fonctions
│ └── historique.c # Fonctions
│ └── statistique.c # Fonctions
│
├── headers/
│ └── athlete.h # Header pour athlete.c
│ └── constants.h # Header qui contient toutes les constantes
│ └── def.h # Header pour def.c
│ └── entrainement.h # Header pour entrainement.c
│ └── historique.h # Header pour historique.c
│ └── statistique.h # Header pour statistique.c
│ └── struct.h # Header qui contient toutes les structures
│
├── output/
│ └── .gitignore # Fichiers à ignorer par Git
│ └── cerjo # L'executable qui permet de lancer le programme
│
├── Makefile # Makefile pour compiler le projet
├── README.md # Ce fichier
└── main.c # Point d'entrée principal du programme


## Authors

- **Charly Pupier** - [charly.pupier@etu.cyu.fr](mailto:charly.pupier@etu.cyu.fr)
- **Aline Bouideghaghen** - [aline.bouideghaghen@etu.cyu.fr](mailto:aline.bouideghaghen@etu.cyu.fr)
- **Amir Azza** - [amir.azza@etu.cyu.fr](mailto:amir.azza@etu.cyu.fr)
