#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct QueueNode {
  Node *treeNode;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode *front;
  QueueNode *rear;
} Queue;

// Function prototypes
Node *createNode(int data);
void insert(Node **root, int data);
void inorder(Node *root);
void preorder(Node *root);
void postorder(Node *root);
void levelOrder(Node *root);
void enqueue(Queue *q, Node *treeNode);
Node *dequeue(Queue *q);
int isEmpty(Queue *q);
Queue *createQueue();

int main() {
  Node *root = NULL;
  int choice, data;

  do {
    printf("\nBinary Tree Operations:");
    printf("\n1. Insert a node");
    printf("\n2. Inorder traversal");
    printf("\n3. Preorder traversal");
    printf("\n4. Postorder traversal");
    printf("\n5. Level order traversal");
    printf("\n6. Exit");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter data to insert: ");
      scanf("%d", &data);
      insert(&root, data);
      break;
    case 2:
      printf("Inorder traversal: ");
      inorder(root);
      printf("\n");
      break;
    case 3:
      printf("Preorder traversal: ");
      preorder(root);
      printf("\n");
      break;
    case 4:
      printf("Postorder traversal: ");
      postorder(root);
      printf("\n");
      break;
    case 5:
      printf("Level order traversal:\n");
      levelOrder(root);
      break;
    case 6:
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice!\n");
    }
  } while (choice != 6);

  return 0;
}

// Create a new tree node
Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// Insert a node in the complete binary tree
void insert(Node **root, int data) {
  Node *newNode = createNode(data);
  if (*root == NULL) {
    *root = newNode;
    return;
  }

  Queue *q = createQueue();
  enqueue(q, *root);

  while (!isEmpty(q)) {
    Node *current = dequeue(q);

    if (current->left != NULL) {
      enqueue(q, current->left);
    } else {
      current->left = newNode;
      break;
    }

    if (current->right != NULL) {
      enqueue(q, current->right);
    } else {
      current->right = newNode;
      break;
    }
  }

  // Free the queue
  free(q);
}

// Inorder traversal
void inorder(Node *root) {
  if (root != NULL) {
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
  }
}

// Preorder traversal
void preorder(Node *root) {
  if (root != NULL) {
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
  }
}

// Postorder traversal
void postorder(Node *root) {
  if (root != NULL) {
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
  }
}

// Level order traversal
void levelOrder(Node *root) {
  if (root == NULL)
    return;

  Queue *q = createQueue();
  enqueue(q, root);
  int levelCount;

  while (!isEmpty(q)) {
    levelCount = 0; // Count nodes at the current level
    int nodeCount = 0;
    QueueNode *temp = q->front;

    // Count number of nodes in the queue
    while (temp != NULL) {
      nodeCount++;
      temp = temp->next;
    }

    // Print nodes at the current level
    for (int i = 0; i < nodeCount; i++) {
      Node *current = dequeue(q);
      printf("%d ", current->data);

      if (current->left != NULL) {
        enqueue(q, current->left);
        levelCount++;
      }
      if (current->right != NULL) {
        enqueue(q, current->right);
        levelCount++;
      }
    }
    printf("\n"); // New line for the next level
  }

  // Free the queue
  free(q);
}

// Create a new queue
Queue *createQueue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = NULL;
  q->rear = NULL;
  return q;
}

// Enqueue a node in the queue
void enqueue(Queue *q, Node *treeNode) {
  QueueNode *newQueueNode = (QueueNode *)malloc(sizeof(QueueNode));
  newQueueNode->treeNode = treeNode;
  newQueueNode->next = NULL;

  if (isEmpty(q)) {
    q->front = newQueueNode;
    q->rear = newQueueNode;
  } else {
    q->rear->next = newQueueNode;
    q->rear = newQueueNode;
  }
}

// Dequeue a node from the queue
Node *dequeue(Queue *q) {
  if (isEmpty(q))
    return NULL;

  QueueNode *temp = q->front;
  Node *treeNode = temp->treeNode;
  q->front = q->front->next;
  free(temp);
  return treeNode;
}

// Check if the queue is empty
int isEmpty(Queue *q) { return q->front == NULL; }
