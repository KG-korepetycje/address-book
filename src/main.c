#include <stdlib.h>
#include <string.h>

#include "contact.h"
#include "list.h"


int main() {
    // Create some sample contacts
    struct contact* contact1 = malloc(sizeof(struct contact));
    strcpy(contact1->name, "John Doe");

    struct contact* contact2 = malloc(sizeof(struct contact));
    strcpy(contact2->name, "Jane Smith");
    
    // Initialize the list
    struct list* list = malloc(sizeof(struct list));
    list->head = NULL;
    list->tail = NULL;
    
    // Add contacts to the list
    struct element* element1 = create_element(contact1);
    struct element* element2 = create_element(contact2);
    insert_element(list, element1);
    insert_element(list, element2);
    
    // Print the list
    print_list(list);
    
    // Clean up
    cleanup(list);

    return 0;
}
