# <img width="70" alt="JO" src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/Olympic_rings_without_rims.svg/langfr-360px-Olympic_rings_without_rims.svg.png">&nbsp;&nbsp; CER-JO &nbsp;&nbsp;<img width="70" alt="JO" src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/Olympic_rings_without_rims.svg/langfr-360px-Olympic_rings_without_rims.svg.png">

## Table des Matières
1. [Introduction](#introduction)
2. [Fonctionnalités](#fonctionnalités)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Structure](#structure)
6. [Rapport](#rapport)
7. [Auteurs](#auteurs)



## Introduction

C’est bientôt les JO ! Le but de ce projet est de développer un programme permettant à l’entraîneur de l’équipe d’athlétisme de France de suivre l’évolution des performances de ses sportifs. Les performances des athlètes lors des entraînements seront stockées dans des fichiers. Le programme permet de mettre à jour les résultats, de consulter certains résultats et de produire des statistiques sur les athlètes.



## Fonctionnalités

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

    <img width="150" alt="Capture d’écran 2024-05-25 à 15 05 35" src="https://github.com/charlyppr/CER-JO/assets/166821960/65f773fb-9813-41ad-9e3a-ada18d74718d"> &nbsp;&nbsp;&nbsp; <img width="400" alt="Capture d’écran 2024-05-25 à 15 07 52" src="https://github.com/charlyppr/CER-JO/assets/166821960/24e7f3de-8de3-4181-971d-47bb91aa2f44">

3. **Accédez au répertoire du projet** :
    ```bash
    cd CER-JO
    ```

4. **Modifier le fichier PATH.h** :
    - Ouvrez le fichier `PATH.h` dans un éditeur de texte.
    - Modifiez la ligne définissant `PATH` pour qu'elle corresponde au chemin absolu ou se trouve le dossier. Par exemple :
      ```c
      #define PATH "/Users/Prenom/Documents/CER-JO"
      ```

    - Enregistrez les modifications.

5. **Compiler le programme** :
    ```bash
    make
    ```

6. **Exécuter le programme** :
     ```bash
     ./cerjo
     ```
    
    ou bien

     ```bash
     make run
     ```

*Et voila ! 🎉*
  
> [!WARNING]
> Assurez-vous que le chemin dans `PATH.h` est correct avant de compiler et d'exécuter le programme.



## Usage

Pour utiliser le programme, suivez les instructions ci-dessous :
#### 1. **Ajouter/Supprimer/Modifier un athlète** :
  - Ajouter un athlète.
  - Supprimer un athlète.
  - Modifier le prénom et le nom d'un athlète.

#### 2. **Ajouter/Supprimer/Modifier un entrainement** :
  - Ajouter un entrainement à un athlète parmis les 5 disciplines.
  - Supprimer un entrainement d'un athlète.
  - Modifier un entrainement d'un athlète :
    - La date.
    - La discipline.
    - Le temps.

#### 3. **Voir l'historique des entrainements de l'athlète** : 
  - Choisissez un athlète, une épreuve ou une date pour afficher les entrainement correspondant.

#### 4. **Consulter les statistiques** :
  - Voir les meilleurs, pires temps et moyennes d'un athlète pour une discipline.
  - Voir les trois meilleurs athlètes pour une discipline et savoir qui envoyer aux JO.
  - Voir la progression d'un athlète entre deux dates pour une discipline.



## Structure

Voici la structure des fichiers du projet :

```yaml
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



---
## Rapport

### 1. Commencement
  Nous avons entrepris en groupe de trois, constitué de Charly, Aline, et Amir, le projet CER-JO, visant à développer un programme de gestion d'athlètes pour les JO. Il permet de suivre les performances et les informations des participants.

  
  Avant de choisir ce projet, nous hésitions entre 3, CY-Fest, CY-BER-Path et CER-JO. Nous avons finalement choisi CER-JO car c'est celui qui semblait le plus atteignable pour nous trois.

### 2. Planning du projet
|Date|Activité|
|----|--------|
|12 avril|Début du projet, réunion de lancement.|
|13 avril - 21 avril|Faible productivité dû à d'autres devoirs.|
|22 avril - 28 avril|Mise en place du squelette du programme, ajout des premières fonctions.|
|29 avril|Réunion pour discuter de l'avancé du projet.<br>Premières difficultés (ouvrir correctement les fichiers textes).|
|30 avril - 5 mai|Répartition du programme sur plusieurs fichiers .c et .h.<br>Moitié du programme déjà fini malgré plusieurs bugs.|
|6 mai - 15 mai|Avancée conséquente du programme.|
|16 mai - 19 mai|Programme quasi terminé.<br>Ajouts de fonctionnalités, correction de bugs mineurs.|
|20 mai - 22 mai|Pas de nouveautés.|
|21 mai|Dernière réunion pour répartir les dernières taches<br>(ajouts de plusieurs fichiers d'athlètes, test des erreurs, ...).|
|23 mai - 25 mai|Dernière modification du programme avant rendu.|
|25 mai|Rendu du programme.|

### 3. Difficultés rencontrées
Nous avons rencontré plusieurs difficultés au cours de l'élaboration de notre programme :
  - **Gestion du Temps** : Faible productivité initiale nécessitant un réajustement du planning.
  - **Ouverture des fichiers texte** : Impossibilités d'ouvrir les fichiers, nécessitant de la documentation pour regler le problème.
  - **Lire un fichier texte** : Programme non fonctionnel du à la lecture de la mauvaise ligne, il fallait donc apprendre à sauter une ligne
  - **Trier les athlètes** : Aucune connaissance sur les tris, nécessité de se documenter
  - **Problème lorsqu'il y a plus de 10 athlètes** : Impossibilité pour le programme de lire correctement les noms, necessité d'ajuster FSEEK

### 4. Conclusion
Malgré les difficultés rencontrés, nous avons développé un programme fonctionnelle pour la gestion des athlètes. Ce projet nous a permis de renforcer nos compétences en développement et en travail d'équipe. 👍

---
## Auteurs

- **Charly** - [charly.pupier@etu.cyu.fr](mailto:charly.pupier@etu.cyu.fr)
- **Aline** - [aline.bouideghaghen@etu.cyu.fr](mailto:aline.bouideghaghen@etu.cyu.fr)
- **Amir** - [amir.azza@etu.cyu.fr](mailto:amir.azza@etu.cyu.fr)
