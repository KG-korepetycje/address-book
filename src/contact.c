#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

void print_contact(struct contact* contact) {
    printf("Name: %s\n", contact->name);
    printf("Address: %p\n", (void*)contact);
};
