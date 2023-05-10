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


void push_to_head(entity_list_t* list, entity_t entity) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for a new node\n");
        exit(EXIT_FAILURE);
    }
    newNode->entity = entity;
    newNode->next_entity = list->head;
    list->head = newNode;
    list->size++;
}
void addToEnd(entity_list_t* list, int x, int y, int id) {
    // Allocate memory for new node and entity
    Node* newNode = (Node*) malloc(sizeof(Node));
    entity_t newEntity;
    
    // Populate new entity with given values
    newEntity.x_coordinates = x;
    newEntity.y_coordinates = y;
    newEntity.entity_id = id;
    
    // Assign new entity to new node
    newNode->entity = newEntity;
    newNode->next_entity = NULL;
    
    // If list is empty, set new node as head
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        // Find last node in list
        Node* lastNode = list->head;
        while (lastNode->next_entity != NULL) {
            lastNode = lastNode->next_entity;
        }
        
        // Add new node to end of list
        lastNode->next_entity = newNode;
    }
    
    // Increment list size
    list->size++;
}



void pop(entity_list_t list, int entity) {
    Node* curr_node = list.head;
    Node* prev_node = NULL;

    // Traverse the list to find the node with the matching entity ID
    while (curr_node != NULL && curr_node->entity.points != entity) {
        prev_node = curr_node;
        curr_node = curr_node->next_entity;
    }

    // If a node with the matching entity ID was found, remove it from the list
    if (curr_node != NULL) {
        if (prev_node == NULL) {
            // If the node to be removed is the head of the list
            list.head = curr_node->next_entity;
        } else {
            // If the node to be removed is not the head of the list
            prev_node->next_entity = curr_node->next_entity;
        }
        free(curr_node);
        list.size--;
    }
}
