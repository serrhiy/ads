#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  int data;
  struct node* previos;
  struct node* next;
} node;

typedef struct {
  struct node* first;
  struct node* last;
} linkedList;

linkedList* listInit() {
  linkedList* list = malloc(sizeof(linkedList));
  if (list == NULL) return NULL;
  *list = (linkedList){ NULL, NULL };
  return list;
}

node* nodeInit(int data, node* previos, node* next) {
  node* newNode = malloc(sizeof(node));
  if (newNode == NULL) return NULL;
  *newNode = (node){ data, previos, next };
  return newNode;
}

node* listPush(linkedList* list, int data) {
  node* newNode = nodeInit(data, list->last, NULL);
  if (newNode == NULL) return NULL;
  if (list->first == NULL) list->first = newNode;
  else list->last->next = newNode;
  list->last = newNode;
  return newNode;
}

void listDestroy(linkedList* list) {
  node* curent = list->first;
  node* next = NULL;
  while (curent != NULL) {
    next = curent->next;
    free(curent);
    curent = next;
  }
  free(list);
}

int calculate(linkedList* list) {
  int result = 1;
  node* first = list->first;
  node* last = list->last;
  while (first->next != NULL) {
    result *= (first->data + first->next->data + 2 * last->data);
    first = first->next;
    last = last->previos;
  }
  return result;
}

int main(int argc, char const *argv[]) {
  linkedList* list = listInit();
  if (list == NULL) {
    printf("Error: There is not enough memory");
    return 0;
  }
  int length, data, success = 1;
  while (1) {
    printf("Enter the count of elements you are going to enter: ");
    scanf("%d", &length);
    if (length > 1) break;
    printf("The value must be greater than 1\n");
  }
  for (int i = 1; i <= length; i++) {
    printf("Enter the element #%d: ", i);
    scanf("%d", &data);
    node* item = listPush(list, data);
    if (item == NULL) {
      printf("Error: There is not enough memory");
      success = 0;
      break;
    }
  }
  if (success) {
    printf("Result: %d\n", calculate(list));
  }
  listDestroy(list);
  return 0;
}