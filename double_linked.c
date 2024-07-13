#if 1
#include <stdio.h>
#include <stdlib.h>

struct NODE //구조체 선언
{
    struct NODE* prev; // 이전 노드를 가리킴
    int data;
    struct NODE* next; // 다음 노드를 기리킴
};
struct NODE* head; // 첫 번째 노드를 head라고 함
struct NODE* tail; // 마지막 노드를 tail이라고 함

//노드 생성 함수
struct NODE* makenode(int value){
    struct NODE *node = (struct NODE*)malloc(sizeof(struct NODE)); // 동적 할당
    node->prev = NULL;
    node->data = value;
    node->next = NULL;
    return node;
}

//출력 함수
void print(){
    struct NODE *p;
    p = head;
    while(p->next != tail){
        printf("%d-->",p->data);
        p = p->next;
    }
    printf("%d",p->data);
}

//초기화 함수
void init(){
    head = (struct NODE*)malloc(sizeof(struct NODE));
    tail = (struct NODE*)malloc(sizeof(struct NODE));
    head->data = 0;
    tail->data = 0;

    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
}

//뒤로부터 노드 추가하는 함수
void push_back(int value){ 
    struct NODE* newnode = makenode(value);
    struct NODE* p;
    p = tail;
    p->prev->next = newnode;
    newnode->prev = p->prev;
    p->prev = newnode;
    newnode->next = p;
}

//main함수
int main(){
    init(); //head와 tail 초기화 (data = 0)
    push_back(10); //10 추가
    push_back(30); //30 추가
    push_back(50); //50 추가
    print();  //출력
    return 0;
}
#endif
