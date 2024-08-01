#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef int element;

typedef struct {
    element stack[STACK_SIZE];
    int top; // top는 스택에서 위치를 가르킴
} StackType;

void init(StackType* s) {
    s->top = -1; // 초기화. -1 위치를 가르킴
}

int is_empty(StackType* s) {
    return (s->top == -1); // 스택이 비어서 top이 -1이면 1을 return
}

int is_full(StackType* s) {
    return (s->top == (STACK_SIZE - 1)); // 다 차면 1을 return
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else {
        s->stack[++(s->top)] = item; // 스택의 top을 하나 증가시키고 그 위치에 값 저장
    }
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else {
        return s->stack[s->top]; // 스택의 최상단에 있는 값 반환
    }
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else {
        return s->stack[(s->top)--]; // 현재 스택 위치에 있는 값을 return하고 위치를 한칸 아래로 내림
    }
}

int prec(char op) {
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1; 
    case '*': case '/': return 2;
    }
    return -1;
} // 우선순위 정의

void in_to_post(char* infix, char* postfix) {
    StackType s;
    init(&s); // 스택 선언 및 초기화

    while (*infix != '\0')
    { // 입력한 문자열에서 (문자열 끝인)NULL값 만날 때까지 반복
        if (*infix == ' ')
        {
            infix++; // ' ' 스페이스는 무시
        }
        else if (*infix == '(')
        {
            push(&s, *infix); // '(' 는 스택에 저장
            infix++;
        }
        else if (*infix == ')')
        {
            while (peek(&s) != '(')
            {
                *postfix++ = pop(&s); // ')'가 입력되려고 하면 '('이 나올때 까지 연산자를 pop하고 배열에 저장
                *postfix++ = ' ';
            }
            pop(&s); // '(' 제거
            infix++;
        }
        else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/')
        {
            while (!is_empty(&s) && (prec(*infix) <= prec(peek(&s)))) // 연산자가 나오면 우선순위를 비교한다.
                                                                      // (, ) 은 0     +, - 는 1     *, / 는 2 반환
            {
                *postfix++ = pop(&s); // 스택에서 최상단 연산자를 꺼내서 postfix에 추가
                *postfix++ = ' '; // postfix에 space 추가
            }
            push(&s, *infix); // 우선순위가 현재꺼가 더 높으면 그냥 바로 넣는다.
            infix++;
        }
        else if (*infix >= '0' && *infix <= '9')
        {
            do {
                *postfix++ = *infix++;
            } while (*infix >= '0' && *infix <= '9');  // 두자리 수 이상을 입력하기 위해
                                                       // 숫자 뒤에 바로 숫자나오면 그대로
                                                       // 계속 쌓음
            *postfix++ = ' '; // 숫자만 다 쌓으면 space 입력해서 숫자 구분
        }
        else {
            infix++;
        }
    }
    while (!is_empty(&s))
    {
        *postfix++ = pop(&s); // 배열이 모두 끝나면 스택에 남아있는 연산자 pop해서 배열에 저장
        *postfix++ = ' ';
    }
    postfix--;
    *postfix = '\0'; // 맨 끝에 '\0' 저장
}

void rm_space(char *infix, char* postfix)
{
    StackType s;
    init(&s); // 스택 선언 및 초기화
    int i;

    while(*infix != '\0')
    {
        if (*infix != ' ')
        {
            push(&s, *infix); // ' ' space빼고 모든 문자 저장
        }
        infix++;
    }

    int idx = 0;
    while (!is_empty(&s))
    {
        postfix[idx++] = pop(&s); // 모든문자 pop해서 배열에 저장
    }
    postfix[idx] = '\0';

    for (i = 0; i < idx / 2; i++) // 마지막으로 들어간 문자가 처음으로 나오니까 배열 뒤집기
    {
        char temp = postfix[i];
        postfix[i] = postfix[idx - 1 - i];
        postfix[idx - 1 - i] = temp;
    }
}

int main(void)
{
    char input[100]; // 사용자 입력할 문자열 배열
    char postfix[100]; // 공백제거 문자열과 후위계산법 배열
    double d_post[100];

    printf("식을 입력하시오 : ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    rm_space(input, postfix);
    printf("공백제거한 문자열 출력 : %s\n", postfix); 

    in_to_post(input, postfix);
    printf("후위표기법 배열 : %.0f\n", postfix);

    return 0;
}
#endif