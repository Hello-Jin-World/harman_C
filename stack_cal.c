/*

stack���� �߰��� Push, ���Ŵ� Pop�̶�� �Ѵ�.
 
������ �켱���� 
1�� (, ) ��ȣ
2�� *, / ����, ������
3�� +, - ����, ����

stack�� �̿��Ͽ� infix�� postfix�� ��ȯ
stack�� �̿��Ͽ� postfix�� ��ȯ�� ���� ���

���ڸ� ���� ���� �迭, �����ڸ� ���� ���� �迭 �ʿ�.
ó�� ���� ��ġ (TOP)�� -1���� ����.

�ʿ��� �Լ�
1. �ڷ����� �ʱ�ȭ�ϴ� �Լ�
2. ���� �迭�� ���ڸ� �ִ� PUSH�Լ�
3. ���� �迭�� ���� �����ϴ� POP�Լ� (�̶� ���� return �ϵ��� ����)
4. ���� �迭�� �����ڸ� �ִ� PUSH�Լ�
5. ���� �迭�� ���� �����ϴ� POP�Լ� (�̶� ���� return �ϵ��� ����)
6. �迭 �ʱ�ȭ �Լ�
7. �������� �켱������ �Ǵ��ϴ� �Լ� (�̶� ������ �켱������ ���� ���� return�ϵ��� ����)
8. ����ϴ� �Լ�
9. �����Լ�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int element
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

void init(StackType* s) {
	s->top = -1;
}

void push(StackType* s, element item) {
	if (is_full(s))
	{
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else
		s->stack[++(s->top)] = item;
}

element peek(StackType* s) {
	if (is_full(s))
	{
		fprintf(stderr, "���� ��ȭ ����\n");
		exit(1);
	}
	else
		return s->stack[s->top];
}

element pop(StackType* s) {
	if (is_full(s))
	{
		fprintf(stderr, "���� ��ȭ ����\n");
		exit(1);
	}
	else
		return s->stack[(s->top)--];
}

int prec(char op) {
	switch (op) {
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return -1;
}

is_empty(StackType* s) {
	return (s->top == -1);
}

void in_to_post(char* infix, char* postfix)
{
	StackType s;
	init(&s); // ���� ���� �� �ʱ�ȭ

	while (*infix != "\0") //�Է��� ���ڿ����� NULL�� ���� �� ���� �ݺ�
	{
		if (*infix == ' ')
		{
			push(&s, *infix);
			infix++;	//' ' �����̽��� �����ϴϱ� �����̽� ������ �Է��� ���� push
		}
		else if (*infix == ')')
		{
			while (peek(&s) != '(')
			{
				*postfix++ = pop(&s);
				*postfix++ = ' ';
			}
			pop(&);
			infix++;
		}
		else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/')
		{
			while (!is_empty(&s) && (prec(*infix) <= prec(peek(*s))))
			{
				*postfix = pop(&s);
				*postfix = ' ';
			}
			push(&s, *infix);
			infix++;
		}
		else if (*infix >= '0' && *infix <= '9')
		{
			do {
				*postfix++ = *infix++;
			} while (*infix >= '0' && *infix <= '9');
			*postfix++ = ' ';
		}
		else
			infix++;
	}
	while (!is_empty(&s))
	{
		*postfix++ = pop(&s);
		*postfix++ = ' ';
	}
	postfix--;
	*postfix = '\0';
}

int main(void)
{
	char input[100];
	char postfix[100];

	printf("������ �Է��ϼ���: ");
	fgets(input, sizeof(input), stdin);

	// ���ڿ� ���� ���� ���� ����
	input[strcspn(input, "\n")] = '\0';

	in_to_post(input, postfix);
	printf("���� ǥ���: %s\n", postfix);

	return 0;
}