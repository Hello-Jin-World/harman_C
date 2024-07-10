/*

stack에서 추가는 Push, 제거는 Pop이라고 한다.
 
연산자 우선순위 
1등 (, ) 괄호
2등 *, / 곱셈, 나눗셈
3등 +, - 덧셈, 뺄셈

stack을 이용하여 infix를 postfix로 변환
stack을 이용하여 postfix로 변환된 수식 계산

숫자를 쌓을 스택 배열, 연산자를 쌓을 스택 배열 필요.
처음 스택 위치 (TOP)는 -1에서 시작.

필요한 함수
1. 자료형을 초기화하는 함수
2. 숫자 배열에 숫자를 넣는 PUSH함수
3. 숫자 배열에 값을 제거하는 POP함수 (이때 값을 return 하도록 선언)
4. 문자 배열에 연산자를 넣는 PUSH함수
5. 문자 배열에 값을 제거하는 POP함수 (이때 값을 return 하도록 선언)
6. 배열 초기화 함수
7. 연산자의 우선순위를 판단하는 함수 (이때 연산의 우선순위에 따라 값을 return하도록 선언)
8. 계산하는 함수
9. 메인함수
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
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->stack[++(s->top)] = item;
}

element peek(StackType* s) {
	if (is_full(s))
	{
		fprintf(stderr, "스택 포화 에러\n");
		exit(1);
	}
	else
		return s->stack[s->top];
}

element pop(StackType* s) {
	if (is_full(s))
	{
		fprintf(stderr, "스택 포화 에러\n");
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
	init(&s); // 스택 선언 및 초기화

	while (*infix != "\0") //입력한 문자열에서 NULL값 만날 때 까지 반복
	{
		if (*infix == ' ')
		{
			push(&s, *infix);
			infix++;	//' ' 스페이스로 구분하니까 스페이스 만나면 입력한 값을 push
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

	printf("연산을 입력하세요: ");
	fgets(input, sizeof(input), stdin);

	// 문자열 끝의 개행 문자 제거
	input[strcspn(input, "\n")] = '\0';

	in_to_post(input, postfix);
	printf("후위 표기법: %s\n", postfix);

	return 0;
}