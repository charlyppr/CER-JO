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
- Stockage des performances dans des fichiers individuels pour chaque athlète
- Enregistrement et sauvegarde des informations des entrainements
- Consultation de l’historique des entraînements par athlète, épreuve ou date
- Statistiques de performances :
  - Meilleur, pire temps et moyenne d’un athlète pour une épreuve donnée
  - Top 3 athlètes pour chaque discipline pour sélection aux JO
  - Progression des athlètes entre deux dates



## Installation

Pour installer et exécuter ce projet, suivez les étapes ci-dessous :

1. **Cloner le dépôt GitHub ou téléchargé le fichier ZIP** :
    ```bash
    git clone https://github.com/charlyppr/CER-JO.git
    ```
    ou

    ![Button] (<button type="button" id=":R55ab:" aria-haspopup="true" tabindex="0" class="types__StyledButton-sc-ws60qy-0 kHdfWW"><span data-component="buttonContent" class="Box-sc-g0xbh4-0 kkrdEu"><span data-component="leadingVisual" class="Box-sc-g0xbh4-0 trpoQ"><div class="Box-sc-g0xbh4-0 bVvbgP"><svg aria-hidden="true" focusable="false" role="img" class="octicon octicon-code" viewBox="0 0 16 16" width="16" height="16" fill="currentColor" style="display:inline-block;user-select:none;vertical-align:text-bottom;overflow:visible"><path d="m11.28 3.22 4.25 4.25a.75.75 0 0 1 0 1.06l-4.25 4.25a.749.749 0 0 1-1.275-.326.749.749 0 0 1 .215-.734L13.94 8l-3.72-3.72a.749.749 0 0 1 .326-1.275.749.749 0 0 1 .734.215Zm-6.56 0a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042L2.06 8l3.72 3.72a.749.749 0 0 1-.326 1.275.749.749 0 0 1-.734-.215L.47 8.53a.75.75 0 0 1 0-1.06Z"></path></svg></div></span><span data-component="text">Code</span></span><span data-component="trailingAction" class="Box-sc-g0xbh4-0 trpoQ"><svg aria-hidden="true" focusable="false" class="octicon octicon-triangle-down" viewBox="0 0 16 16" width="16" height="16" fill="currentColor" style="display:inline-block;user-select:none;vertical-align:text-bottom;overflow:visible"><path d="m4.427 7.427 3.396 3.396a.25.25 0 0 0 .354 0l3.396-3.396A.25.25 0 0 0 11.396 7H4.604a.25.25 0 0 0-.177.427Z"></path></svg></span></button>)

2. **Accédez au répertoire du projet** :
    ```bash
    cd CER-JO
    ```

3. **Modifier le fichier PATH.h** :
    - Ouvrez le fichier `PATH.h` dans un éditeur de texte.
    - Modifiez la ligne définissant `PATH` pour qu'elle corresponde au chemin absolu du dossier où se trouvent les fichiers du programme. Par exemple :

      ```c
      #define PATH "/Users/Prenom/Documents/CER-JO"
      ```

    - Enregistrez les modifications.

4. **Compiler le programme** :
    ```bash
    make
    ```

5. **Nettoyer les fichiers objets** :
    ```bash
    make clean
    ```

6. **Exécuter le programme** :
    - ```bash
      ./cerjo
      ```
    
    ou

    - ```bash
      make run
      ```

> Assurez-vous que le chemin dans `PATH.h` est correct avant de compiler et d'exécuter le programme.



## Usage

Pour utiliser le programme, suivez les instructions ci-dessous :

1. **Ajouter/Supprimer/Modifier un athlète** :
    - Ajouter un athlète.
    - Supprimer un athlète.
    - Modifier le prénom et le nom d'un athlète.

2. **Ajouter/Supprimer/Modifier un entrainement** :
    - Ajouter un entrainement à un athlète parmis les 5 disciplines.
    - Supprimer un entrainement d'un athlète.
    - Modifier un entrainement d'un athlète :
        - La date.
        - La discipline.
        - Le temps.

3. **Voir l'historique des entrainements de l'athlète** : 
    - Choisissez un athlète, une épreuve ou une date pour afficher les entrainement correspondant.

4. **Consulter les statistiques** :
    - Voir les meilleurs, pires temps et moyennes d'un athlète pour une discipline.
    - Voir les trois meilleurs athlètes pour une discipline et savoir qui envoyer au JO.
    - Voir la progression d'un athlète entre deux dates pour une discipline.



## File Structure

Voici la structure des fichiers du projet :

```bash
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
│ └── def.c # Fonctions diverses
│ └── entrainement.c # Fonctions pour gérer les entrainements
│ └── historique.c # Fonctions pour gérer l'historique
│ └── statistique.c # Fonctions pour calculer les statistiques
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
│
├── Makefile # Makefile pour compiler le projet
├── PATH.h # Header qui relie le programme au chemin du fichier
├── README.md # Ce fichier
└── main.c # Point d'entrée principal du programme
```



## Authors

- **Charly Pupier** - [charly.pupier@etu.cyu.fr](mailto:charly.pupier@etu.cyu.fr)
- **Aline Bouideghaghen** - [aline.bouideghaghen@etu.cyu.fr](mailto:aline.bouideghaghen@etu.cyu.fr)
- **Amir Azza** - [amir.azza@etu.cyu.fr](mailto:amir.azza@etu.cyu.fr)
