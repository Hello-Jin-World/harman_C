#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //구조체
#include <string.h>
#define NAME_LEN   20

void show_menu(void);       // 메뉴출력
void make_account(void);       // 계좌개설을 위한 함수
void deposit_money(void);       // 입    금
void with_draw_money(void);      // 출    금
void show_all_acc_info(void);     // 잔액조회

//enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT = 9 };  // 자동으로 DEPOSIT = 2, WITHDRAW = 3 처럼 숫자 할당이 자동으로 된다.

//#define : 매크로 (MACRO)
#define MAKE     1
#define DEPOSIT  2
#define WITHDRAW 3
#define INQUIRE  4
#define EXIT     9


typedef struct // t_account 로 redefine 한다
{
	int acc_id;      // 계좌번호
	int balance;    // 잔    액
	char cus_name[NAME_LEN];   // 고객이름
} t_account;
/*
struct
{
	int acc_id;      // 계좌번호
	int balance;    // 잔    액
	char cus_name[NAME_LEN];   // 고객이름
} account;

struct account acc_arr[100]; // 이렇게 하면 100개를 하나하나 다 입력해야함.

*/

t_account acc_arr[100];   // Account 저장을 위한 배열, 100개가 연속으로 잡힌다.

int acc_num = 0;        // 저장된 Account 수

int main()  // int main(argc, char *argv[])
{
	int choice;

	while (1)
	{
		show_menu();
		printf("선택: ");
		scanf("%d", &choice);  // '1' --> 1 --> choice
		printf("\n");

		switch (choice)
		{
		case MAKE:  // 	case 1:
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
		case EXIT:
			return 0;
		default:
			printf("Illegal selection..\n");
		}
	}
	return 0;
}

void show_menu(void)
{
	char* menu[] =  // 원래는 char menu[6][32] = 이런식으로 메모리를 계속 잡고 있어야했음.
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
		printf("%s", *(menu + i)); // printf("%s", menu[i]);
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

	acc_arr[acc_num].acc_id = id;
	acc_arr[acc_num].balance = balance;
	strcpy(acc_arr[acc_num].cus_name, name);
	acc_num++;
}

void deposit_money(void)
{
	int money;
	int id, i;

	printf("[입    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("입금액: ");
	scanf("%d", &money);

	for (i = 0; i < acc_num; i++)
	{
		if (acc_arr[i].acc_id == id)
		{
			acc_arr[i].balance += money;
			printf("입금완료\n\n");
			return;
		}
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void with_draw_money(void)
{
	int money;
	int id, i;

	printf("[출    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("출금액: ");
	scanf("%d", &money);

	for (i = 0; i < acc_num; i++)
	{
		if (acc_arr[i].acc_id == id)
		{
			if (acc_arr[i].balance < money)
			{
				printf("잔액부족\n\n");
				return;
			}

			acc_arr[i].balance -= money;  // acc_arr[i].balance = acc_arr[i].balance - money;
			printf("출금완료\n\n");
			return;
		}
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void show_all_acc_info(void)
{
	int i;

	for (i = 0; i < acc_num; i++)
	{
		printf("계좌ID: %d\n", acc_arr[i].acc_id);
		printf("이  름: %s\n", acc_arr[i].cus_name);
		printf("잔  액: %d\n\n", acc_arr[i].balance);
	}
}
#endif 