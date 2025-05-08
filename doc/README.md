# LIFAPCDA-projet

###### Jérémy BOUILLY | Adrien SALERIN | Louis MOREL

Notre objectif avec ce projet est de créer un "Zelda-like" en 2D vu du dessus avec un système de combat, des coffres et des déplacement dans differente pièces.

---

## - Fonctionnement

---

## - Visualisation
---

## - Téléchargement

Vous pouver trouver une version a jour sur mon github à <https://forge.univ-lyon1.fr/p2100444/lifapcda> ou le téléchargé avec la commande

    git clone https://forge.univ-lyon1.fr/p2100444/lifapcda.git

---

## - Installation / compilation

pour que le programme fonctionne ils vus faudra SDL2, SDL2 image et Mingw (lien dans l'onglet sources)

afin de le compiler en mode debug (est plus rapide a compilé) il faudra créer un dossier debug dans le dossier bin et y mettre les dll qu'il y a dans le fichier dll utiliser la commande(en remplacent [SDL2 include] par la position du dossier include de SDL2 sur votre ordinateur):

    g++ -c src/*.cpp -std=c++14 -g -Wall -m64 -I include -I [SDL2 include]  && g++ *.o -o bin/debug/main -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image && start bin/debug/main

afin de le compiler en mode release (prend moins de place une fois compilé) il faudra créer un dossier release dans le dossier bin et y mettre les dll qu'il y a dans le fichier dll utiliser la commande(en remplacent [SDL2 include] par la position du dossier include de SDL2 sur votre ordinateur):

    g++ -c src/*.cpp -std=c++14 -O3 -Wall -m64 -I include -I [SDL2 include]  && g++ *.o -o bin/release/main -s -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image && start bin/release/main

---

## - Source

-SDL2:
 <https://www.libsdl.org/download-2.0.php>

-SDL2 image:
 <https://www.libsdl.org/projects/SDL_image/>

-Mingw-w64:
 <https://www.mingw-w64.org>
