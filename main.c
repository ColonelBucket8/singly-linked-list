#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *next;
    int data;
} Node;

Node *head = NULL;

Node *addNode(int data);

void printMenu();

void printList();


int removeNode(int arg1);

Node *insertNode(int arg1, int arg2);

int main(int argc, char **argv) {
    int option = -1;
    int arg1 = 0;
    int arg2 = 0;

    while (option != 5) {
        printMenu();

        int num_received = scanf("%d", &option);
        if (num_received == 1 && option > 0 && option <= 5) {
            switch (option) {
                case 1:
                    // Add operation
                    setbuf(stdout, 0);
                    printf("What data should I insert?:\n");
                    scanf("%d", &arg1);
                    Node *new = addNode(arg1);
                    break;
                case 2:
                    // Remove Operation
                    printf("What data should I remove?:\n");
                    scanf("%d", &arg1);
                    int success = removeNode(arg1);
                    if (!success) {
                        printf("Element not found\n");
                    }
                    break;
                case 3:
                    // Insert operation
                    printf("What data should I insert?:\n");
                    scanf("%d", &arg1);
                    printf("What position?:\n");
                    scanf("%d", &arg2);
                    new = insertNode(arg1, arg2);
                    if (new == NULL) {
                        printf("Failed to insert into list\n");
                    }
                    break;
                case 4:
                    printList();
                    break;
                case 5:
                    break;
            }
        }
    }

    return 0;
}

Node *insertNode(int data, int position) {
    Node *current = head;
    while (current != NULL && position != 0) {
        position--;
    }

    if (position != 0) {
        printf("Requested position too far into list\n");
        return NULL;
    }

    Node *new = malloc(sizeof(Node));
    if (new == NULL) {
        return NULL;
    }

    new->data = data;
    new->next = current->next;
    current->next = new;

    return new;
}

int removeNode(int data) {
    Node *current = head;
    Node *prev = head;

    while (current != NULL) {
        if (current->data == data) {
            // If current node is the list head
            if (current == head) {
                head = current->next;
            } else {
                prev->next = current->next;
                free(current);
                current = NULL;
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

Node *addNode(int data) {
    Node *new = NULL;
    // Two cases:
    // If the list is empty.
    if (head == NULL) {
        new = malloc(sizeof(Node));
        if (new == NULL) return NULL;

        new->data = data;
        head = new;
        new->next = NULL;
    } else {
        new = malloc(sizeof(Node));
        if (new == NULL)
            return NULL;

        new->data = data;
        new->next = head;
        head = new;
    }

    return NULL;
}

void printMenu() {
    setbuf(stdout, 0);
    printf("You have the following options:\n");
    printf("\t1. Add a node to the list.\n");
    printf("\t2. Remove a node from the list.\n");
    printf("\t3. Insert a node to the list.\n");
    printf("\t4. Print your list\n");
    printf("\t5. Quit.\n");
    return;
}

void printList() {
    Node *current = head;
    while (current != NULL) {
        setbuf(stdout, 0);
        printf("%d->", current->data);
        current = current->next;
    }

    setbuf(stdout, 0);
    printf("\n");
    return;
}
