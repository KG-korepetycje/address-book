#ifndef LIST_H
#define LIST_H

struct contact {
    char name[30];
    char surname[30];
    char phone[20];
    char group[50];
};


struct element {
    struct contact data;

    struct element* prev;
    struct element* next;
};


struct element* create_element(struct contact data);
void append(struct element** head, struct contact data);
void append_from_csv(struct element** head, char file_path[]);
void print_list(struct element* head);
void sort_list(struct element** head, int sort_type);
void free_list(struct element** head);

#endif
