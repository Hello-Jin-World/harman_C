#if 0
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


#if 0
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>    // atoi itoa malloc등이 들어 있다. 
#define NAME_LEN   20

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT = 9 };

// #define : 매크로 (MACRO)
#define MAKE     1
#define DEPOSIT  2
#define WITHDRAW 3
#define INQUIRE  4
#define EXIT     9


typedef struct
{
	int acc_id;      // 계좌번호
	int balance;    // 잔    액
	char cus_name[NAME_LEN];   // 고객이름
} t_account;

void show_menu(void);       // 메뉴출력
void make_account(t_account* pt, int* pn);   // 계좌개설
void deposit_money(t_account* pt, int* pn);  // 입금
void with_draw_money(t_account* pt, int* pn);  // 출금 
void show_all_acc_info(t_account* pt, int* pn); // 잔액조회

FILE* filep;   // 이름은 money_file

int main()  // int main(argc, char *argv[])
{
	int choice;
#
	void (*fp[]) (t_account*, int*) =
	{
		NULL, // 0
		make_account,
		deposit_money,
		with_draw_money,
		show_all_acc_info
	};
	t_account acc_arr[10];   // Account 저장을 위한 배열

	int acc_num = 0;        // 저장된 Account 수

	if ((filep = fopen("money_file", "rb+")) == NULL) // 파일 주소 반환
	{
		if ((filep = fopen("money_file", "wb+")) == NULL)
		{
			fprintf(stderr, "can't open money_file !!!\n");
			exit(1); // 실행종료 error code 1
		}
	}
	while (1)
	{
		show_menu();
		printf("선택: ");
		scanf("%d", &choice);  // '1' --> 1 --> choice
		printf("\n");
		if (choice == 9)
		{
			// free(acc_arr);
			fclose(filep);   // 파일의 연결을 끊는다.
			break;
		}
		if (choice >= 1 && choice <= 4)
			fp[choice](acc_arr, &acc_num);

	}
	return 0;
}

void show_menu(void)
{
	char* menu[] =   //  
	{
	 "-----Menu------\n",
	 "1. 계좌개설\n",
	 "2. 입    금\n",
	 "3. 출    금\n",
	 "4. 계좌정보 전체 출력\n",
	 "9. 종    료\n"
	};

	int i;

	for (i = 0; i < 6; i++)
		printf("%s", *(menu + i));   // printf("%s", menu[i]);
}

void make_account(t_account* pt, int* pn)
{
	int id;
	char name[NAME_LEN];
	int balance;
	t_account* p = pt + *pn;

	printf("[계좌개설]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("이  름: ");
	scanf("%s", name);
	printf("입금액: ");
	scanf("%d", &balance);
	printf("\n");

	rewind(filep); // 파일의 헤더를 처음으로 위치시킨다.
	for (int i = 0; ; i++)
	{
		if (fread((char*)&p->acc_id, 1, sizeof(t_account), filep) == NULL)
		{
			break;   // 더이상 읽을 데이터가 없을 때
		}
		//읽는 것을 성공 했을 때
		else if (p->acc_id == id)
		{
			printf("Already exist ID %d\n", id);
			return;
		}
	}

	fseek(filep, 0, SEEK_END); // 헤더를 파일의 맨 끝으로 보냄

	p->acc_id = id;   // (*p).acc_id = id;
	p->balance = balance;
	strcpy(p->cus_name, name);
	fwrite((char*)&p->acc_id, 1, sizeof(t_account), filep);
	*pn += 1;  // pn +=1   주소가 증가 되는것이다. 
}

void deposit_money(t_account* pt, int* pn)
{
	int money;
	int id, i, size;
	t_account* p = pt;

	printf("[입    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("입금액: ");
	scanf("%d", &money);

	rewind(filep);

	//for (i = 0; i < *pn; i++, p++)
	for (i = 0; ; i++, p++)
	{
		if (fread((char*)&p->acc_id, 1, sizeof(t_account), filep) == NULL)
		{
			break;   // 더이상 읽을 데이터가 없을 때
		}
		//읽는 것을 성공 했을 때
		else if (p->acc_id == id)
		{
			p->balance += money;
			size = sizeof(t_account);
			fseek(filep, -size, SEEK_CUR); // 현재 헤더에서 -28byte만큼 옮긴다..
			fwrite((char*)&p->acc_id, 1, sizeof(t_account), filep);
			printf("입금완료\n\n");
			return;
		}
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void with_draw_money(t_account* pt, int* pn)
{
	int money;
	int id, i, size;
	t_account* p = pt;

	printf("[출    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("출금액: ");
	scanf("%d", &money);

	rewind(filep);

	//for (i = 0; i < *pn; i++, p++)
	for (i = 0; ; i++, p++)
	{
		if (fread((char*)&p->acc_id, 1, sizeof(t_account), filep) == NULL)
		{
			break;   // 더이상 읽을 데이터가 없을 때
		}
		else if (p->acc_id == id)
		{

			if (p->balance < money)
			{
				printf("잔액부족\n\n");
				return;
			}

			p->balance -= money;  // acc_arr[i].balance = acc_arr[i].balance - money;
			size = sizeof(t_account);
			fseek(filep, -size, SEEK_CUR); // 현재 헤더에서 -28byte만큼 옮긴다..
			fwrite((char*)&p->acc_id, 1, sizeof(t_account), filep);
			printf("출금완료\n\n");
			return;
		}
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void show_all_acc_info(t_account* pt, int* pn)
{
	int i;
	t_account* p = pt;

	rewind(filep); //헤더를 맨 위로 옮김

	//for (i = 0; i < *pn; i++, p++)
	for (i = 0; ; i++, p++)
	{
		if (fread((char*)&p->acc_id, 1, sizeof(t_account), filep) == NULL)
		{
			break;   // 더이상 읽을 데이터가 없을 때
		}
		printf("계좌ID: %d\n", p->acc_id);
		printf("이  름: %s\n", p->cus_name);
		printf("잔  액: %d\n\n", p->balance);
	}
	printf("\n");
}
#endif

#if 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 20

typedef struct node {
    struct node* prev; 
    int acc_id;      
    int balance;    
    char cus_name[NAME_LEN];  
    struct node* next; 
} acc_node;

acc_node* head; 
acc_node* tail; 

void init() {
    head = (acc_node*)malloc(sizeof(acc_node));
    tail = (acc_node*)malloc(sizeof(acc_node));
    head->next = tail;
    head->prev = NULL;
    tail->next = NULL;
    tail->prev = head;
}

acc_node* makenode(int id, int balance, char* name) {
    acc_node* node = (acc_node*)malloc(sizeof(acc_node));
    node->prev = NULL;
    node->acc_id = id;
    node->balance = balance;
    strcpy(node->cus_name, name);
    node->next = NULL;
    return node;
}

void push_back(int id, int balance, char* name) {
    acc_node* newnode = makenode(id, balance, name);
    acc_node* p = tail->prev;
    p->next = newnode;
    newnode->prev = p;
    newnode->next = tail;
    tail->prev = newnode;
}

void show_menu(void);
void make_account(void);
void deposit_money(void);
void with_draw_money(void);
void show_all_acc_info(void);

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT = 9 };

FILE* filep; 

int main() {
    int choice;

    void (*fp[])(void) = {
        NULL, 
        make_account,
        deposit_money,
        with_draw_money,
        show_all_acc_info
    };

    init();

    if ((filep = fopen("money_file", "rb+")) == NULL) {
        if ((filep = fopen("money_file", "wb+")) == NULL) {
            fprintf(stderr, "can't open money_file !!!\n");
            exit(1); 
        }
    }

    while (1) {
        show_menu();
        printf("선택: ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == 9) {
            fclose(filep); 
            break;
        }
        if (choice >= 1 && choice <= 4)
            fp[choice]();
    }
    return 0;
}

void show_menu(void) {
    char* menu[] = {
        "-----Menu------\n",
        "1. 계좌개설\n",
        "2. 입    금\n",
        "3. 출    금\n",
        "4. 계좌정보 전체 출력\n",
        "9. 종    료\n"
    };

    for (int i = 0; i < 6; i++)
        printf("%s", menu[i]);
}

void make_account() {
    int id;
    char name[NAME_LEN];
    int balance;
    acc_node* p = head->next;

    printf("[계좌개설]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("이  름: ");
    scanf("%s", name);
    printf("입금액: ");
    scanf("%d", &balance);
    printf("\n");

    rewind(filep);

    while (p != tail) {
        if (p->acc_id == id) {
            printf("이미 존재하는 ID입니다.\n");
            return;
        }
        p = p->next;
    }

    fseek(filep, 0, SEEK_END);
    push_back(id, balance, name);
    fwrite(&(makenode(id, balance, name)->acc_id), sizeof(acc_node), 1, filep);
}

void deposit_money() {
    int id, money;
    acc_node* p = head->next;

    printf("[입    금]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("입금액: ");
    scanf("%d", &money);

    rewind(filep);

    while (p != tail) {
        if (fread(p, sizeof(acc_node), 1, filep) == 0) {
            break;
        }
        if (p->acc_id == id) {
            p->balance += money;
            fseek(filep, -sizeof(acc_node), SEEK_CUR);
            fwrite(p, sizeof(acc_node), 1, filep);
            printf("입금완료\n\n");
            return;
        }
        p = p->next;
    }
    printf("유효하지 않은 ID 입니다.\n\n");
}

void with_draw_money() {
    int id, money;
    acc_node* p = head->next;

    printf("[출    금]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("출금액: ");
    scanf("%d", &money);

    rewind(filep);

    while (p != tail) {
        if (fread(p, sizeof(acc_node), 1, filep) == 0) {
            break;
        }
        if (p->acc_id == id) {
            if (p->balance < money) {
                printf("잔액부족\n\n");
                return;
            }
            p->balance -= money;
            fseek(filep, -sizeof(acc_node), SEEK_CUR);
            fwrite(p, sizeof(acc_node), 1, filep);
            printf("출금완료\n\n");
            return;
        }
        p = p->next;
    }
    printf("유효하지 않은 ID 입니다.\n\n");
}

void show_all_acc_info() {
    acc_node* p = head->next;

    rewind(filep);

    while (p != tail) {
        if (fread(p, sizeof(acc_node), 1, filep) == 0) {
            break;
        }
        printf("계좌ID: %d\n", p->acc_id);
        printf("이  름: %s\n", p->cus_name);
        printf("잔  액: %d\n\n", p->balance);
        p = p->next;
    }
}
#endif