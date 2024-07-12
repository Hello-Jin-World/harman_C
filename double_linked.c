#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct __node
{
	int value; // 현재 노드의 값
	struct __node* next; // 다음 노드
	struct __node* prev; // 이전 노드
} Node;

Node* getNode(Node* ptr)
{
	if (ptr == NULL) // 포인터가 NULL일 때만 노드 생성
	{
		ptr = malloc(sizeof(Node)); // 노드 사이즈 만큼 생성
		ptr->value = 0; // 4byte
		ptr->next = NULL; // 8byte
		ptr->prev = NULL; // 8byte
		printf("node created..\n");
		return ptr;
	}
	printf("node creation failed..");
}

void appendFirst(Node* head, int data)