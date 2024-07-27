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

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, DELETE, EXIT = 9 };

// #define : 매크로 (MACRO)
#define MAKE     1
#define DEPOSIT  2
#define WITHDRAW 3
#define INQUIRE  4
#define DELETE   5
#define EXIT     9

typedef struct t_account {
    int acc_id;      // 계좌번호
    int balance;    // 잔    액
    char cus_name[NAME_LEN];   // 고객이름
    struct t_account* prev;  // 이전 노드 포인터
    struct t_account* next;  // 다음 노드 포인터
} t_account;

void show_menu(void);       // 메뉴출력
void make_account(t_account** head, int* pn);   // 계좌개설
void deposit_money(t_account** head, int* pn);  // 입금
void with_draw_money(t_account** head, int* pn);  // 출금 
void show_all_acc_info(t_account** head, int* pn); // 잔액조회

FILE* filep;   // 이름은 money_file

int main()  // int main(argc, char *argv[])
{
	int choice;
    
	void (*fp[]) (t_account*, int*) =
	{
		NULL, // 0
		make_account,
		deposit_money,
		with_draw_money,
        delete_account,
		show_all_acc_info
	};
	t_account acc_arr[10];   // Account 저장을 위한 배열

    t_account* head = NULL;
    int acc_num = 0;

	if ((filep = fopen("money_file", "rb+")) == NULL) // 파일 주소 반환
	{
		if ((filep = fopen("money_file", "wb+")) == NULL)
		{
			fprintf(stderr, "can't open money_file !!!\n");
			exit(1); // 실행종료 error code 1
		}
	}

    // 파일에서 데이터 읽어오기
    rewind(filep);
    t_account temp;
    while (fread(&temp, sizeof(t_account), 1, filep) == 1) {
        t_account* new_account = (t_account*)malloc(sizeof(t_account));
        *new_account = temp;
        new_account->prev = NULL;
        new_account->next = head;
        if (head != NULL)
            head->prev = new_account;
        head = new_account;
        acc_num++;
    }

	while (1)
    {
        show_menu();
        printf("선택: ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == EXIT)
        {
            // 리스트 메모리 해제
            t_account* current = head;
            while (current != NULL)
            {
                t_account* temp = current;
                current = current->next;
                free(temp);
            }
            fclose(filep);
            break;
        }
        if (choice >= MAKE && choice <= DELETE)
            fp[choice](&head, &acc_num);
    }
	return 0;
}

void show_menu(void)
{
	char* menu[] =
	{
	 "-----Menu------\n",
	 "1. 계좌개설\n",
	 "2. 입    금\n",
	 "3. 출    금\n",
	 "4. 계좌정보 전체 출력\n",
     "5. 계좌삭제\n",
	 "9. 종    료\n"
	};

	int i;

	for (i = 0; i < 7; i++)
		printf("%s", *(menu + i));   // printf("%s", menu[i]);
}

void make_account(t_account** head, int* pn)
{
    t_account* new_account = (t_account*)malloc(sizeof(t_account));
    if (new_account == NULL) {
        printf("메모리 할당 실패\n");
        return;
    }

    printf("[계좌개설]\n");
    printf("계좌ID: ");
    scanf("%d", &new_account->acc_id);
    printf("이  름: ");
    scanf("%s", new_account->cus_name);
    printf("입금액: ");
    scanf("%d", &new_account->balance);
    printf("\n");

    // 파일에 새 계좌 정보 추가
    fseek(filep, 0, SEEK_END);
    fwrite(new_account, sizeof(t_account), 1, filep);

    // 링크드 리스트에 새 노드 추가
    new_account->prev = NULL;
    new_account->next = *head;
    if (*head != NULL)
        (*head)->prev = new_account;
    *head = new_account;

    (*pn)++;
}

void deposit_money(t_account** head, int* pn)
{
    int money, id;
    t_account* current = *head;

    printf("[입    금]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("입금액: ");
    scanf("%d", &money);

    while (current != NULL) {
        if (current->acc_id == id) {
            current->balance += money;
            
            // 파일 업데이트
            long pos = ftell(filep) - sizeof(t_account);
            fseek(filep, pos, SEEK_SET);
            fwrite(current, sizeof(t_account), 1, filep);
            
            printf("입금완료\n\n");
            return;
        }
        current = current->next;
    }
    printf("유효하지 않은 ID 입니다.\n\n");
}

void with_draw_money(t_account** head, int* pn)
{
    int money, id;
    t_account* current = *head;

    printf("[출    금]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("출금액: ");
    scanf("%d", &money);

    while (current != NULL) {
        if (current->acc_id == id) {
            if (current->balance < money) {
                printf("잔액부족\n\n");
                return;
            }
            current->balance -= money;
            
            // 파일 업데이트
            long pos = ftell(filep) - sizeof(t_account);
            fseek(filep, pos, SEEK_SET);
            fwrite(current, sizeof(t_account), 1, filep);
            
            printf("출금완료\n\n");
            return;
        }
        current = current->next;
    }
    printf("유효하지 않은 ID 입니다.\n\n");
}

void delete_account(t_account** head, int* pn)
{
    int id;
    printf("[계좌삭제]\n");
    printf("계좌ID: ");
    scanf("%d", &id);

    t_account* current = *head;
    t_account* prev = NULL;
    long file_pos = 0;

    while (current != NULL) {
        if (current->acc_id == id) {
            if (prev != NULL)
                prev->next = current->next;
            else
                *head = current->next;

            if (current->next != NULL)
                current->next->prev = prev;

            // 파일에서 해당 계좌 정보 삭제 (실제로는 파일 끝의 데이터로 덮어씌움)
            fseek(filep, 0, SEEK_END);
            long last_pos = ftell(filep) - sizeof(t_account);
            t_account last_account;
            fseek(filep, last_pos, SEEK_SET);
            fread(&last_account, sizeof(t_account), 1, filep);

            fseek(filep, file_pos, SEEK_SET);
            fwrite(&last_account, sizeof(t_account), 1, filep);

            // 파일 크기 줄이기
            ftruncate(fileno(filep), last_pos);

            free(current);
            (*pn)--;
            printf("계좌가 삭제되었습니다.\n\n");
            return;
        }
        prev = current;
        current = current->next;
        file_pos += sizeof(t_account);
    }
    printf("유효하지 않은 ID 입니다.\n\n");
}

void show_all_acc_info(t_account** head, int* pn)
{
    t_account* current = *head;

    while (current != NULL) {
        printf("계좌ID: %d\n", current->acc_id);
        printf("이  름: %s\n", current->cus_name);
        printf("잔  액: %d\n\n", current->balance);
        current = current->next;
    }
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

typedef struct t_account
{
	int acc_id;      // 계좌번호
	int balance;    // 잔    액
	char cus_name[NAME_LEN];   // 고객이름
    struct t_account* prev; // 이전 노드
    struct t_account* next; // 다음 노드
} t_account;

t_account* head = NULL;
t_account* tail = NULL;

void show_menu(void);       // 메뉴출력
void make_account(t_account* pt, int* pn);   // 계좌개설
void deposit_money(t_account* pt, int* pn);  // 입금
void with_draw_money(t_account* pt, int* pn);  // 출금 
void show_all_acc_info(t_account* pt, int* pn); // 잔액조회
void free_all_nodes(void); // 노드 동적 할당 해제

FILE* filep;   // 이름은 money_file



int main()  // int main(argc, char *argv[])
{
	int choice;

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

    t_account temp; // 임시
    while (fread(&temp, sizeof(t_account), 1, filep) == 1)
    {
        t_account* new_account = (t_account*)malloc(sizeof(t_account));
        *new_account = temp;
        new_account->prev = tail;
        new_account->next = NULL;
        if (tail) tail->next = new_account;
        else head = new_account;
        tail = new_account;
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

#if 0
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define NAME_LEN 20

typedef struct t_account {
    int acc_id;
    int balance;
    char cus_name[NAME_LEN];
    struct t_account* prev;
    struct t_account* next;
} t_account;

t_account* head = NULL;
t_account* tail = NULL;

void show_menu(void);
void make_account(void);
void deposit_money(void);
void with_draw_money(void);
void show_all_acc_info(void);
void delete_account(void);
void free_all_nodes(void);
void save_to_file(void);

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, DELETE, EXIT = 9 };

FILE* filep;

int main()
{
    int choice;

    if ((filep = fopen("money_file", "rb+")) == NULL)
    {
        if ((filep = fopen("money_file", "wb+")) == NULL)
        {
            fprintf(stderr, "can't open money_file !!!\n");
            exit(1);
        }
    }

    // Load existing accounts from file
    t_account temp;
    while (fread(&temp, sizeof(t_account), 1, filep) == 1)
    {
        t_account* new_account = (t_account*)malloc(sizeof(t_account));
        *new_account = temp;
        new_account->prev = tail;
        new_account->next = NULL;
        if (tail) tail->next = new_account;
        else head = new_account;
        tail = new_account;
    }

    while (1)
    {
        show_menu();
        printf("선택: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case MAKE:
            make_account();
            break;
        case DEPOSIT:
            deposit_money();
            break;
        case WITHDRAW:
            with_draw_money();
            break;
        case INQUIRE:
            show_all_acc_info();
            break;
        case DELETE:
            delete_account();
            break;
        case EXIT:
            save_to_file();
            free_all_nodes();
            fclose(filep);
            return 0;
        default:
            printf("Illegal selection..\n");
        }
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
     "5. 계좌삭제\n",
	 "9. 종    료\n"
	};

	int i;

	for (i = 0; i < 7; i++)
		printf("%s", *(menu + i));   // printf("%s", menu[i]);
}

void make_account(void)
{
    int id;
    char name[NAME_LEN];
    int balance;

    printf("[계좌개설]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("이  름: ");
    scanf("%s", name);
    printf("입금액: ");
    scanf("%d", &balance);
    printf("\n");

    t_account* current = head;
    while (current != NULL)
    {
        if (current->acc_id == id)
        {
            printf("Already exist ID %d\n", id);
            return;
        }
        current = current->next;
    }

    t_account* new_account = (t_account*)malloc(sizeof(t_account));
    new_account->acc_id = id;
    new_account->balance = balance;
    strcpy(new_account->cus_name, name);
    new_account->prev = tail;
    new_account->next = NULL;

    if (tail) tail->next = new_account;
    else head = new_account;
    tail = new_account;

    fseek(filep, 0, SEEK_END);
    fwrite(new_account, sizeof(t_account), 1, filep);
    fflush(filep);
}

void deposit_money(void)
{
    int money;
    int id;

    printf("[입    금]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("입금액: ");
    scanf("%d", &money);

    t_account* current = head;
    while (current != NULL)
    {
        if (current->acc_id == id)
        {
            current->balance += money;
            printf("입금완료\n\n");

            // Update file
            fseek(filep, -(long)sizeof(t_account), SEEK_CUR);
            fwrite(current, sizeof(t_account), 1, filep);
            return;
        }
        current = current->next;
    }

    printf("유효하지 않은 ID 입니다.\n\n");
}

void with_draw_money(void)
{
    int money;
    int id;

    printf("[출    금]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("출금액: ");
    scanf("%d", &money);

    t_account* current = head;
    while (current != NULL)
    {
        if (current->acc_id == id)
        {
            if (current->balance < money)
            {
                printf("잔액부족\n\n");
                return;
            }

            current->balance -= money;
            printf("출금완료\n\n");

            // Update file
            fseek(filep, -(long)sizeof(t_account), SEEK_CUR);
            fwrite(current, sizeof(t_account), 1, filep);
            return;
        }
        current = current->next;
    }

    printf("유효하지 않은 ID 입니다.\n\n");
}

void show_all_acc_info(void)
{
    t_account* current = head;
    while (current != NULL)
    {
        printf("계좌ID: %d\n", current->acc_id);
        printf("이  름: %s\n", current->cus_name);
        printf("잔  액: %d\n\n", current->balance);
        current = current->next;
    }
}

void free_all_nodes(void)
{
    t_account* current = head;
    while (current != NULL)
    {
        t_account* next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
    tail = NULL;
}

void delete_account(void)
{
    int id;
    printf("[계좌 삭제]\n");
    printf("삭제할 계좌ID: ");
    scanf("%d", &id);

    t_account* current = head;
    while (current != NULL)
    {
        if (current->acc_id == id)
        {
            if (current->prev)
                current->prev->next = current->next;
            else
                head = current->next;

            if (current->next)
                current->next->prev = current->prev;
            else
                tail = current->prev;

            free(current);
            printf("계좌가 삭제되었습니다.\n\n");
            return;
        }
        current = current->next;
    }

    printf("유효하지 않은 ID 입니다.\n\n");
}

void save_to_file(void)
{
    fseek(filep, 0, SEEK_SET);
    t_account* current = head;
    while (current != NULL)
    {
        fwrite(current, sizeof(t_account), 1, filep);
        current = current->next;
    }
    ftruncate(fileno(filep), ftell(filep));
}
#endif

#if 0
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAME_LEN   20

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, DELETE, EXIT = 9 };

typedef struct account {
    int acc_id;      // 계좌번호
    int balance;    // 잔    액
    char cus_name[NAME_LEN];   // 고객이름
    struct account* prev;  // 이전 노드
    struct account* next;  // 다음 노드
} t_account;

void show_menu(void);
void make_account(t_account** head, int* pn);
void deposit_money(t_account** head, int* pn);
void with_draw_money(t_account** head, int* pn);
void show_all_acc_info(t_account** head, int* pn);
void delete_account(t_account** head, int* pn);
void load_accounts(t_account** head, int* pn);

FILE* filep;   // 이름은 money_file

int main()
{
    int choice;

    void (*fp[]) (t_account**, int*) =
    {
        NULL, // 0
        make_account,
        deposit_money,
        with_draw_money,
        show_all_acc_info,
        delete_account
    };

    t_account* head = NULL;  // 리스트의 헤드
    int acc_num = 0;        // 저장된 Account 수

    // 파일 열기
    if ((filep = fopen("money_file", "rb+")) == NULL)
    {
        // 파일 없으면 새로 만들기 
        if ((filep = fopen("money_file", "wb+")) == NULL)
        {
            fprintf(stderr, "can't open money_file !!!\n");
            exit(1);
        }
    }
    else // 파일 있으면 정보 로딩
    {
        load_accounts(&head, &acc_num); // 기존 money_file에 있는 데이터들 불러오기
    }

    while (1)
    {
        show_menu();
        printf("선택: ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == EXIT)
        {
            // 리스트 메모리 해제
            t_account* current = head;
            while (current != NULL) {
                t_account* next = current->next;
                free(current);
                current = next;
            }
            fclose(filep);
            break;
        }
        if (choice >= MAKE && choice <= DELETE)
            fp[choice](&head, &acc_num);
    }
    return 0;
}

void show_menu(void)
{
    char* menu[] =
    {
     "-----Menu------\n",
     "1. 계좌개설\n",
     "2. 입    금\n",
     "3. 출    금\n",
     "4. 계좌정보 전체 출력\n",
     "5. 계좌삭제\n",
     "9. 종    료\n"
    };

    for (int i = 0; i < 7; i++)
        printf("%s", menu[i]);
}

void make_account(t_account** head, int* pn)
{
    int id;
    char name[NAME_LEN];
    int balance;

    printf("[계좌개설]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("이  름: ");
    scanf("%s", name);
    printf("입금액: ");
    scanf("%d", &balance);
    printf("\n");

    t_account* current = *head;
    while (current != NULL) {
        if (current->acc_id == id) {
            printf("Already exist ID %d\n", id);
            return;
        }
        current = current->next;
    }

    t_account* new_account = (t_account*)malloc(sizeof(t_account));
    new_account->acc_id = id;
    new_account->balance = balance;
    strcpy(new_account->cus_name, name);
    new_account->prev = NULL;
    new_account->next = *head;

    if (*head != NULL)
        (*head)->prev = new_account;
    *head = new_account;

    (*pn)++;
    printf("계좌가 개설되었습니다.\n\n");

    // 파일에 저장
    fseek(filep, 0, SEEK_END);
    fwrite(new_account, sizeof(t_account), 1, filep);
}

void deposit_money(t_account** head, int* pn)
{
    int money;
    int id;

    printf("[입    금]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("입금액: ");
    scanf("%d", &money);

    t_account* current = *head;
    while (current != NULL) {
        if (current->acc_id == id) {
            current->balance += money;
            printf("입금완료\n\n");
            
            // 파일 업데이트
            long pos = ftell(filep);  // 현재 위치 저장
            fseek(filep, pos - (long)sizeof(t_account), SEEK_SET);
            fwrite(current, sizeof(t_account), 1, filep);
            return;
        }
        current = current->next;
    }
    printf("유효하지 않은 ID 입니다.\n\n");
}

void with_draw_money(t_account** head, int* pn)
{
    int money;
    int id;

    printf("[출    금]\n");
    printf("계좌ID: ");
    scanf("%d", &id);
    printf("출금액: ");
    scanf("%d", &money);

    t_account* current = *head;
    while (current != NULL) {
        if (current->acc_id == id) {
            if (current->balance < money) {
                printf("잔액부족\n\n");
                return;
            }
            current->balance -= money;
            printf("출금완료\n\n");
            
            // 파일 업데이트
            long pos = ftell(filep);  // 현재 위치 저장
            fseek(filep, pos - (long)sizeof(t_account), SEEK_SET);
            fwrite(current, sizeof(t_account), 1, filep);
            return;
        }
        current = current->next;
    }
    printf("유효하지 않은 ID 입니다.\n\n");
}

void show_all_acc_info(t_account** head, int* pn)
{
    t_account* current = *head;
    while (current != NULL)
    {
        printf("계좌ID: %d\n", current->acc_id);
        printf("이  름: %s\n", current->cus_name);
        printf("잔  액: %d\n\n", current->balance);
        current = current->next;
    }
}

void delete_account(t_account** head, int* pn)
{
    int id;
    printf("[계좌삭제]\n");
    printf("계좌ID: ");
    scanf("%d", &id);

    t_account* current = *head;
    while (current != NULL) {
        if (current->acc_id == id) {
            if (current->prev != NULL)
                current->prev->next = current->next;
            else
                *head = current->next;

            if (current->next != NULL)
                current->next->prev = current->prev;

            free(current);
            (*pn)--;
            printf("계좌가 삭제되었습니다.\n\n");
            
            rewind(filep);
            current = *head;
            while (current != NULL) {
                fwrite(current, sizeof(t_account), 1, filep);
                current = current->next;
            }
            return;
        }
        current = current->next;
    }
    printf("유효하지 않은 ID 입니다.\n\n");
}

void load_accounts(t_account** head, int* pn)
{
    t_account* temp = NULL; // 저장할 임시 노드
    while (1) {
        t_account* new_account = (t_account*)malloc(sizeof(t_account)); // 메모리 동적 할당

        if (fread(new_account, sizeof(t_account), 1, filep) != 1) {
            free(new_account);
            break;
        }
        new_account->next = temp;
        if (temp != NULL)
            temp->prev = new_account;
        temp = new_account;
        (*pn)++;
    }
    if (temp != NULL) {
        *head = temp;
        (*head)->prev = NULL;
    }
}
#endif

#if 0 // 원래 코드
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

#if 0 // 원래 코드
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


typedef struct t_account
{
    struct t_account* prev; // 이전 노드
    struct t_account* next; // 다음 노드
    int acc_id;      // 계좌번호
    int balance;    // 잔    액
    char cus_name[NAME_LEN];   // 고객이름
} t_account;

struct t_account* head;
struct t_account* tail;

void show_menu(void);       // 메뉴출력
void make_account(t_account* pt, int* pn);   // 계좌개설
void deposit_money(t_account* pt, int* pn);  // 입금
void with_draw_money(t_account* pt, int* pn);  // 출금 
void show_all_acc_info(t_account* pt, int* pn); // 잔액조회

FILE* filep;   // 이름은 money_file

int main()  // int main(argc, char *argv[])
{
    int choice;

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