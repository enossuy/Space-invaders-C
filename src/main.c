
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
#define DX_BTWN_INVADERS 15
#define INVADER_1_IMG_1_FILE "../Lutins/invader_monstre1_1.bmp"
#define INVADER_1_IMG_2_FILE "../Lutins/invader_monstre1_2.bmp"
#define INVADER_2_IMG_1_FILE "../Lutins/invader_monstre2_1.bmp"
#define INVADER_2_IMG_2_FILE "../Lutins/invader_monstre2_2.bmp"
#define INVADER_3_IMG_1_FILE "../Lutins/invader_monstre3_1.bmp"
#define INVADER_3_IMG_2_FILE "../Lutins/invader_monstre3_2.bmp"
#define SHIELD_IMG_FILE "../Lutins/invader_bouclier.bmp"
#define SHIP_IMG_FILE "../Lutins/invader_canon.bmp"
#define SHIP_KILLED_IMG_FILE "../Lutins/invader_canon_ferraille.bmp"
#define MISSILE_IMG_FILE "../Lutins/invader_missile.bmp"
#define INVADER_KILLED_IMG_FILE "../Lutins/invader_monstre_bouillie.bmp"
#define DAMAGE_IMG_D "../Lutins/invader_bombe.bmp"
#define INVADERS_DY 15
#define INVADERS_PER_ROW 8


int invaders_rows=5;


int* SHIELD_WIDTH= NULL;
int* SHIELD_HEIGHT= NULL;
int* SHIP_WIDTH= NULL;
int* SHIP_HEIGHT= NULL;
int* INVADER_WIDTH= NULL;
int* INVADER_HEIGHT= NULL;
int shield[SHIELDS][SHIELD_DATA]={0};
entity_t ship; 
int ship_health = 3;
entity_t Invaders;




void init_sprites(int* shield_img,int* ship_img,int* ship_killed_img,int* invader_killed_img,int* invader_1_img_1,int* invader_1_img_2,int* invader_2_img_1,int* invader_2_img_2,int* invader_3_img_1,int* invader_3_img_2,int* missile_img)
{
    *shield_img = chargerLutin(SHIELD_IMG_FILE, COULEUR_NOIR);
    *ship_img = chargerLutin(SHIP_IMG_FILE, COULEUR_NOIR);
    *ship_killed_img= chargerLutin(SHIP_KILLED_IMG_FILE, COULEUR_NOIR);
    *invader_killed_img= chargerLutin(INVADER_KILLED_IMG_FILE, COULEUR_NOIR);
    *invader_1_img_1= chargerLutin(INVADER_1_IMG_1_FILE, COULEUR_NOIR);
    *invader_1_img_2= chargerLutin(INVADER_1_IMG_2_FILE, COULEUR_NOIR);
    *invader_2_img_1= chargerLutin(INVADER_2_IMG_1_FILE, COULEUR_NOIR);
    *invader_2_img_2= chargerLutin(INVADER_2_IMG_2_FILE, COULEUR_NOIR);
    *invader_3_img_1= chargerLutin(INVADER_3_IMG_1_FILE, COULEUR_NOIR);
    *invader_3_img_2= chargerLutin(INVADER_3_IMG_2_FILE, COULEUR_NOIR);
    *missile_img= chargerLutin(MISSILE_IMG_FILE, COULEUR_NOIR);
}


void display_shields(int shield_img)
{   
    
    SHIELD_WIDTH = malloc(sizeof(int));
    SHIELD_HEIGHT = malloc(sizeof(int));
    if (SHIELD_WIDTH == NULL || SHIELD_HEIGHT == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for SHIELD_WIDTH or SHIELD_HEIGHT\n");
        exit(1);
    }
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
            shield[i+1][0] = shield[i][0] + (*SHIELD_WIDTH) + even_space; // distance apart
            shield[i+1][1] = SHIELD_Y;
            shield[i+1][2] = SHIELD_MAX_LIFE;
        }
        afficherLutin(shield_img, shield[i][0],shield[i][1]);
    }
    
}

void display_ship(int ship_img)
{
    SHIP_WIDTH = malloc(sizeof(int));
    SHIP_HEIGHT = malloc(sizeof(int));
    tailleLutin(ship_img, SHIP_WIDTH, SHIP_HEIGHT);
    ship.x_coordinates = (SCREEN_WIDTH / 2) - ((*SHIP_WIDTH) / 2);
    ship.y_coordinates = (SCREEN_HEIGHT - ((*SHIP_HEIGHT) + 20));
    afficherLutin(ship_img , ship.x_coordinates, ship.y_coordinates);
    
}


entity_list_t* init_invaders(int invader_1_img_1,int invader_1_img_2,int invader_2_img_1,int invader_2_img_2,int invader_3_img_1,int invader_3_img_2,entity_t* Invaders)
{
    entity_list_t* invaders_list= createLinkedList();
    Invaders->direction = 1;
    Invaders->speed = 1;
    Invaders->killed = 1;
    Invaders->state_speed = 1000;
    Invaders->x_coordinates = 0;
    Invaders->y_coordinates = 30;
    for(int i = 0 ; i < INVADERS_PER_ROW; i++)
    {
        addToEnd(invaders_list, i * 30 , 200,invader_1_img_1);
        addToEnd(invaders_list, i * 30 , 260,invader_2_img_1);
        addToEnd(invaders_list, i * 30 , 320,invader_3_img_1);
    }
    return invaders_list;
    
}
void display_invaders(entity_list_t init_invaders)
{
    Node *monstre = init_invaders.head;
    while(monstre != NULL)
    {
    
        afficherLutin(monstre->entity.entity_id,monstre->entity.x_coordinates,monstre->entity.y_coordinates);
        monstre->next_entity;
    }
    }

int main(){
    
        creerSurface( SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders");
        int shield_img;
        int ship_img;
        int ship_killed_img;
        int invader_killed_img;
        int invader_1_img_1;
        int invader_1_img_2;
        int invader_2_img_1;
        int invader_2_img_2;
        int invader_3_img_1;
        int invader_3_img_2;
        int missile_img;
        
        init_sprites(&shield_img, &ship_img, &ship_killed_img, &invader_killed_img, &invader_1_img_1, &invader_1_img_2, &invader_2_img_1, &invader_2_img_2, &invader_3_img_1, &invader_3_img_2, &missile_img);
        entity_list_t* invaders_list = init_invaders( invader_1_img_1, invader_1_img_2, invader_2_img_1, invader_2_img_2, invader_3_img_1, invader_3_img_2,&Invaders);
        display_invaders(*invaders_list );
        display_shields(shield_img);
        display_ship(ship_img);
        majSurface();   
        attendreEvenement();
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



