#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

typedef struct Queue {
  struct Node *top;
  int size;
} Queue;

Queue *createQueue();
void printQueue(Queue *queue);
int pop(Queue *queue);
void push(Queue *queue, int data);
Queue *add(int a, int b);

int main() {
  int a, b;
  printf("Enter two numbers: ");
  scanf("%d %d", &a, &b);
  Queue *queue = add(a, b);
  printQueue(queue);
  return 0;
}

void push(Queue *queue, int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = queue->top;
  queue->top = newNode;
  queue->size++;
}
int pop(Queue *queue) {
  if (queue->top == NULL) {
    return -1; // Queue is empty
  }

  // If there is only one element in the queue
  if (queue->top->next == NULL) {
    int data = queue->top->data;
    free(queue->top);
    queue->top = NULL;
    queue->size--;
    return data;
  }

  // If there are more than one elements in the queue
  struct Node *p = queue->top;
  while (p->next->next != NULL) {
    p = p->next;
  }

  int data = p->next->data;
  free(p->next);
  p->next = NULL;
  queue->size--;
  return data;
}

Queue *add(int a, int b) {
  Queue *queueA = createQueue();
  while (a != 0) {
    push(queueA, a % 10);
    a = a / 10;
  }
  Queue *queueB = createQueue();
  while (b != 0) {
    push(queueB, b % 10);
    b = b / 10;
  }
  Queue *queue = createQueue();
  int carry = 0;
  while (queueA->top != NULL && queueB->top != NULL) {
    int sum = pop(queueA) + pop(queueB) + carry;
    carry = sum / 10;
    push(queue, sum % 10);
  }
  while (queueA->top != NULL) {
    int sum = pop(queueA) + carry;
    carry = sum / 10;
    push(queue, sum % 10);
  }
  while (queueB->top != NULL) {
    int sum = pop(queueB) + carry;
    carry = sum / 10;
    push(queue, sum % 10);
  }
  if (carry > 0) {
    push(queue, carry);
  }
  return queue;
}

void printQueue(Queue *queue) {
  if (queue->top == NULL) {
    printf("Queue is empty\n");
    return;
  }
  struct Node *p = queue->top;
  while (p != NULL) {
    printf("%d", p->data);
    p = p->next;
  }
  printf("\n");
}
Queue *createQueue() {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->top = NULL;
  queue->size = 0;
  return queue;
}
