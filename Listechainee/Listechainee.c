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
