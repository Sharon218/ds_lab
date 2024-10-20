#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  Node *front;
  Node *rear;
} DQ;

void insert_begin(DQ *dq, int data);
void insert_end(DQ *dq, int data);
void insert_pos(DQ *dq, int data, int pos);
void delete_begin(DQ *dq);
void delete_end(DQ *dq);
void delete_pos(DQ *dq, int pos);
void display_front(DQ *dq);
void display_rear(DQ *dq);

int main() {
  int choice, data, pos, i;
  DQ *dq = (DQ *)malloc(sizeof(DQ));
  printf("1. Insert at front\n2. Insert at end\n3. Insert at pos\n4. Delete at "
         "front\n5. Delete at end\n6. Delete at pos\n7. Display front\n8. "
         "Display rear\n9. Exit\n");
  while (1) {
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("Enter data: ");
      scanf("%d", &data);
      insert_begin(dq, data);
      break;
    case 2:
      printf("Enter data: ");
      scanf("%d", &data);
      insert_end(dq, data);
      break;
    case 3:
      printf("Enter data: ");
      scanf("%d", &data);
      printf("Enter position: ");
      scanf("%d", &pos);
      insert_pos(dq, data, pos);
      break;
    case 4:
      delete_begin(dq);
      break;
    case 5:
      delete_end(dq);
      break;
    case 6:
      printf("Enter position: ");
      scanf("%d", &pos);
      delete_pos(dq, pos);
      break;
    case 7:
      display_front(dq);
      break;
    case 8:
      display_rear(dq);
      break;
    case 9:
      exit(0);
    default:
      printf("Invalid choice\n");
    }
  }
  return 0;
}

void insert_begin(DQ *dq, int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = dq->front;
  new_node->prev = NULL;

  if (dq->front == NULL) {
    dq->front = new_node;
    dq->rear = new_node;
  } else {
    dq->front->prev = new_node;
    new_node->next = dq->front;
    dq->front = new_node;
  }
}

void insert_end(DQ *dq, int data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = dq->rear;

  if (dq->rear == NULL) {
    dq->front = new_node;
    dq->rear = new_node;
  } else {
    dq->rear->next = new_node;
    new_node->prev = dq->rear;
    dq->rear = new_node;
  }
}

void insert_pos(DQ *dq, int data, int pos) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = NULL;

  if (pos == 1) {
    new_node->next = dq->front;
    dq->front->prev = new_node;
    dq->front = new_node;
  } else {
    Node *temp = dq->front;
    int i;
    for (i = 1; i < pos - 1 && temp != NULL; i++) {
      temp = temp->next;
    }
    if (temp == NULL) {
      printf("Position is greater than size of list\n");
      return;
    }
    new_node->next = temp->next;
    new_node->prev = temp;
    temp->next->prev = new_node;
    temp->next = new_node;
  }
}

void delete_begin(DQ *dq) {
  if (dq->front == NULL) {
    printf("List is empty\n");
    return;
  }
  Node *temp = dq->front;
  dq->front = dq->front->next;
  dq->front->prev = NULL;
  free(temp);
}

void delete_end(DQ *dq) {
  if (dq->rear == NULL) {
    printf("List is empty\n");
  } else {
    Node *temp = dq->rear;
    dq->rear = dq->rear->prev;
    dq->rear->next = NULL;
    free(temp);
  }
}

void delete_pos(DQ *dq, int pos) {
  if (pos == 1) {
    delete_begin(dq);
  } else {
    Node *temp = dq->front;
    int i;
    for (i = 1; i < pos - 1 && temp != NULL; i++) {
      temp = temp->next;
    }
    if (temp == NULL) {
      printf("Position is greater than size of list\n");
      return;
    }
    Node *temp2 = temp->next;
    temp->next = temp->next->next;
    if (temp->next == dq->rear) {
      dq->rear = temp;
    } else {
      temp->next->next->prev = temp;
    }
    free(temp2);
  }
}

void display_front(DQ *dq) {
  if (dq->front == NULL) {
    printf("List is empty\n");
  } else {
    Node *temp = dq->front;
    printf("Front -> ");
    while (temp != dq->rear) {
      printf("%d ", temp->data);
      temp = temp->next;
    }
    printf("%d ", dq->rear->data);
    printf("\n");
  }
}

void display_rear(DQ *dq) {
  if (dq->rear == NULL) {
    printf("List is empty\n");
  } else {
    Node *temp = dq->rear;
    printf("Rear -> ");
    while (temp != dq->front) {
      printf("%d ", temp->data);
      temp = temp->prev;
    }
    printf("%d ", dq->front->data);
    printf("\n");
  }
}
