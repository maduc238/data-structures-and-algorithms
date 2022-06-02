#include <stdio.h>
#include <stdlib.h>
#define MAX 50


struct stack{
    int data[MAX];
    int top;
};

typedef struct stack st;
void init_st(st *s) {
    s->top = -1;
}

int isFull(st *s) {
    if (s->top == MAX - 1)
        return 1;
    else
        return 0;
}

int isEmp(st *s) {
    if (s->top == -1)
        return 1;
    else
        return 0;
}

void push(st *s, int new_data) {
    if (isFull(s)) {
        printf("\nStack đã đầy\n");
    }     
    else {
        s->top++;
        s->data[s->top] = new_data;
    }
    
}

int pop(st *s) {
    int temp;
    if (isEmp(s)) {
        printf("\nStack rỗng\n");
        temp=-1;
    } 
    else {
        temp = s->data[s->top];
        s->top--;
    }
    return temp;
}

