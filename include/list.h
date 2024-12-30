
struct element {
    int data;

    struct element* prev;
    struct element* next;
};

struct element* create_element(int data);
void append(struct element* head, struct element* element);
void print_list(struct element* head);
void free_list(struct element* head);
