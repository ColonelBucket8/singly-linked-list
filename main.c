#include <stdio.h>
#include <stdlib.h>

enum Action
{
  Add = 1,
  Remove,
  Insert,
  Pop,
  Shift,
  Print,
  Print_Reverse,
  Quit,
};

typedef struct
{
  void *next;
  int data;
} Node;

Node *head = NULL;

Node *insertNode(int data, int position)
{
  Node *current = head;
  while (current != NULL && position != 0)
  {
    position--;
  }

  if (position != 0)
  {
    printf("Requested position too far into list\n");
    return NULL;
  }

  Node *new = malloc(sizeof(Node));
  if (new == NULL)
  {
    return NULL;
  }

  new->data = data;
  new->next = current->next;
  current->next = new;

  return new;
}

int remove_node(int data)
{
  Node *current = head;
  Node *prev = head;

  while (current != NULL)
  {
    if (current->data == data)
    {
      // If current node is the list head
      if (current == head)
      {
        head = current->next;
        free(current);
        current = NULL;
      }
      else
      {
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

Node *add_node(int data)
{
  Node *new = NULL;
  // Two cases:
  // If the list is empty.
  if (head == NULL)
  {
    new = malloc(sizeof(Node));
    if (new == NULL)
      return NULL;

    new->data = data;
    head = new;
    new->next = NULL;
  }
  else
  {
    new = malloc(sizeof(Node));
    if (new == NULL)
      return NULL;

    new->data = data;
    new->next = head;
    head = new;
  }

  return NULL;
}

void print_menu()
{
  printf("You have the following options:\n");
  printf("\t1. Add a node to the list.\n");
  printf("\t2. Remove a node from the list.\n");
  printf("\t3. Insert a node to the list.\n");
  printf("\t4. Pop a node from the list.\n");
  printf("\t5. Shift a node from the list.\n");
  printf("\t6. Print your list\n");
  printf("\t7. Print your list in reverse\n");
  printf("\t8. Quit.\n");
  return;
}

void print_list()
{
  Node *current = head;

  if (current == NULL)
  {
    printf("List is empty. There is nothing to print.\n");
    return;
  }

  while (current != NULL)
  {
    printf("%d->", current->data);
    current = current->next;
  }

  printf("\n");
  return;
}

void print_list_reverse()
{
  Node *current = head;

  if (current == NULL)
  {
    printf("The list is empty.\n");
    return;
  }

  int temp_arr[1000];
  size_t index = 0;

  while (current != NULL)
  {
    temp_arr[index++] = current->data;
    current = current->next;
  }

  for (size_t i = index - 1; i > 0; i--)
  {
    printf("%d<-", temp_arr[i]);
  }

  printf("%d", temp_arr[0]);

  printf("\n");
}

int pop_list()
{
  Node *current = head;
  Node *prev = head;

  if (current == NULL)
  {
    printf("List is empty. There is nothing to pop\n");
    return 0;
  }

  // If current node is the head
  if (current->next == NULL)
  {
    free(current);
    current = NULL;

    head = NULL;

    return 1;
  }

  while (current->next != NULL)
  {
    prev = current;
    current = current->next;
  }

  prev->next = NULL;
  free(current);
  current = NULL;

  return 1;
}

int get_length()
{
  Node *current = head;
  int count = 0;

  while (current != NULL)
  {
    current = current->next;
    count++;
  }

  return count;
}

int shift_list()
{
  Node *current = head;

  if (current == NULL)
  {
    printf("Empty list. Nothing to shift.\n");

    return 0;
  }

  head = current->next;

  free(current);
  current = NULL;

  return 1;
}

int main(int argc, char **argv)
{
  int option = -1;
  int arg1 = 0;
  int arg2 = 0;

  while (option != Quit)
  {
    print_menu();

    int num_received = scanf("%d", &option);
    if (num_received == 1 && option > 0 && option < Quit)
    {
      switch (option)
      {
      case Add:
        printf("What data should I insert?:\n");
        scanf("%d", &arg1);
        Node *new = add_node(arg1);
        break;
      case Remove:
        printf("What data should I remove?:\n");
        scanf("%d", &arg1);
        int success = remove_node(arg1);
        if (!success)
        {
          printf("Element not found\n");
        }
        break;
      case Insert:
        printf("What data should I insert?:\n");
        scanf("%d", &arg1);
        printf("What position?:\n");
        scanf("%d", &arg2);
        new = insertNode(arg1, arg2);
        if (new == NULL)
        {
          printf("Failed to insert into list\n");
        }
        break;
      case Pop:
        pop_list();
        break;
      case Shift:
        shift_list();
        break;
      case Print:
        print_list();
        break;
      case Print_Reverse:
        print_list_reverse();
        break;
      }
    }
    else if (option != Quit)
    {
      printf("Invalid option. Please input again.\n");
    }
  }

  return 0;
}
