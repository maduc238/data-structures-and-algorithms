#include <iostream>
#define MAX 500
struct queue {
    int element[MAX];
    int fron;
    int rear;
};
struct queue* create_queue() {
    struct queue* q = new struct queue[sizeof(struct queue)];
    q->fron = -1;
    q->rear = -1;
    return q;
}
int isEmpty(struct queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

void add_element_into_queue(struct queue* q, int value) {
    if (q->rear == MAX - 1)
        printf("\nQueue is full.");
    else {
        if (q->fron == -1)
            q->fron = 0;
        q->rear++;
        q->element[q->rear] = value;
  }
}

int remove_element_from_queue(struct queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("\nQueue is empty.");
        item = -1;
    }
    else {
        item = q->element[q->fron];
        q->fron++;
        if (q->fron > q->rear) {
            q->fron = q->rear = -1;
        }
    }
    return item;
}

void print_queue(struct queue* q) {
    int i = q->fron;
    if (isEmpty(q)) {
        printf("Hàng đợi rỗng");
  } else {
        printf("\nCác phần tử trong hàng đợi là: ");
        for (i = q->fron; i < q->rear + 1; i++) {
            printf("%d ", q->element[i]);
        }
    }
}
