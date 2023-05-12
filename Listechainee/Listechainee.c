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





void pop_head(entity_list_t* list, int x, int y) {
    if (list->head == NULL) {
        // If the list is empty, return without doing anything
        return;
    }
    
    Node_t* current_node = list->head;
    Node_t* previous_node = NULL;
    
    while (current_node != NULL) {
        if (current_node->entity.x_coordinates == x && current_node->entity.y_coordinates == y) {
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


