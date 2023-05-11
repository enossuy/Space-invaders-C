
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <unistd.h>
#include "../Listechainee/Listechainee.h"
#include "Graphique/libgraph.h"

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 800
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
#define BOMB_IMG_FILE "../Lutins/invader_bombe.bmp"
#define INVADERS_DX 20
#define INVADERS_DY 15
#define INVADERS_PER_ROW 12


int invaders_rows=5;





entity_t Invaders;
int shield[SHIELDS][SHIELD_DATA];



void init_sprites(int* shield_img,int* ship_img,int* ship_killed_img,int* invader_killed_img,int* invader_1_img_1,int* invader_1_img_2,int* invader_2_img_1,int* invader_2_img_2,int* invader_3_img_1,int* invader_3_img_2,int* missile_img, int* bomb_img)
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
    *bomb_img= chargerLutin(BOMB_IMG_FILE, COULEUR_NOIR);
}


void display_shields(int shield_img, int SHIELD_WIDTH, int shield[SHIELDS][SHIELD_DATA] )
{   
    
    int shield_total_width = SHIELD_WIDTH * SHIELDS;
    int space_left = SCREEN_WIDTH - shield_total_width;
    int even_space = space_left/GAPS_BTWN_SHIELDS; // 4 gaps
    shield[0][0] = even_space;
    shield[0][1] = SHIELD_Y;
    shield[0][2] = SHIELD_MAX_LIFE;
    


    for (int i = 0; i < SHIELDS; i++)
    {
        
        if(i < (SHIELDS - 1)){
            shield[i+1][0] = shield[i][0] + SHIELD_WIDTH + even_space; // distance apart
            shield[i+1][1] = SHIELD_Y;
            shield[i+1][2] = SHIELD_MAX_LIFE;
        }
        afficherLutin(shield_img, shield[i][0],shield[i][1]);
    }
    
}




entity_list_t* init_invaders(int invader_1_img_1,int invader_1_img_2,int invader_2_img_1,int invader_2_img_2,int invader_3_img_1,int invader_3_img_2,entity_t* Invaders, int direction)
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
        push_to_head(invaders_list, i * 50 , 200,invader_1_img_1,1);
        push_to_head(invaders_list, i * 50 , 260,invader_2_img_1,1);
        push_to_head(invaders_list, i * 50 , 320,invader_3_img_1,1);
    }
    return invaders_list;
    
}
void display_invaders(entity_list_t init_invaders)
{
    Node_t *invader = init_invaders.head;
    while(invader != NULL)
    { 
        afficherLutin(invader->entity.entity_id,invader->entity.x_coordinates,invader->entity.y_coordinates);
        invader = invader->next_entity;
    }
}


void move_invaders_down(entity_list_t* invaders_list)
{
    Node_t* invader = invaders_list->head;
    while(invader != NULL)
    {
        invader->entity.y_coordinates += INVADERS_DY;
        invader->entity.direction *= (-1);
        invader = invader->next_entity;
    }
}

void move_invaders(entity_list_t* invaders_list)
{
    Node_t* invader = invaders_list->head;
    while (invader != NULL)
    {
        switch (invader->entity.direction)
        {
            case 1:
                if (invader->entity.x_coordinates + INVADERS_DX >= SCREEN_WIDTH - 30)
                {
                    move_invaders_down(invaders_list);
                    return;
                }
                invader->entity.x_coordinates += INVADERS_DX;
                break;
            case -1:
                if (invader->entity.x_coordinates - INVADERS_DX <= 20)
                {
                    invader->entity.x_coordinates -= INVADERS_DX;
                    move_invaders_down(invaders_list);
                    return;
                }
                invader->entity.x_coordinates -= INVADERS_DX;
                break;
            default:
                break;
        }
        invader = invader->next_entity;
    }
}


entity_list_t* init_bombs(int bomb_img, entity_list_t* invaders, entity_list_t* bombs, int bombs_max)
{
    entity_list_t* bombs_list= createLinkedList();
    srand(time(NULL));
    int i = 0;
    Node_t* invader = invaders->head;
    while (i < bombs_max && invader != NULL) {
        // Generate random x and y coordinates based on invader position
        int x = invader->entity.x_coordinates + (rand() % 20) - 10; // random offset of up to 10 pixels from invader's x position
        int y = invader->entity.y_coordinates + 10; // bombs appear just below the invader

        // Create a new bomb entity with the specified image and coordinates
        entity_t bomb = { .entity_id = bomb_img, .x_coordinates = x, .y_coordinates = y };

        // Add the new bomb entity to the bombs list
        push_to_head(bombs, bomb.x_coordinates, bomb.y_coordinates, bomb.entity_id,0);

        i++;
        invader = invader->next_entity;
    }
    return bombs_list;
}
/*

void move_bombs(entity_list_t* bombs)
{
    
        Node_t *bomb = bombs->head;
            while (bomb != NULL)
            {
                afficherLutin(bomb->entity.entity_id,bomb->entity.x_coordinates,bomb->entity.y_coordinates);
                bomb->entity.y_coordinates += INVADERS_DY;

                bomb = bomb->next_entity;
                
            }
}
*/
void move_ship(int ship_img, entity_t* Ship,evenement event, char key)
{ 
    if (event== toucheBas && Ship->x_coordinates > 0)
    {
        if (key=='g' && Ship->x_coordinates > 0)
        {
            Ship->x_coordinates -= 10;
        } 
    }
    else if (event== toucheBas && Ship->x_coordinates + 50 < SCREEN_WIDTH )
    {
        if ( key=='h' && (Ship->x_coordinates + 50 < SCREEN_WIDTH))
        {
            Ship->x_coordinates += 10;
            
        }
        else ;
        
    }
    
    afficherLutin(ship_img,Ship->x_coordinates,Ship->y_coordinates);
}

void init_missiles(int missile_img, int ship_x, int ship_y, entity_list_t* missiles,char key, evenement event)
{
        if (key=='r' && event== toucheBas){
        push_to_head(missiles,ship_x,ship_y,missile_img,0);
        }
    
}
void move_missiles(entity_list_t* missiles)
{
    
        Node_t *missile = missiles->head;
            while (missile != NULL)
            {
                afficherLutin(missile->entity.entity_id,missile->entity.x_coordinates,missile->entity.y_coordinates);
                missile->entity.y_coordinates -= INVADERS_DY;

                missile = missile->next_entity;
                
            }
}

/*
bool invader_shield_collision(entity invader, int shields[i][SHIELD_DATA]  )
        
        bool b = false;
        if (invader.x_coordinates == shields[i][0] && invader.y_coordinates == shields[i][1] ){
            printf("ok\n");
            b = true;
        }
    return b;
}
*/

bool hitbox_test(int x1, int y1, int height1, int width1, int x2, int y2, int height2, int width2)
{   bool test=false;
    if ( ((((x1<=x2+width2 && x1>=x2) || (x1+width1<=x2+width2 && x1+width1>=x2)) && ((y1<=y2+height2 && y1>=y2) || (y1+height1<=y2+height2 && y1+height1>=y2)))) ){ test=true;}
    return test;
    
}

void collision(entity_list_t* list_1, entity_list_t* list_2){
    Node_t *entity_1 = list_1->head;
    Node_t *entity_2 = list_2->head;
    while(entity_2 != NULL)
    {
        while(entity_1 != NULL)
        {
            if (hitbox_test(entity_2->entity.x_coordinates, entity_2->entity.y_coordinates, entity_2->entity.height, entity_2->entity.width, entity_1->entity.x_coordinates, entity_1->entity.y_coordinates, entity_1->entity.height, entity_1->entity.width))
            {   
                pop(list_2, entity_2->entity);
                pop(list_1,entity_1->entity);
            }
            entity_1 = entity_1->next_entity;  // update missile pointer to next node
        }
        entity_2 = entity_2->next_entity;  // update invader pointer to next node
    }
}






int main(){
    
        creerSurface( SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders");
        entity_t ship;
        
        int SHIELD_HEIGHT=0;
        int SHIELD_WIDTH= 0;
        int ship_health = 3;
        
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
        int bomb_img;
        int direction= 1;
        entity_list_t missiles;
        entity_list_t bombs;
        
        init_sprites(&shield_img, &ship_img, &ship_killed_img, &invader_killed_img, &invader_1_img_1, &invader_1_img_2, &invader_2_img_1, &invader_2_img_2, &invader_3_img_1, &invader_3_img_2, &missile_img, &bomb_img);
        entity_list_t* invaders_list = init_invaders( invader_1_img_1, invader_1_img_2, invader_2_img_1, invader_2_img_2, invader_3_img_1, invader_3_img_2,&Invaders, direction);
        tailleLutin(shield_img, &SHIELD_WIDTH, &SHIELD_HEIGHT);
        
        tailleLutin(ship_img, &ship.width, &ship.height);
        ship.x_coordinates = (SCREEN_WIDTH / 2) - (ship.width / 2);
        ship.y_coordinates = (SCREEN_HEIGHT - (ship.height) );
        while (1){
        char key='u';
        evenement event;
        rectanglePlein (0, 0, SCREEN_WIDTH,  SCREEN_HEIGHT,  COULEUR_NOIR);
        
        display_invaders(*invaders_list );
        display_shields(shield_img,SHIELD_WIDTH,shield[SHIELDS][SHIELD_DATA]);
//         display_ship(ship_img);
        lireEvenement(&event, &key, NULL);
        init_missiles(missile_img, ship.x_coordinates +20, ship.y_coordinates, &missiles,key,event);
        move_missiles(&missiles);
        bombs=*init_bombs(bomb_img, invaders_list, &bombs, 5);
//         move_bombs(&bombs);
//         move_missiles(&missiles);
        move_ship(ship_img,&ship,event,key);
        majSurface();
        move_invaders(invaders_list);
        collision(invaders_list,&missiles);
        afficherLutin(bombs.head->entity.entity_id,bombs.head->entity.x_coordinates,bombs.head->entity.y_coordinates);

//         if (invader_shield_collision( invader,  shields[0][SHIELD_DATA] )== )
        usleep(100000);
        if (event==quitter) break;
        }
        fermerSurface();
        
    return 0;
}


/* while(monstre!=NULL)
 * {
 *  while(missile!=NULL)
 *  {
 *      if(hitbox)
 *          {
 *              pop(monstre);
 *              pop(missile);
 *              }
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



