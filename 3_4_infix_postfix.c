#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Node structure for the expression tree
typedef struct Node {
  char data;
  struct Node *left;
  struct Node *right;
} Node;

// Stack structure for operators
typedef struct Stack {
  Node *items[MAX];
  int top;
} Stack;

// Function prototypes
Node *createNode(char data);
void push(Stack *s, Node *node);
Node *pop(Stack *s);
int isEmpty(Stack *s);
int precedence(char op);
void infixToPostfix(const char *infix, char *postfix);
Node *buildExpressionTree(const char *postfix);
void displayPrefix(Node *root);
void displayInfix(Node *root);
void displayPostfix(Node *root);
int evaluate(Node *root);
void freeTree(Node *root);
int isDigit(char ch);

int main() {
  char infix[MAX], postfix[MAX];
  Node *root;

  printf("Enter an infix expression: ");
  fgets(infix, MAX, stdin);
  infix[strcspn(infix, "\n")] = 0; // Remove newline character

  infixToPostfix(infix, postfix);
  printf("Postfix expression: %s\n", postfix);

  root = buildExpressionTree(postfix);

  printf("Infix expression: ");
  displayInfix(root);
  printf("\n");

  printf("Prefix expression: ");
  displayPrefix(root);
  printf("\n");

  printf("Postfix expression: ");
  displayPostfix(root);
  printf("\n");

  int result = evaluate(root);
  printf("Evaluation result: %d\n", result);

  freeTree(root);
  return 0;
}

// Create a new tree node
Node *createNode(char data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

// Stack operations
void push(Stack *s, Node *node) { s->items[++s->top] = node; }

Node *pop(Stack *s) { return s->items[s->top--]; }

int isEmpty(Stack *s) { return s->top == -1; }

// Check if a character is a digit
int isDigit(char ch) { return ch >= '0' && ch <= '9'; }

// Operator precedence
int precedence(char op) {
  switch (op) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  }
  return 0;
}

// Convert infix expression to postfix
void infixToPostfix(const char *infix, char *postfix) {
  Stack s;
  s.top = -1;
  int j = 0;

  for (int i = 0; infix[i]; i++) {
    if (isDigit(infix[i])) {
      postfix[j++] = infix[i]; // Append operand
    } else if (infix[i] == '(') {
      push(&s, createNode('('));
    } else if (infix[i] == ')') {
      while (!isEmpty(&s) && s.items[s.top]->data != '(') {
        postfix[j++] = pop(&s)->data;
      }
      pop(&s); // Remove '('
    } else {
      while (!isEmpty(&s) &&
             precedence(s.items[s.top]->data) >= precedence(infix[i])) {
        postfix[j++] = pop(&s)->data;
      }
      push(&s, createNode(infix[i])); // Push operator
    }
  }

  while (!isEmpty(&s)) {
    postfix[j++] = pop(&s)->data;
  }

  postfix[j] = '\0'; // Null terminate postfix expression
}

// Build expression tree from postfix expression
Node *buildExpressionTree(const char *postfix) {
  Stack s;
  s.top = -1;

  for (int i = 0; postfix[i]; i++) {
    if (isDigit(postfix[i])) {
      push(&s, createNode(postfix[i]));
    } else {
      Node *node = createNode(postfix[i]);
      node->right = pop(&s); // Right child
      node->left = pop(&s);  // Left child
      push(&s, node);
    }
  }

  return pop(&s); // The root of the expression tree
}

// Display the expression tree in prefix order
void displayPrefix(Node *root) {
  if (root) {
    printf("%c ", root->data);
    displayPrefix(root->left);
    displayPrefix(root->right);
  }
}

// Display the expression tree in infix order
void displayInfix(Node *root) {
  if (root) {
    if (root->left) {
      printf("(");
      displayInfix(root->left);
    }
    printf("%c ", root->data);
    if (root->right) {
      displayInfix(root->right);
      printf(")");
    }
  }
}

// Display the expression tree in postfix order
void displayPostfix(Node *root) {
  if (root) {
    displayPostfix(root->left);
    displayPostfix(root->right);
    printf("%c ", root->data);
  }
}

// Evaluate the expression tree
int evaluate(Node *root) {
  if (root == NULL) {
    return 0;
  }
  if (isDigit(root->data)) {
    return root->data - '0'; // Convert char to int
  }

  int leftEval = evaluate(root->left);
  int rightEval = evaluate(root->right);

  switch (root->data) {
  case '+':
    return leftEval + rightEval;
  case '-':
    return leftEval - rightEval;
  case '*':
    return leftEval * rightEval;
  case '/':
    return leftEval / rightEval;
  }
  return 0;
}

// Free the expression tree
void freeTree(Node *root) {
  if (root) {
    freeTree(root->left);
    freeTree(root->right);
    free(root);
  }
}
