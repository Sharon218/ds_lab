#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

typedef struct {
  struct Node *top;
  int size;
} Queue;

Queue *createQueue();
int deleteElement(Queue *q, int data);
void display(Queue *q);
void enqueue(Queue *q, int data);
int dequeue(Queue *q);

int main() {
  Queue *q = createQueue();

  int choice;
  printf(
      "1. Enqueue\n2. Dequeue\n3. Delete an elemeent\n4. Display\n5. Exit\n");
  while (1) {
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("Enter the element to be enqueued: ");
      int data;
      scanf("%d", &data);
      enqueue(q, data);
      break;
    case 2:
      int data1 = dequeue(q);
      if (data1 == -1) {
        break;
      }
      printf("The element dequeued is: %d\n", data1);
      break;
    case 3:
      printf("Enter the element to be deleted: ");
      int data2;
      scanf("%d", &data2);
      deleteElement(q, data2);
      break;
    case 4:
      display(q);
      break;
    case 5:
      printf("Exiting...\n");
      exit(0);
    default:
      printf("Invalid choice\n");
    }
  }
}

void enqueue(Queue *q, int data) {
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
  temp->data = data;
  temp->next = NULL;

  if (q->top == NULL) {
    q->top = temp;
    return;
  }

  struct Node *p = q->top;
  while (p->next != NULL) {
    p = p->next;
  }
  p->next = temp;
  q->size++;
}

int dequeue(Queue *q) {
  if (q->top == NULL) {
    printf("Queue is empty\n");
    return -1;
  }

  struct Node *temp = q->top;
  q->top = q->top->next;
  int data = temp->data;
  free(temp);
  q->size--;
  return data;
}

int deleteElement(Queue *q, int data) {
  if (q->top == NULL) {
    printf("Queue is empty\n");
    return -1;
  }

  struct Node *p = q->top;
  if ((q->top)->data != data) {
    while (p->next != NULL) {
      if ((p->next)->data == data) {
        struct Node *temp = p->next;
        p->next = temp->next;
        free(temp);
        return 1;
      }
      p = p->next;
    }
  } else {
    struct Node *temp = q->top;
    q->top = q->top->next;
    free(temp);
  }
  q->size--;
  return 0;
}

void display(Queue *q) {
  if (q->top == NULL) {
    printf("Queue is empty\n");
    return;
  }

  struct Node *p = q->top;
  while (p != NULL) {
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}

Queue *createQueue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->top = NULL;
  q->size = 0;
  return q;
}
