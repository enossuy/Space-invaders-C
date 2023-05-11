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


void pop(entity_list_t* list, entity_t entity) {
    if (list->head == NULL) {
        // If the list is empty, return without doing anything
        return;
    }
    
    Node_t* current_node = list->head;
    Node_t* previous_node = NULL;
    
    while (current_node != NULL) {
        if (current_node->entity.entity_id == entity.entity_id) {
            // If we found the entity to remove, update the previous node's next pointer
            if (previous_node == NULL) {
                // If the entity is the head of the list, update the head pointer
                list->head = current_node->next_entity;
            } else {
                previous_node->next_entity = current_node->next_entity;
            }
            
            // Free the memory for the removed node and decrement the list's size
            free(current_node);
            list->size--;
            return;
        }
        
        // Update the current and previous nodes
        previous_node = current_node;
        current_node = current_node->next_entity;
    }
}



