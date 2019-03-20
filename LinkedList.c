//
// Created by Devin on 3/20/2019.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* nextNode;
}node;

node* head;
node* tail;
node *current;

void printLList() {
    if (head != 0) {
        current = head;
        printf("head");

        while (current != tail->nextNode) {
            printf("->%d", current->value);
            current = current->nextNode;
        }
        printf("<-tail\n");
    } else {
        printf("List is empty\n");
    }
}

void insert(int value) {
    current = head;
    if (head == 0) { // if the list is empty
        head = (node*) malloc(sizeof(node));
        head->nextNode = 0;
        head->value = value;
        tail = head;
    } else { // if the list is not empty
        if (value < head->value) { // checks for insertion at beginning of list
            node *temp = head;
            head = (node*) malloc(sizeof(node));
            head->value = value;
            head->nextNode = temp;
        } else if (value >= tail->value){ // checks for insertion at end of list
            tail->nextNode = (node*) malloc(sizeof(node));
            tail = tail->nextNode;
            tail->value = value;
            tail->nextNode = 0;
        } else {
            while (value >= current->nextNode->value) { // while (value >= current->nextNode->value)    why doesn't this work?
                current = current->nextNode; // while value is greater than next value
            }

            node *temp = current->nextNode; // hold a temp node* to keep the rest of the list
            current->nextNode = (node *) malloc(sizeof(node)); // create a new node
            current = current->nextNode;

            current->value = value;
            current->nextNode = temp;
        }
    }
}

// deletion from index (zero based)
void delete(int index) {
    current = head;
    if (index == 0) { // deleting from beginning of list
        head = head->nextNode;
        free(current);
        current = 0;
    } else if (index > 0){
        for (int i = index; i > 1 && current != tail; i--) { // sets current equal to the node before the node we want to delete
            current = current->nextNode;
        }
        if (current == tail) { // if index is too large
            printf("index %d is too large\n", index);
        } else { // index is in bounds 1 to list.length
            if (current->nextNode == tail) tail = current; // deleting from end of list
            node *temp = current->nextNode;
            current->nextNode = current->nextNode->nextNode;
            free(temp);
        }
    } else { // if index is too small
        printf("index %d is too small\n", index);
    }
}

void freeList() {
    current = head;
    while (current != 0) {
        head = head->nextNode;
        free(current);
        current = head;
    }
    head = 0;
    tail = 0;
    current = 0;
}

// an empty list looks like a node *head and a node *tail pointing to the null pointer 0
void run_linked_list() {
    printf("Running linked list\n");

    head = 0; // initialize empty linked list
    tail = 0; // initialize empty list
    current = 0;

    insert(5);
    printLList();
    insert(4);
    printLList();
    insert(7);
    printLList();
    insert(2);
    printLList();
    insert(6);
    printLList();

    delete(4);
    printLList();
    delete(0);
    printLList();
    delete(2);
    printLList();
    delete(2);
    printLList();
    delete(1);
    printLList();
    delete(0);
    printLList();

    freeList();
    printf("\n");
}