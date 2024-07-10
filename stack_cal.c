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
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else {
        s->stack[++(s->top)] = item;
    }
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else {
        return s->stack[s->top];
    }
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
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
    init(&s); // 스택 선언 및 초기화

    while (*infix != '\0') { // 입력한 문자열에서 NULL값 만날 때까지 반복
        if (*infix == ' ') {
            infix++; // ' ' 스페이스는 무시
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
            pop(&s); // '(' 제거
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

    printf("식을 입력하시오 : ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    in_to_post(input, postfix);
    printf("후위표기법 배열 : %s\n", postfix);

    return 0;
}