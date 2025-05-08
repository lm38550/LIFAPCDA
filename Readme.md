# L'Incroyable Fermier Assassins Partant Chercher Des Abricots (LIFAPCDA)

### Louis MOREL p2100444 | Jérémy BOUILLY p2103485 | Adrien SALLERIN p2102184

---

## Synopsis

Vous incarnez un jeune fermier assasins, fan d'abricots qui part à la conquête du château du roi afin de prendre sa couronne !

Vous devrez progresser dans le château du roi tout en rassemblant les abricots. Arriverez-vous à surmonter ces épreuves ?

---

## Commandes

Voici les commandes qui vous seront utiles afin de jouer au jeu :

- _ZQSD/WASD_ pour se déplacer
- _F_ pour attaquer à la fourche
- _1-2-3_ pour sélectionner un objet
- _A_ pour utilliser l'objet sélectionné
- _E_ pour intéragir avec les coffres

---

## Fonctionalités du jeu

Voici les différentes fonctionalités que vous pourrez utiliser dans notre jeu

- Se déplacer dans un espace 2D
- Intéragir avec différentes entités (coffres, ennemies, collectibles)
- Génération d'entité par le jouer (bombes, flèches, feu)
- Gestion d'une barre de vie et d'un compteur d'abricots
- Déplacement entre plusieurs salles, uniques les unes des autres

---

## Téléchargement

Vous pouver trouver une version a jour sur le github suivant <https://forge.univ-lyon1.fr/p2100444/lifapcda> ou le téléchargé avec la commande

    git clone https://forge.univ-lyon1.fr/p2100444/lifapcda.git

---

## Compilation

Vous trouverez les 3 commandes utiles afin de lancer notre jeu :

- afin de supprimer les anciens fichier de compilation

        make clean

- afin de créer les fichiers .o et le fichier .exe nécessaire au fonctionnement du jeu

        make

- pour lancer le jeu

        bin/mainSDL.exe

---

## Description de l'organisation de l'archive

Voici l'organisation de nos fichier à la racine :

- un répertoire _assest_
- un répertoire _bin_
- un répertoire _data_
- un répertoire _doc_
- un répertoire _include_
- un répertoire _library_
- un répertoire _obj_
- un répertoire _src_
- un fichier _Makefile_
- un fichier _Readme.txt_
- un fichier _Readme.md_

Concernant le contenu des différents répertoires :

- _assets_ : contient les différents textures
- _bin_ : contient le fichier .exe
- _data_ : contient le fichier .json qui gère la map
- _doc_ : contient la documentation doxygen
- _include_ : contient les différents fichiers .h
- _library_ : contient les librairies utilisées dans le projet
- _obj_ : contient les différents fichier .o
- _src_ : contient les différents fichier .cpp

---

## Source

-SDL2:
 <https://www.libsdl.org/download-2.0.php>

-SDL2 image:
 <https://www.libsdl.org/projects/SDL_image/>

-Mingw-w64:
 <https://www.mingw-w64.org>
