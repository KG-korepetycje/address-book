#ifndef LIST_H
#define LIST_H

#include "contact.h"

struct element {
    struct contact* data;
    struct element* prev;
    struct element* next;
};

struct list {
    struct element* head;
    struct element* tail;
};

struct element* create_element(struct contact* contact_data);
void insert_element(struct list* list, struct element* element);
void print_list(struct list* list);
void cleanup(struct list* list);

#endif
