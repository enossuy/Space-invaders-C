
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <unistd.h>
#include "../Listechainee/Listechainee.h"
#include "Graphique/libgraph.h"
#include <SDL/SDL_ttf.h>

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
#define INVADERS_DX 3
#define INVADERS_DY 8
#define INVADERS_PER_ROW 12


int invaders_rows=5;








void starting_screen()
{
    creerSurface();
    chargerSurface();
}



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




entity_list_t* init_invaders(int invader_1_img_1,int invader_2_img_1,int invader_3_img_1,entity_t* Invaders, int direction)
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
void display_invaders(entity_list_t* init_invaders)
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
    bool edge_test = false;
    while (invader != NULL)
    {
        if (invader->entity.x_coordinates - INVADERS_DX <= 0 && invader->entity.direction == -1)
        {
            edge_test = true;
            break;
        }
        if (invader->entity.x_coordinates + INVADERS_DX >= SCREEN_WIDTH - 35 && invader->entity.direction == 1)
        {
            edge_test = true;
            break;
        }
        invader = invader->next_entity;
    }    
    if (edge_test)
    {
        move_invaders_down(invaders_list);
    }
    else
    {
        invader = invaders_list->head;
        while (invader != NULL)
        {
            invader->entity.x_coordinates +=  invader->entity.direction * INVADERS_DX;
            invader = invader->next_entity;
        }
    }
         
}

/*void move_invaders(entity_list_t* invaders_list)
{
    Node_t* invader = invaders_list->head;
    bool edge_test = false;

    while (invader != NULL)
    {
        if (invader->entity.x_coordinates - INVADERS_DX <= 20 && invader->entity.direction == -1)
        {
            edge_test = true;
            break;
        }
        if (invader->entity.x_coordinates + INVADERS_DX >= SCREEN_WIDTH - 30 && invader->entity.direction == 1)
        {
            edge_test = true;
            break;
        }

        switch (invader->entity.direction)
        {
            case -1:
                invader->entity.x_coordinates -= INVADERS_DX;
                break;

            case 1:
                invader->entity.x_coordinates += INVADERS_DX;
                break;

            default:
                break;
        }

        invader = invader->next_entity;
    }

    if (edge_test)
    {
        move_invaders_down(invaders_list);
    }
}
*/

/*

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
*/
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

void move_ship(int ship_img, entity_t* Ship,evenement event, char key)
{ 
    if (key=='g' && event== toucheBas )
    {
        if ( Ship->x_coordinates > 0)
        {
            Ship->x_coordinates -= 10;
        } 
    }
    else if (key=='h' &&  event== toucheBas  )
    {
        if ( (Ship->x_coordinates + 50 < SCREEN_WIDTH))
        {
            Ship->x_coordinates += 10;
            
        }
        
    }
    
    afficherLutin(ship_img,Ship->x_coordinates,Ship->y_coordinates);
}
void init_missiles(int missile_img, int ship_x, int ship_y, entity_list_t* missiles, char key, evenement event)
{
    if (key == 'r' && event == toucheHaut) {
        push_to_head(missiles, ship_x + 19, ship_y, missile_img, 0);
    }
}

void move_missiles(entity_list_t* missiles)
{
    Node_t* missile = missiles->head;
    while (missile != NULL) {
        missile->entity.y_coordinates -= 20;
        afficherLutin(missile->entity.entity_id, missile->entity.x_coordinates, missile->entity.y_coordinates);
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
    
    int x1_2= x1+width1;
    int y1_2= y1+height1;
    int x2_2= x2+width2;
    int y2_2= y2+height2;
    
   
    
    if (
            (
                (
                    (
                        (x1<=x2_2 && x1>=x2) 
                        ||                                                  //second entity coming from the left
                        (x1_2<=x2_2 && x1_2>=x2)
                    ) 
                    && 
                    (
                        (y1<=y2_2 && y1>=y2) 
                        ||                                                  //second entity coming from the right
                        (y1_2<=y2_2 && y1_2>=y2)
                    )
                )
            ) 
       )
    
/*    int x_min = x1 < x2 ? x1 : x2;
    int x_max = x1 > x2 ? x1 : x2;
    int y_min = y1 < y2 ? y1 : y2;
    int y_max = y1 > y2 ? y1 : y2;
    
    if (x_min + width1
  */  
        test=true;
    return test;
    
}

void collision(entity_list_t* list_1, entity_list_t* list_2) {
    if (list_1->head == NULL || list_2->head == NULL)
    {
        return;
    }
    Node_t* current_node_1 = list_1->head;
    
    while (current_node_1 != NULL) {
        Node_t* current_node_2 = list_2->head;
        while (current_node_2 != NULL) {
            printf("%d \n",hitbox_test(current_node_1->entity.x_coordinates, current_node_1->entity.y_coordinates, current_node_1->entity.height, current_node_1->entity.width, current_node_2->entity.x_coordinates, current_node_2->entity.y_coordinates, current_node_2->entity.height, current_node_2->entity.width));
            if (hitbox_test(current_node_1->entity.x_coordinates, current_node_1->entity.y_coordinates, current_node_1->entity.height, current_node_1->entity.width, current_node_2->entity.x_coordinates, current_node_2->entity.y_coordinates, current_node_2->entity.height, current_node_2->entity.width)) {
                // If the entities have collided, remove them from their respective lists
                printf("%d %d\n",current_node_1->entity.x_coordinates,current_node_1->entity.y_coordinates);
                pop(list_2, current_node_2->entity);
                printf("%d %d\n",current_node_2->entity.x_coordinates,current_node_2->entity.y_coordinates);
                pop(list_1, current_node_1->entity);
                
                
                // Exit the inner loop since we have already found a collision for this entity
                return;
            }
            current_node_2 = current_node_2->next_entity;
        }
        current_node_1 = current_node_1->next_entity;
    }
}







int main(){
    
        creerSurface( SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders");
        entity_t ship;
        entity_t Invaders;
        int SHIELD_HEIGHT=0;
        int SHIELD_WIDTH= 0;
        int ship_health = 3;
        int shield[SHIELDS][SHIELD_DATA];
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
        
        
        init_sprites(&shield_img, &ship_img, &ship_killed_img, &invader_killed_img, &invader_1_img_1, &invader_1_img_2, &invader_2_img_1, &invader_2_img_2, &invader_3_img_1, &invader_3_img_2, &missile_img, &bomb_img);
        entity_list_t* invaders_list = init_invaders( invader_1_img_1, invader_2_img_1, invader_3_img_1,&Invaders, direction);
        if (invaders_list == NULL) {
        printf("Failed to initialize invaders list.\n");
        return 1;
        }
        tailleLutin(shield_img, &SHIELD_WIDTH, &SHIELD_HEIGHT);
        while(invaders_list->head!=NULL){
        tailleLutin(invader_1_img_1, &invaders_list->head->entity.width, &invaders_list->head->entity.height);

        
            invaders_list->head=invaders_list->head->next_entity;
        }
        tailleLutin(ship_img, &ship.width, &ship.height);
    ship.x_coordinates = (SCREEN_WIDTH / 2) - (ship.width / 2);
    ship.y_coordinates = (SCREEN_HEIGHT - (ship.height) );

        char key = 'u';
        evenement event;
        entity_list_t missiles = *createLinkedList();
        entity_list_t bombs = *createLinkedList();

    while (1) {
        rectanglePlein(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COULEUR_NOIR);
        display_invaders(*invaders_list);
        display_shields(shield_img, SHIELD_WIDTH, shield);
        lireEvenement(&event, &key, NULL);
        init_missiles(missile_img, ship.x_coordinates + 19, ship.y_coordinates, &missiles, key, event);
        while (missiles.head != NULL) {
            tailleLutin(missile_img, &missiles.head->entity.width, &missiles.head->entity.height);
            missiles.head = missiles.head->next_entity;
        }
        move_missiles(&missiles);
        bombs = *init_bombs(bomb_img, invaders_list, &bombs, 5);
        while (bombs.head != NULL) {
            tailleLutin(bomb_img, &bombs.head->entity.width, &bombs.head->entity.height);
            bombs.head = bombs.head->next_entity;
        }
        move_bombs(&bombs);
        move_ship(ship_img, &ship, event, key);
        majSurface();
        move_invaders(invaders_list);
        collision(invaders_list, &missiles);
        usleep(50000);
        if (event == quitter) break;
    }
            
        
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



