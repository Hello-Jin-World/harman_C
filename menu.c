#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //����ü
#include <string.h>
#define NAME_LEN   20

void show_menu(void);       // �޴����
void make_account(void);       // ���°����� ���� �Լ�
void deposit_money(void);       // ��    ��
void with_draw_money(void);      // ��    ��
void show_all_acc_info(void);     // �ܾ���ȸ

//enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT = 9 };  // �ڵ����� DEPOSIT = 2, WITHDRAW = 3 ó�� ���� �Ҵ��� �ڵ����� �ȴ�.

//#define : ��ũ�� (MACRO)
#define MAKE     1
#define DEPOSIT  2
#define WITHDRAW 3
#define INQUIRE  4
#define EXIT     9


typedef struct //account_node �� redefine �Ѵ�
{
	int acc_id;      // ���¹�ȣ
	int balance;    // ��    ��
	char cus_name[NAME_LEN];   // �����̸�
}account_node;
/*
struct
{
	int acc_id;      // ���¹�ȣ
	int balance;    // ��    ��
	char cus_name[NAME_LEN];   // �����̸�
} account;

struct account acc_arr[100]; // �̷��� �ϸ� 100���� �ϳ��ϳ� �� �Է��ؾ���.

*/

t_account acc_arr[100];   // Account ������ ���� �迭, 100���� �������� ������.

int acc_num = 0;        // ����� Account ��

int main()  // int main(argc, char *argv[])
{
	int choice;

	while (1)
	{
		show_menu();
		printf("����: ");
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
	char* menu[] =  // ������ char menu[6][32] = �̷������� �޸𸮸� ��� ��� �־������.
	{
	 "-----Menu------\n",
	 "1. ���°���\n",
	 "2. ��    ��\n",
	 "3. ��    ��\n",
	 "4. �������� ��ü ���\n",
	 "9. ��    ��\n"
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

	printf("[���°���]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("��  ��: ");
	scanf("%s", name);
	printf("�Աݾ�: ");
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

	printf("[��    ��]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("�Աݾ�: ");
	scanf("%d", &money);

	for (i = 0; i < acc_num; i++)
	{
		if (acc_arr[i].acc_id == id)
		{
			acc_arr[i].balance += money;
			printf("�ԱݿϷ�\n\n");
			return;
		}
	}
	printf("��ȿ���� ���� ID �Դϴ�.\n\n");
}

void with_draw_money(void)
{
	int money;
	int id, i;

	printf("[��    ��]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("��ݾ�: ");
	scanf("%d", &money);

	for (i = 0; i < acc_num; i++)
	{
		if (acc_arr[i].acc_id == id)
		{
			if (acc_arr[i].balance < money)
			{
				printf("�ܾ׺���\n\n");
				return;
			}

			acc_arr[i].balance -= money;  // acc_arr[i].balance = acc_arr[i].balance - money;
			printf("��ݿϷ�\n\n");
			return;
		}
	}
	printf("��ȿ���� ���� ID �Դϴ�.\n\n");
}

void show_all_acc_info(void)
{
	int i;

	for (i = 0; i < acc_num; i++)
	{
		printf("����ID: %d\n", acc_arr[i].acc_id);
		printf("��  ��: %s\n", acc_arr[i].cus_name);
		printf("��  ��: %d\n\n", acc_arr[i].balance);
	}
}
#endif 