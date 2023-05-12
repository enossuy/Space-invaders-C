#ifndef __LISTECHAINEE_H__
#define __LISTECHAINEE_H__

#include <stdbool.h>

typedef struct entity {
    int x_coordinates;
    int y_coordinates;
    int width;
    int height;
    int entity_id;
    int direction; /* 1 for right, -1 for left, 0 for static */
    int health;
} entity_t;

typedef struct Node {
    entity_t entity;
    struct Node* next_entity;
} Node_t;


typedef struct entity_list {
    Node_t* head;
    int size;
} entity_list_t;


entity_list_t* createLinkedList();
bool isEmpty(entity_list_t* list);
void push_to_head(entity_list_t* list, int x, int y, int id, int directory);
void pop_entity(entity_list_t* list, int x, int y);







#endif
