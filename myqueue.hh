#ifndef MYQUEUE_H_
#define MYQUEUE_H_

struct node {
    struct node* next;
    int *client_socket;
};

typedef struct node node_t;
void enqueue(int *cluent_socket);
int *dequeue();

#endif