
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Listechainee/Listechainee.h"
#include "Graphique/libgraph.h"

#define SCREEN_WIDTH 900 
#define SCREEN_HEIGHT 700
#define SHIELDS 3
#define SHIELD_DATA 4
#define SHIELD_Y 570
#define SHIELD_MAX_LIFE 5
#define GAPS_BTWN_SHIELDS 3
#define SHIELD_IMG_FILE "../Lutins/invader_bouclier.bmp"
#define SHIP_IMG_FILE "../Lutins/invader_canon.bmp" 





int* SHIELD_WIDTH= NULL;
int* SHIELD_HEIGHT= NULL;
int* SHIP_WIDTH= NULL;
int* SHIP_HEIGHT= NULL;
int* INVADER_WIDTH= NULL;
int* INVADER_HEIGHT= NULL;
int shield[SHIELDS][SHIELD_DATA]={0};
entity_t ship; 
int ship_health = 3;
entity_t invader;
entity_list_t Invaders;
int shield_img;
int ship_img;
int invader_killed_img;
int invader_1_img_1;
int invader_1_img_2;
int invader_2_img_1;
int invader_2_img_2;
int invader_3_img_1;
int invader_3_img_2;




void init_shields()
{   
    
    SHIELD_WIDTH = malloc(sizeof(int));
    SHIELD_HEIGHT = malloc(sizeof(int));
    if (SHIELD_WIDTH == NULL || SHIELD_HEIGHT == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for SHIELD_WIDTH or SHIELD_HEIGHT\n");
        exit(1);
    }
    
    shield_img = chargerLutin(SHIELD_IMG_FILE, COULEUR_NOIR);
    tailleLutin(shield_img, SHIELD_WIDTH, SHIELD_HEIGHT);
    if (SHIELD_WIDTH == NULL || SHIELD_HEIGHT == NULL) {
        fprintf(stderr, "Error: SHIELD_WIDTH or SHIELD_HEIGHT is a NULL pointer\n");
        exit(1);
    }
    
    int shield_total_width = (*SHIELD_WIDTH) * SHIELDS;
    int space_left = SCREEN_WIDTH - shield_total_width;
    int even_space = space_left/GAPS_BTWN_SHIELDS; // 4 gaps
    shield[0][0] = even_space;
    shield[0][1] = SHIELD_Y;
    shield[0][2] = SHIELD_MAX_LIFE;
    


    for (int i = 0; i < SHIELDS; i++)
    {
        
        if(i < (SHIELDS - 1)){
            shield[i+1][0] = shield[i][0] + *SHIELD_WIDTH + even_space; // distance apart
            shield[i+1][1] = SHIELD_Y;
            shield[i+1][2] = SHIELD_MAX_LIFE;

        }
    }
    
}

void display_shields()
{
    for(int i=0; i<SHIELDS; i++){
        afficherLutin(shield_img , shield[i][0] , shield[i][1]);
    }
}

void init_ship()
{
    SHIP_WIDTH = malloc(sizeof(int));
    SHIP_HEIGHT = malloc(sizeof(int));
    ship_img = chargerLutin(SHIP_IMG_FILE, COULEUR_NOIR);
    tailleLutin(ship_img, SHIP_WIDTH, SHIP_HEIGHT);
    ship.x_coordinates = (SCREEN_WIDTH / 2) - ((*SHIP_WIDTH) / 2);
    ship.y_coordinates = (SCREEN_HEIGHT - ((*SHIP_HEIGHT) + 20));
    
}

void display_ship()
{    
    afficherLutin(ship_img , ship.x_coordinates, ship.y_coordinates);
}



int main(){
    
        
        creerSurface( SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders");
              
        init_shields();
        init_ship();
        printf("ok\n");
        display_shields();
        display_ship();
        printf("ok\n");
        majSurface();
        printf("ok\n");
        
        
        attendreEvenement();
        printf("ok\n");
        fermerSurface();

    
    return 0;
}
/*
void init(){
    init_ship();
    init_shields();
    init_invaders();
    display_shields();
    display_ship();
    display_invaders();
}
*/


/*
    int upper_bound = 10;
    srand(time(NULL)); // Seed the random number generator with the current time
    int random_number = rand() % (upper_bound + 1);
*/



