#ifndef __LISTECHAINEE_H__
#define __LISTECHAINEE_H__


typedef struct {
    int x_coordinates;
    int y_coordinates;
    int speed;
    int direction;
    int points;/*1 for right, -1 for left*/
} entity_t;

typedef struct Node {
    entity_t entity;
    struct Node* next_entity;
} Node;

typedef struct entity_list {
    Node* head;
    int size;
} entity_list_t;

entity_list_t* createLinkedList();
bool isEmpty(entity_list_t* list);
void push_to_head(entity_list_t* list, entity_t entity);
void pop(entity_list_t list, int entity) ;








#endif
