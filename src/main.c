
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "../Listechainee/Listechainee.h"
#include "Graphique/libgraph.h"

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 800
#define SHIELDS 3
#define SHIELD_Y 570
#define SHIELD_MAX_LIFE 5
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
#define INVADERS_DX 1
#define INVADERS_DY 6
#define INVADERS_PER_ROW 12
#define MISSILE_STARTING_POSITION 18
#define BOMBS_DY 5
#define RIGHT 1
#define LEFT -1
#define STATIC 0










void init_sprites(int* shield_img,int* ship_img,int* ship_killed_img,int* invader_killed_img,int* invader_1_img_1,int* invader_2_img_1,int* invader_3_img_1,int* missile_img,int* bomb_img)
{
    *shield_img = chargerLutin(SHIELD_IMG_FILE, COULEUR_NOIR);
    *ship_img = chargerLutin(SHIP_IMG_FILE, COULEUR_NOIR);
    *ship_killed_img= chargerLutin(SHIP_KILLED_IMG_FILE, COULEUR_NOIR);
    *invader_killed_img= chargerLutin(INVADER_KILLED_IMG_FILE, COULEUR_NOIR);
    *invader_1_img_1= chargerLutin(INVADER_1_IMG_1_FILE, COULEUR_NOIR);
    *invader_2_img_1= chargerLutin(INVADER_2_IMG_1_FILE, COULEUR_NOIR);
    *invader_3_img_1= chargerLutin(INVADER_3_IMG_1_FILE, COULEUR_NOIR);
    *missile_img= chargerLutin(MISSILE_IMG_FILE, COULEUR_NOIR);
    *bomb_img= chargerLutin(BOMB_IMG_FILE, COULEUR_NOIR);
}

entity_list_t* init_shields(int shield_img, int width )
{
    entity_list_t* shields_list= createLinkedList();
    
    int shield_total_width = width * SHIELDS;
    int space_left = SCREEN_WIDTH - shield_total_width;
    int even_space = space_left/(SHIELDS+1); // 4 gaps
    for (int i=0; i<SHIELDS; i++)
    {
        push_to_head(shields_list, even_space + i*even_space + ((i*width)-(i%1)*width), SHIELD_Y, shield_img, STATIC);
    }
    return shields_list;
}


entity_list_t* init_invaders(int invader_1_img_1,int invader_2_img_1,int invader_3_img_1, int direction)
{
    entity_list_t* invaders_list= createLinkedList();
    
    for(int i = 0 ; i < INVADERS_PER_ROW; i++)
    {
        push_to_head(invaders_list, i * 50 , 200,invader_1_img_1,direction);
        push_to_head(invaders_list, i * 50 , 260,invader_2_img_1,direction);
        push_to_head(invaders_list, i * 50 , 320,invader_3_img_1,direction);
    }
    return invaders_list;
    
}
void display_entity(entity_list_t list)
{
    Node_t *element = list.head;
    while(element != NULL)
    { 
        afficherLutin(element->entity.entity_id,element->entity.x_coordinates,element->entity.y_coordinates);
        element = element->next_entity;
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

void init_missiles(int missile_img, int ship_x, int ship_y, entity_list_t* missiles,char key, evenement event)
{
        if (key=='r' && event== toucheBas){
            if(missiles->head!=NULL)
            {
                if(missiles->head->entity.y_coordinates < 700)
                    push_to_head(missiles,ship_x,ship_y,missile_img,0);
            }
            else
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




void init_dimensions(entity_list_t* list, int height, int width)
{
    Node_t *entity = list->head;
            while (entity != NULL)
            {
                entity->entity.height = height;
                entity->entity.width = width;
                entity = entity->next_entity;
            }
}

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
     
        test=true;
    return test;
    
}


entity_list_t* init_bombs(int bomb_img, entity_list_t* invaders, int width, int height,int random_number)
{
    entity_list_t* bombs_list= createLinkedList();
    
    Node_t* invader = invaders->head;
    while (invader != NULL) {
        if (random_number==(rand()%20)){
        // Generate random x and y coordinates based on invader position
            int x = invader->entity.x_coordinates + width/2 ; // random offset of up to 10 pixels from invader's x position
            int y = invader->entity.y_coordinates + height ; // bombs appear just below the invader

        // Create a new bomb entity with the specified image and coordinates
            entity_t bomb = { .entity_id = bomb_img, .x_coordinates = x, .y_coordinates = y };

        // Add the new bomb entity to the bombs list
            push_to_head(bombs_list, bomb.x_coordinates, bomb.y_coordinates, bomb.entity_id,0);
            
        }

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
                bomb->entity.y_coordinates += BOMBS_DY;

                bomb = bomb->next_entity;
                
            }
}


void collision(entity_list_t* list_1, entity_list_t* list_2) {
    if (list_1->head == NULL || list_2->head == NULL) {
        return;
    }
    Node_t* current_node_1 = list_1->head;
    
    while (current_node_1 != NULL) {
        Node_t* current_node_2 = list_2->head;
        while (current_node_2 != NULL) {
            if (hitbox_test(current_node_1->entity.x_coordinates, current_node_1->entity.y_coordinates, current_node_1->entity.height, current_node_1->entity.width, current_node_2->entity.x_coordinates, current_node_2->entity.y_coordinates, current_node_2->entity.height, current_node_2->entity.width)) {
                // If the entities have collided, remove them from their respective lists
                pop_head(list_1, current_node_1->entity.x_coordinates, current_node_1->entity.y_coordinates);
                
                pop_head(list_2, current_node_2->entity.x_coordinates, current_node_2->entity.y_coordinates);
                
                return;
                
                // Update current_node_2 since we just removed an entity from list_2
                current_node_2 = list_2->head;
                
                // Exit the inner loop since we have already found a collision for this entity
                
            }
            current_node_2 = current_node_2->next_entity;
        }
        current_node_1 = current_node_1->next_entity;
    }
}
/*
void ship_collision(entity_list_t* invaders,entity_list_t* bombs, entity_t )
{   
    if  
}
*/
int main(){
    
        creerSurface( SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders");
        entity_t ship;
        int random_number=5;
        int SHIELD_HEIGHT=0;
        int INVADER_WIDTH= 0;
        int INVADER_HEIGHT=0;
        int SHIELD_WIDTH= 0;
        int MISSILE_WIDTH=0;
        int MISSILE_HEIGHT=0;
        int BOMB_HEIGHT=0;
        int BOMB_WIDTH=0;
        int ship_health = 3;
        int shield_img;
        int ship_img;
        int ship_killed_img;
        int invader_killed_img;
        int invader_1_img_1;;
        int invader_2_img_1;
        int invader_3_img_1;
        int missile_img;
        int bomb_img;
        int direction= RIGHT;
        entity_list_t* missiles;
        missiles = (entity_list_t*) malloc(sizeof(entity_list_t));
        
        srand(time(NULL));
        init_sprites(&shield_img, &ship_img, &ship_killed_img, &invader_killed_img, &invader_1_img_1, &invader_2_img_1, &invader_3_img_1, &missile_img,&bomb_img);
        entity_list_t* invaders_list = init_invaders( invader_1_img_1, invader_2_img_1, invader_3_img_1, direction);
        entity_list_t* shields_list = init_shields(shield_img, SHIELD_WIDTH);
        tailleLutin(shield_img, &SHIELD_WIDTH, &SHIELD_HEIGHT);
        tailleLutin(invader_1_img_1, &INVADER_WIDTH, &INVADER_HEIGHT);
        tailleLutin(bomb_img, &BOMB_WIDTH, &BOMB_HEIGHT);
        tailleLutin(shield_img, &SHIELD_WIDTH, &SHIELD_HEIGHT);
        init_dimensions(invaders_list, INVADER_HEIGHT, INVADER_WIDTH);
        
        init_dimensions(missiles, MISSILE_HEIGHT, MISSILE_WIDTH);
        entity_list_t* bombs_list=init_bombs( bomb_img, invaders_list, INVADER_WIDTH, INVADER_HEIGHT, random_number);
        init_dimensions(bombs_list, BOMB_HEIGHT, BOMB_WIDTH);
        tailleLutin(ship_img, &ship.width, &ship.height);
        ship.x_coordinates = (SCREEN_WIDTH / 2) - (ship.width / 2);
        ship.y_coordinates = (SCREEN_HEIGHT - (ship.height) );
        char key;
        evenement event;
        while (1){
        
        rectanglePlein (0, 0, SCREEN_WIDTH,  SCREEN_HEIGHT,  COULEUR_NOIR);
        display_entity(*invaders_list );
        display_entity(*shields_list );
//         display_ship(ship_img);
        lireEvenement(&event, &key, NULL);
        init_missiles(missile_img, ship.x_coordinates + MISSILE_STARTING_POSITION, ship.y_coordinates, missiles,key,event);
        move_missiles(missiles);
        move_bombs(bombs_list);
        move_ship(ship_img, &ship, event, key);
        majSurface();
        SDL_Delay(20);
        move_invaders(invaders_list);
        collision(missiles,invaders_list);
        collision(missiles,bombs_list);
        collision(missiles,shields_list);
        collision(shields_list,bombs_list);

    

//         if (invader_shield_collision( invader,  shields[0][SHIELD_DATA] )== )
        
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
*
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


