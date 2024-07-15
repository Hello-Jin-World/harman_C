#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef int element;

typedef struct {
    element stack[STACK_SIZE];
    int top; // top�� ���ÿ��� ��ġ�� ����Ŵ
} StackType;

void init(StackType* s) {
    s->top = -1; // �ʱ�ȭ. -1 ��ġ�� ����Ŵ
}

int is_empty(StackType* s) {
    return (s->top == -1); // ������ �� top�� -1�̸� 1�� return
}

int is_full(StackType* s) {
    return (s->top == (STACK_SIZE - 1)); // �� ���� 1�� return
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else {
        s->stack[++(s->top)] = item; // ������ top�� �ϳ� ������Ű�� �� ��ġ�� �� ����
    }
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else {
        return s->stack[s->top]; // ������ �ֻ�ܿ� �ִ� �� ��ȯ
    }
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else {
        return s->stack[(s->top)--]; // ���� ���� ��ġ�� �ִ� ���� return�ϰ� ��ġ�� ��ĭ �Ʒ��� ����
    }
}

int prec(char op) {
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1; 
    case '*': case '/': return 2;
    }
    return -1;
} // �켱���� ����

void in_to_post(char* infix, char* postfix) {
    StackType s;
    init(&s); // ���� ���� �� �ʱ�ȭ

    while (*infix != '\0')
    { // �Է��� ���ڿ����� (���ڿ� ����)NULL�� ���� ������ �ݺ�
        if (*infix == ' ')
        {
            infix++; // ' ' �����̽��� ����
        }
        else if (*infix == '(')
        {
            push(&s, *infix); // '(' �� ���ÿ� ����
            infix++;
        }
        else if (*infix == ')')
        {
            while (peek(&s) != '(')
            {
                *postfix++ = pop(&s); // ')'�� �ԷµǷ��� �ϸ� '('�� ���ö� ���� �����ڸ� pop�ϰ� �迭�� ����
                *postfix++ = ' ';
            }
            pop(&s); // '(' ����
            infix++;
        }
        else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/')
        {
            while (!is_empty(&s) && (prec(*infix) <= prec(peek(&s)))) // �����ڰ� ������ �켱������ ���Ѵ�.
                                                                      // (, ) �� 0     +, - �� 1     *, / �� 2 ��ȯ
            {
                *postfix++ = pop(&s); // ���ÿ��� �ֻ�� �����ڸ� ������ postfix�� �߰�
                *postfix++ = ' '; // postfix�� space �߰�
            }
            push(&s, *infix); // �켱������ ���粨�� �� ������ �׳� �ٷ� �ִ´�.
            infix++;
        }
        else if (*infix >= '0' && *infix <= '9')
        {
            do {
                *postfix++ = *infix++;
            } while (*infix >= '0' && *infix <= '9');  // ���ڸ� �� �̻��� �Է��ϱ� ����
                                                       // ���� �ڿ� �ٷ� ���ڳ����� �״��
                                                       // ��� ����
            *postfix++ = ' '; // ���ڸ� �� ������ space �Է��ؼ� ���� ����
        }
        else {
            infix++;
        }
    }
    while (!is_empty(&s))
    {
        *postfix++ = pop(&s); // �迭�� ��� ������ ���ÿ� �����ִ� ������ pop�ؼ� �迭�� ����
        *postfix++ = ' ';
    }
    postfix--;
    *postfix = '\0'; // �� ���� '\0' ����
}

void rm_space(char *infix, char* postfix)
{
    StackType s;
    init(&s); // ���� ���� �� �ʱ�ȭ
    int i;

    while(*infix != '\0')
    {
        if (*infix != ' ')
        {
            push(&s, *infix); // ' ' space���� ��� ���� ����
        }
        infix++;
    }

    int idx = 0;
    while (!is_empty(&s))
    {
        postfix[idx++] = pop(&s); // ��繮�� pop�ؼ� �迭�� ����
    }
    postfix[idx] = '\0';

    for (i = 0; i < idx / 2; i++) // ���������� �� ���ڰ� ó������ �����ϱ� �迭 ������
    {
        char temp = postfix[i];
        postfix[i] = postfix[idx - 1 - i];
        postfix[idx - 1 - i] = temp;
    }
}

int main(void)
{
    char input[100]; // ����� �Է��� ���ڿ� �迭
    char postfix[100]; // �������� ���ڿ��� �������� �迭
    double d_post[100];

    printf("���� �Է��Ͻÿ� : ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    rm_space(input, postfix);
    printf("���������� ���ڿ� ��� : %s\n", postfix); 

    in_to_post(input, postfix);
    printf("����ǥ��� �迭 : %.0f\n", postfix);

    return 0;
}
#endif