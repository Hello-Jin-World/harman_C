#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct __node
{
	int value; // ���� ����� ��
	struct __node* next; // ���� ���
	struct __node* prev; // ���� ���
} Node;

Node* getNode(Node* ptr)
{
	if (ptr == NULL) // �����Ͱ� NULL�� ���� ��� ����
	{
		ptr = malloc(sizeof(Node)); // ��� ������ ��ŭ ����
		ptr->value = 0; // 4byte
		ptr->next = NULL; // 8byte
		ptr->prev = NULL; // 8byte
		printf("node created..\n");
		return ptr;
	}
	printf("node creation failed..");
}

void appendFirst(Node* head, int data)
#endif