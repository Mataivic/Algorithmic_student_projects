#include <stdlib.h>
#include <stdio.h>
#include "files_fct.h"

int main() { 

    printf("%s\n", "Création d'une file");
    File maFile = fileVide();

    printf("%s", "Test file vide : " );
    printf("%d\n", estFileVide(maFile));    

    printf("%s\n", "On enfile 3 fois : 4, 8, 15");
    maFile = enfiler(maFile, 4);
    maFile = enfiler(maFile, 8);
    maFile = enfiler(maFile, 15);

    printf("%s", "Test file vide : ");
    printf("%d\n", estFileVide(maFile));

    printf("%s", "Début de la file : ");
    printf("%d\n", getDebut(maFile));
    printf("%s", "Fin de la file : ");
    printf("%d\n", getFin(maFile));
    printf("%s", "Longueur de la file : ");
    printf("%d\n", getLongueur(maFile));
    printf("%s", "Affichage : ");
    afficherFile(maFile);    

    printf("%s\n", "On enfile encore 3 fois : 16, 23, 42");
    maFile = enfiler(maFile, 16);
    maFile = enfiler(maFile, 23);
    maFile = enfiler(maFile, 42);

    printf("%s", "Début de la pile : ");
    printf("%d\n", getDebut(maFile));
    printf("%s", "Fin de la file : ");
    printf("%d\n", getFin(maFile));
    printf("%s", "Longueur de la file : ");
    printf("%d\n", getLongueur(maFile));
    printf("%s", "Affichage : ");
    afficherFile(maFile);
    
    printf("%s\n", "On défile 1 fois");
    maFile = defiler(maFile);        

    printf("%s", "Début de la file : ");
    printf("%d\n", getDebut(maFile));
    printf("%s", "Fin de la file : ");
    printf("%d\n", getFin(maFile));
    printf("%s", "Longueur de la file : ");
    printf("%d\n", getLongueur(maFile));
    printf("%s", "Affichage : ");
    afficherFile(maFile);

    printf("%s\n", "Vidage de la file");
    videFile(maFile);

    printf("%s", "Test file vide : " );
    printf("%d\n", estFileVide(maFile));
   
    return EXIT_SUCCESS;
}
