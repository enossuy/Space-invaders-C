#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Listechainee.h"


entity_list_t* createLinkedList() {
    entity_list_t* list = (entity_list_t*)malloc(sizeof(entity_list_t));
    if (list == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for the linked list\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

bool isEmpty(entity_list_t* list) {
    return (list->size == 0);
}
void push_to_head(entity_list_t* list, int x, int y, int id, int directory) {
    Node_t* newNode = malloc(sizeof(Node_t));
    newNode->entity.x_coordinates = x;
    newNode->entity.y_coordinates = y;
    newNode->entity.entity_id = id;
    newNode->entity.direction = directory;
    newNode->next_entity = list->head;
    list->head = newNode;
    list->size++;
}


void addToEnd(entity_list_t* list, int x, int y, int id, int dir) {
    // Allocate memory for new node and entity
    Node_t* newNode = (Node_t*) malloc(sizeof(Node_t));
    entity_t newEntity;
    
    // Populate new entity with given values
    newEntity.x_coordinates = x;
    newEntity.y_coordinates = y;
    newEntity.entity_id = id;
    newEntity.direction = dir;

    
    // Assign new entity to new node
    newNode->entity = newEntity;
    newNode->next_entity = NULL;
    
    // If list is empty, set new node as head
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        // Find last node in list
        Node_t* lastNode = list->head;
        while (lastNode->next_entity != NULL) {
            lastNode = lastNode->next_entity;
        }
        
        // Add new node to end of list
        lastNode->next_entity = newNode;
    }
    
    // Increment list size
    list->size++;
}


void pop(entity_list_t* list, int x, int y) {
    Node_t* curr = list->head;
    Node_t* prev = NULL;

    while (curr != NULL) {
        if (curr->entity.x_coordinates == x && curr->entity.y_coordinates == y) {
            if (prev == NULL) { // Case where the first node is to be removed
                list->head = curr->next_entity;
            } else {
                prev->next_entity = curr->next_entity;
            }
            free(curr);
            list->size--;
            return;
        }
        prev = curr;
        curr = curr->next_entity;
    }
}

