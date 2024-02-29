#include <stdlib.h>
#include <stdio.h>

typedef struct linkedList {
  int data;
  struct linkedList* prev;
  struct linkedList* next;
} linkedList;

linkedList* listInit() {
  return NULL;
}

linkedList* listPush(linkedList* list, int data) {
  linkedList* node = malloc(sizeof(linkedList));
  if (node == NULL) return NULL;
  if (list == NULL) {
    *node = (linkedList){ data, node, node };
    return node;
  }
  linkedList* tail = list->prev;
  *node = (linkedList){ data, tail, list };
  tail->next = node;
  list->prev = node;
  return node;
}

void listDestroy(linkedList* list) {
  linkedList* head = list;
  linkedList* tail = list->prev;
  while (head != tail) {
    head = head->next;
    free(head->prev);
  }
  free(head);
}

int calculate(linkedList* list) {
  linkedList* tail = list->prev;
  linkedList* head = list;
  linkedList* first = list;
  double result = 1;
  while (tail != first) {
    result *= (tail->data + tail->prev->data + 2 * head->data);
    tail = tail->prev;
    head = head->next;
  }
  return result;
}

int main(int argc, char const *argv[]) {
  linkedList* list = listInit();
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
    list = listPush(list, data);
    if (list == NULL) {
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

// linkedList* listInit(int data) {
//   linkedList* list = malloc(sizeof(linkedList));
//   if (list == NULL) return NULL;
//   *list = (linkedList){ data, list, list };
//   return list;
// }

// linkedList* listPush(linkedList* list, int data) {
//   linkedList* node = malloc(sizeof(linkedList));
//   if (node == NULL) return NULL;
//   linkedList* tail = list->prev;
//   *node = (linkedList){ data, tail, list };
//   tail->next = node;
//   list->prev = node;
//   return node;
// }