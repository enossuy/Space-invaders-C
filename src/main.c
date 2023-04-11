
#include <stdio.h>
#include <unistd.h>
#include "Graphique/libgraph.h"

int main(){
    creerSurface(500,500,"Test");
        int lutin1=chargerLutin("/home/y/e/yelqasta/Envahisseurs/Lutins/invader_monstre1_1.bmp",COULEUR_NOIR);
//     do {afficherLutin(lutin1,200,200);
//     rectanglePlein (100,10, 50, 10,COULEUR_BLANC);    
//     majSurface();
//     sleep(10);
//         
//     } while(); 
    
    fermerSurface();
    return 0;
}
