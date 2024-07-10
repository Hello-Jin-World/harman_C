#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef double element;

typedef struct {
    element stack[STACK_SIZE];
    int top;
} StackType;

void init(StackType* s) {
    s->top = -1;
}

int is_empty(StackType* s) {
    return (s->top == -1);
}

int is_full(StackType* s) {
    return (s->top == (STACK_SIZE - 1));
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else {
        s->stack[++(s->top)] = item;
    }
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else {
        return s->stack[s->top];
    }
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else {
        return s->stack[(s->top)--];
    }
}

int prec(char op) {
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

void in_to_post(char* infix, char* postfix) {
    StackType s;
    init(&s); // ���� ���� �� �ʱ�ȭ

    while (*infix != '\0') { // �Է��� ���ڿ����� NULL�� ���� ������ �ݺ�
        if (*infix == ' ') {
            infix++; // ' ' �����̽��� ����
        }
        else if (*infix == '(') {
            push(&s, *infix);
            infix++;
        }
        else if (*infix == ')') {
            while (peek(&s) != '(') {
                *postfix++ = pop(&s);
                *postfix++ = ' ';
            }
            pop(&s); // '(' ����
            infix++;
        }
        else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/') {
            while (!is_empty(&s) && (prec(*infix) <= prec(peek(&s)))) {
                *postfix++ = pop(&s);
                *postfix++ = ' ';
            }
            push(&s, *infix);
            infix++;
        }
        else if (*infix >= '0' && *infix <= '9') {
            do {
                *postfix++ = *infix++;
            } while (*infix >= '0' && *infix <= '9');
            *postfix++ = ' ';
        }
        else {
            infix++;
        }
    }
    while (!is_empty(&s)) {
        *postfix++ = pop(&s);
        *postfix++ = ' ';
    }
    postfix--;
    *postfix = '\0';
}

int main(void) {
    char input[100];
    char postfix[100];

    printf("���� �Է��Ͻÿ� : ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    in_to_post(input, postfix);
    printf("����ǥ��� �迭 : %s\n", postfix);

    return 0;
}