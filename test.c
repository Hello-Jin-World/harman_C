#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc �Լ� ��������.
#endif

/*
1. ����ü �迭
2. ����ü ������ (���� -> ����)
3. ���� �޸� -> ���� �޸� (switch~case -> �Լ� ������ �迭)
4. reset -> ���� ó��
5. union
*/

// union (����ü) �н�
// union�� �����ϰ� union�� ���� ���� �� �뵵�� �����Ѵ�.
//--- Big Endian(����Ѷ�迭)�� Little Endion(����)�� ������
// - �����͸� ó���ϴ� ��巹���� �ּ� ���� : byte
//   �����͸� ó���ϴµ� ū���� ���� ó���� ���ΰ� ���� �������� ó���� ���ΰ�
//	 ū���� ó��:Big Endian, �������� ó��:Little Endion
// - 0x12345678�� byte data�� �ִٰ� ��������
//   3130................0
// 
//   MSB(Most Significant Byte) : 0x12
//   LSB(Least Significant Byte) : 0x78
// - Big Endian(����Ѷ�迭) type���� �����͸� ����(����)
//   0x12 0x34 0x56 0x78
// - Little Endion(���ڰ迭) type���� �����͸� ����(����)
//   0x78 0x56 0x23 0x12
#if 0
int main(void)
{
	union
	{
		// BYTE ������ ������ ����Ǹ� struct { } s;���� ���� ���� �ٲ��. (����ü)
		unsigned char BYTE;		// 0x1000������ �޸𸮰� 1byte�� �Ҵ� �Ǿ��ٰ� ��������.
		struct   // little endian 0x1000���� ���� ����
		{
			unsigned b0 : 1;  // 1bit �Ҵ�
			unsigned b1 : 1;
			unsigned b2 : 1;
			unsigned b3 : 1;	// ���� b0~b3�� ������.
			unsigned dummy : 4;
		} s;
	} u;

	u.BYTE = 0xff;
	printf("u.BYTE : %0x\n", u.BYTE);
	u.s.b3 = 0;
	printf("u.BYTE : %0x\n", u.BYTE);
	u.s.dummy = 0;
	printf("u.BYTE : %0x\n", u.BYTE);

	return 0;
}
#endif

//����ü�� ���� ó��(���� ������. fseek, rewind)�� ���� ����
// --> ���α׷��� ���� �ϴ��� ���� ������ �״�� ���� �ֵ��� �ϱ� ����
// --> ��ġ DB�� �����.
#if 0
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>    // atoi itoa malloc���� ��� �ִ�. 
#define NAME_LEN   20

void show_menu(void);       // �޴����
void make_account(void);       // ���°����� ���� �Լ�
void deposit_money(void);       // ��    ��
void with_draw_money(void);      // ��    ��
void show_all_acc_info(void);     // �ܾ���ȸ

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT = 9 };

// #define : ��ũ�� (MACRO)
#define MAKE     1
#define DEPOSIT  2
#define WITHDRAW 3
#define INQUIRE  4
#define EXIT     9


typedef struct
{
	int acc_id;      // ���¹�ȣ
	int balance;    // ��    ��
	char cus_name[NAME_LEN];   // �����̸�
} t_account;
/*
struct
{
	int acc_id;     // ���¹�ȣ
	int balance;    // ��    ��
	char cus_name[NAME_LEN];   // �����̸�
} account;

struct account acc_arr[100];
*/
void make_account(t_account* pt, int* pn);   // ���°���
void deposit_money(t_account* pt, int* pn);  // �Ա�
void with_draw_money(t_account* pt, int* pn);  // ��� 
void show_all_acc_info(t_account* pt, int* pn); // �ܾ���ȸ

FILE* filep;   // �̸��� money_file



int main()  // int main(argc, char *argv[])
{
	int choice;
#if 0
	t_account* acc_arr;   // acc_arr��� ������ t_account Ÿ���� ����ü Ÿ���� 
	// ������(�ּҸ� �����ϴ� ����(����) �̴�. 
	void (*fp[]) (t_account*, int*) =
	{
		NULL, // 0
		make_account,
		deposit_money,
		with_draw_money,
		show_all_acc_info
	};


	acc_arr = (t_account*)malloc(sizeof(t_account) * 10);   // acc_arr[10];
	// malloc�� ���� �Ǵ� default�� char *�̳� �̸� ����ü �����ͷ� ��ȯ
	// acc_arr���� ���� ������ ���� �ȴ�. 
	if (acc_arr == NULL)
	{
		printf("�޸� �Ҵ� ���� @!!!!!\n");
		return -1;   // 0: ������, -1: �ɰ��� error
	}

#else  // orginal 
	void (*fp[]) (t_account*, int*) =
	{
		NULL, // 0
		make_account,
		deposit_money,
		with_draw_money,
		show_all_acc_info
	};
	t_account acc_arr[10];   // Account ������ ���� �迭
#endif 

	int acc_num = 0;        // ����� Account ��

	if ((filep = fopen("money_file", "rb+")) == NULL) // ���� �ּ� ��ȯ
	{
		if ((filep = fopen("money_file", "wb+")) == NULL)
		{
			fprintf(stderr, "can't open money_file !!!\n");
			exit(1); // �������� error code 1
		}
	}
	while (1)
	{
		show_menu();
		printf("����: ");
		scanf("%d", &choice);  // '1' --> 1 --> choice
		printf("\n");
		if (choice == 9)
		{
			// free(acc_arr);
			fclose(filep);   // ������ ������ ���´�.
			break;
		}
		if (choice >= 1 && choice <= 4)
			fp[choice](acc_arr, &acc_num);

#if 0  // �Լ� ������ �迭�� ���� �ǵ��� �ϼ� �Ͻÿ� 
		switch (choice)
		{
		case MAKE:  // 	case 1:
			make_account(acc_arr, &acc_num);
			break;
		case DEPOSIT:
			deposit_money(acc_arr, &acc_num);
			break;
		case WITHDRAW:
			with_draw_money(acc_arr, &acc_num);
			break;
		case INQUIRE:   // case 4:
			show_all_acc_info(acc_arr, &acc_num);
			break;
		case EXIT:
			free(acc_arr);   // ���� �޸𸮸� ���� �Ѵ�. 
			return 0;
		default:
			printf("Illegal selection..\n");
		}
#endif 
	}
	return 0;
}

void show_menu(void)
{
	char* menu[] =   //  
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
		printf("%s", *(menu + i));   // printf("%s", menu[i]);
}

void make_account(t_account* pt, int* pn)
{
	int id;
	char name[NAME_LEN];
	int balance;
	t_account* p = pt + *pn;

	printf("[���°���]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("��  ��: ");
	scanf("%s", name);
	printf("�Աݾ�: ");
	scanf("%d", &balance);
	printf("\n");

	rewind(filep); // ������ ����� ó������ ��ġ��Ų��.
	for (int i = 0; ; i++)
	{
		if (fread((char*)&p->acc_id, 1, sizeof(t_account), filep) == NULL)
		{
			break;   // ���̻� ���� �����Ͱ� ���� ��
		}
		//�д� ���� ���� ���� ��
		else if (p->acc_id == id)
		{
			printf("Already exist ID %d\n", id);
			return;
		}
	}

	fseek(filep, 0, SEEK_END); // ����� ������ �� ������ ����

	p->acc_id = id;   // (*p).acc_id = id;
	p->balance = balance;
	strcpy(p->cus_name, name);
	fwrite((char*)&p->acc_id, 1, sizeof(t_account), filep);
	*pn += 1;  // pn +=1   �ּҰ� ���� �Ǵ°��̴�. 
}

void deposit_money(t_account* pt, int* pn)
{
	int money;
	int id, i, size;
	t_account* p = pt;

	printf("[��    ��]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("�Աݾ�: ");
	scanf("%d", &money);

	rewind(filep);

	//for (i = 0; i < *pn; i++, p++)
	for (i = 0; ; i++, p++)
	{
		if (fread((char*)&p->acc_id, 1, sizeof(t_account), filep) == NULL)
		{
			break;   // ���̻� ���� �����Ͱ� ���� ��
		}
		//�д� ���� ���� ���� ��
		else if (p->acc_id == id)
		{
			p->balance += money;
			size = sizeof(t_account);
			fseek(filep, -size, SEEK_CUR); // ���� ������� -28byte��ŭ �ű��..
			fwrite((char*)&p->acc_id, 1, sizeof(t_account), filep);
			printf("�ԱݿϷ�\n\n");
			return;
		}
	}
	printf("��ȿ���� ���� ID �Դϴ�.\n\n");
}

void with_draw_money(t_account* pt, int* pn)
{
	int money;
	int id, i, size;
	t_account* p = pt;

	printf("[��    ��]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("��ݾ�: ");
	scanf("%d", &money);

	rewind(filep);

	//for (i = 0; i < *pn; i++, p++)
	for (i = 0; ; i++, p++)
	{
		if (fread((char*)&p->acc_id, 1, sizeof(t_account), filep) == NULL)
		{
			break;   // ���̻� ���� �����Ͱ� ���� ��
		}
		else if (p->acc_id == id)
		{

			if (p->balance < money)
			{
				printf("�ܾ׺���\n\n");
				return;
			}

			p->balance -= money;  // acc_arr[i].balance = acc_arr[i].balance - money;
			size = sizeof(t_account);
			fseek(filep, -size, SEEK_CUR); // ���� ������� -28byte��ŭ �ű��..
			fwrite((char*)&p->acc_id, 1, sizeof(t_account), filep);
			printf("��ݿϷ�\n\n");
			return;
		}
	}
	printf("��ȿ���� ���� ID �Դϴ�.\n\n");
}

void show_all_acc_info(t_account* pt, int* pn)
{
	int i;
	t_account* p = pt;

	rewind(filep); //����� �� ���� �ű�

	//for (i = 0; i < *pn; i++, p++)
	for (i = 0; ; i++, p++)
	{
		if (fread((char*)&p->acc_id, 1, sizeof(t_account), filep) == NULL)
		{
			break;   // ���̻� ���� �����Ͱ� ���� ��
		}
		printf("����ID: %d\n", p->acc_id);
		printf("��  ��: %s\n", p->cus_name);
		printf("��  ��: %d\n\n", p->balance);
	}
	printf("\n");
}
#endif

//17-8 ����    ����ü ������ �迭
#if 0
struct address
{
	char name[20];
	int age;
	char tel[20];
	char addr[80];
};
typedef struct address t_address;

void print_all(t_address* lp);
void print_one(t_address* lp, char* nm);

void print_list(struct address* lp);

int main(void)
{
	char input[80];
	char name[80];
	struct address list[5] = {
		{"ȫ�浿", 23, "111-1111", "�︪�� ����"},
		{"�̼���", 35, "222-2222", "���� ��õ��"},
		{"�庸��", 19, "333-3333", "�ϵ� û����"},
		{"������", 15, "444-4444", "�泲 õ��"},
		{"���߱�", 45, "555-5555", "Ȳ�ص� ����"},
	};

	while (1)
	{
		printf("1: ��ü ����, 2: ���� ����, 9: ������   �Է� : ");
		fgets(input, 10, stdin);
		int sel = atoi(input);
		if (sel == 9)
		{
			break;
		}
		else if (sel == 1)
		{
			print_all(list);
		}
		else if (sel == 2)
		{
			printf("�̸� : ");
			scanf("%s", name);
			getchar();
			print_one(list, name);
		}
	}

	return 0;
}

void print_all(t_address* lp)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		printf("%10s%5d%15s%20s\n", (lp + i)->name, (lp + i)->age, (lp + i)->tel, (lp + i)->addr);
	}
}

void print_one(t_address* lp, char* nm)
{
	int i = 0;
	while (1)
	{
		if (strncmp((lp + i)->name, nm, 3) == 0)
		{
			break;
		}
		i++;
	}
	printf("%10s%5d%15s%20s\n", (lp + i)->name, (lp + i)->age, (lp + i)->tel, (lp + i)->addr);
}

#endif

// ���� �޸� �Ҵ�
/*
1. ����ü �迭 ���� �޸𸮸� ���� �޸𸮷� �Ҵ��ϱ�
2. switch~case ���� �Լ� ������ �迭�� �����ϵ��� �ϱ�
*/
#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //����ü
#include <string.h>
#include <stdlib.h>
#define NAME_LEN   20

//#define : ��ũ�� (MACRO)
#define MAKE     1
#define DEPOSIT  2
#define WITHDRAW 3
#define INQUIRE  4
#define EXIT     9


typedef struct // t_account �� redefine �Ѵ�			28byte
{
	int acc_id;      // ���¹�ȣ
	int balance;    // ��    ��
	char cus_name[NAME_LEN];   // �����̸�
} t_account;

void show_menu(void);
void make_account(t_account* pt, int* pn); // ���� ����
void deposit_money(t_account* pt, int* pn); // �Ա�
void with_draw_money(t_account* pt, int* pn); // ���
void show_all_acc_info(t_account* pt, int* pn); // �ܾ���ȸ

int main()  // int main(argc, char *argv[])
{
	int choice;
	int acc_num = 0;        // ����� Account ��
#if 1
	t_account* acc_arr;	// acc_arr�̶�� ������ t_account Ÿ���� ����ü Ÿ����
	//������(�ּҸ� �����ϴ� ����(����))�̴�.
	void (*fp[]) (t_account*, int*) =
	{
		NULL, // 0�� �迭�� ����.
		make_account,
		deposit_money,
		with_draw_money,
		show_all_acc_info
	};


	acc_arr = (t_account*)malloc(sizeof(t_account) * 10); // ����ü �����ŭ �Ѱ���        acc_arr[10];�̶� ����.			malloc�� charŸ���̶� ����ȯ �ʿ�.
	// malloc�� ���ϵǴ� default�� char *�̳� �̸� ����ü �����ͷ� ��ȯ. (t_account *) ����.
	// acc_arr���� ���� ������ ���ϵȴ�.
	if (acc_arr == NULL)
	{
		printf("�޸� �Ҵ� ����!\n");
		return -1; // 0�� ���� ����, -1�� �ɰ��� error
	}


#else // original
	t_account acc_arr[10];   // Account ������ ���� �迭, 100���� �������� ������.
#endif

	while (1)
	{
		show_menu();
		printf("����:(1 : make, 2: deposit, 3: withdraw, 4 : inquire, 9 : exit)");
		scanf("%d", &choice);  // '1' --> 1 --> choice
		printf("\n");
		if (choice == 9)
		{
			free(acc_arr);
			break;
		}
		if (choice >= 1 && choice <= 4)
		{
			fp[choice](acc_arr, &acc_num);
		}

#if 1 // �Լ� ������ �迭�� ���۵ǵ���

#else	//original
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
			free(acc_arr);	// ���� �޸𸮸� �����Ѵ�.
			return 0;
		default:
			printf("Illegal selection..\n");
		}
#endif
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

void make_account(t_account* pt, int* pn)
{
	int id;
	char name[NAME_LEN];
	int balance;
	t_account* p = pt + *pn; //�ڿ��� �ּ��� �������� Ʋ���� �� �־ ���ǽ�Ŵ.

	printf("[���°���]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("��  ��: ");
	scanf("%s", name);
	printf("�Աݾ�: ");
	scanf("%d", &balance);
	printf("\n");

	p->acc_id = id;
	p->balance = balance;
	strcpy(p->cus_name, name);
	*pn += 1;	// pn += 1 �̷��� �ּҰ� ������.
}

void deposit_money(t_account* pt, int* pn)
{
	int money;
	int id, i;
	t_account* p = pt;

	printf("[��    ��]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("�Աݾ�: ");
	scanf("%d", &money);

	for (i = 0; i < *pn; i++, p++)
	{
		if (p->acc_id == id)
		{
			p->balance += money;
			printf("�ԱݿϷ�\n\n");
			return;
		}
	}
	printf("��ȿ���� ���� ID �Դϴ�.\n\n");
}

void with_draw_money(t_account* pt, int* pn)
{
	t_account* p = pt;
	int money;
	int id, i;

	printf("[��    ��]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("��ݾ�: ");
	scanf("%d", &money);

	for (i = 0; i < *pn; i++, p++)
	{
		if (p->acc_id == id)
		{
			if (p->balance < money)
			{
				printf("�ܾ׺���\n\n");
				return;
			}

			p->balance -= money;  // acc_arr[i].balance = acc_arr[i].balance - money;
			printf("��ݿϷ�\n\n");
			return;
		}
	}
	printf("��ȿ���� ���� ID �Դϴ�.\n\n");
}

void show_all_acc_info(t_account* pt, int* pn)
{
	t_account* p = pt;
	int i;

	for (i = 0; i < *pn; i++, p++)
	{
		printf("����ID: %d\n", p->acc_id);
		printf("��  ��: %s\n", p->cus_name);
		printf("��  ��: %d\n\n", p->balance);
	}
}
#endif 
// ���� �޸� �Ҵ�
#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //����ü
#include <string.h>
#define NAME_LEN   20

#define MAKE     1
#define DEPOSIT  2
#define WITHDRAW 3
#define INQUIRE  4
#define EXIT     9


typedef struct // t_account �� redefine �Ѵ�
{
	int acc_id;      // ���¹�ȣ
	int balance;    // ��    ��
	char cus_name[NAME_LEN];   // �����̸�
} t_account;

void show_menu(void);
void make_account(t_account* pt, int* acc_num); // ���� ����
void deposit_money(t_account* pt, int* acc_num); // �Ա�
void with_draw_money(t_account* pt, int* acc_num); // ���
void show_all_acc_info(t_account* pt, int* acc_num); // �ܾ���ȸ

int main()  // int main(argc, char *argv[])
{
	t_account acc_arr[100];   // Account ������ ���� �迭, 100���� �������� ������.

	int acc_num = 0;        // ����� Account ��
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
			make_account(acc_arr, &acc_num);
			break;
		case DEPOSIT:
			deposit_money(acc_arr, &acc_num);
			break;
		case WITHDRAW:
			with_draw_money(acc_arr, &acc_num);
			break;
		case INQUIRE:
			show_all_acc_info(acc_arr, &acc_num);
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

void make_account(t_account* pt, int* acc_num)
{
	int id;
	char name[NAME_LEN];
	int balance;
	t_account* p = pt + *acc_num; //�ڿ��� �ּ��� �������� Ʋ���� �� �־ ���ǽ�Ŵ.

	printf("[���°���]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("��  ��: ");
	scanf("%s", name);
	printf("�Աݾ�: ");
	scanf("%d", &balance);
	printf("\n");

	p->acc_id = id;
	p->balance = balance;
	strcpy(p->cus_name, name);
	*acc_num += 1;	// pn += 1 �̷��� �ּҰ� ������.
}

void deposit_money(t_account* pt, int* acc_num)
{
	int money;
	int id, i;
	t_account* p = pt;

	printf("[��    ��]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("�Աݾ�: ");
	scanf("%d", &money);

	for (i = 0; i < *acc_num; i++, p++)
	{
		if (p->acc_id == id)
		{
			p->balance += money;
			printf("�ԱݿϷ�\n\n");
			return;
		}
	}
	printf("��ȿ���� ���� ID �Դϴ�.\n\n");
}

void with_draw_money(t_account* pt, int* acc_num)
{
	t_account* p = pt;
	int money;
	int id, i;

	printf("[��    ��]\n");
	printf("����ID: ");
	scanf("%d", &id);
	printf("��ݾ�: ");
	scanf("%d", &money);

	for (i = 0; i < *acc_num; i++, p++)
	{
		if (p->acc_id == id)
		{
			if (p->balance < money)
			{
				printf("�ܾ׺���\n\n");
				return;
			}

			p->balance -= money;  // acc_arr[i].balance = acc_arr[i].balance - money;
			printf("��ݿϷ�\n\n");
			return;
		}
	}
	printf("��ȿ���� ���� ID �Դϴ�.\n\n");
}

void show_all_acc_info(t_account* pt, int* acc_num)
{
	t_account* p = pt;
	int i;

	for (i = 0; i < *acc_num; i++, p++)
	{
		printf("����ID: %d\n", p->acc_id);
		printf("��  ��: %s\n", p->cus_name);
		printf("��  ��: %d\n\n", p->balance);
	}
}
#endif 

/*
1. ����ü�� ���� �޸� �Ҵ� �� ����ڷκ��� �����͸� �Է� �޾� print�ϴ� ���α׷��� �ۼ��Ѵ�. (����ü �����͸� Ȱ��)
	(1) �̸� ���� �ּҸ� �Է� �޾Ƽ� ����ü �迭�� �����ϰ�
	(2) ����ڷ� ���� end �Է��� ������ �Է��� �����ϰ�
	(3) ������� ����ü �迭�� ����� �����͸� ����Ʈ�Ѵ�.
*/
#if 0
#define NUMBER 10

typedef struct person
{
	char name[20];
	int age;
	char address[40];
} t_person;

print_person(t_person* p, int n);
copy_person(t_person* p, char* pn, int* page, char* paddr, int* pcount);

int main(void)
{
	t_person p1[NUMBER]; //����� �����ϱ� ���� �迭
	char name[20];
	int age = 0;
	char address[40];
	int count = 0;

	while (1)
	{
		printf("name age address (exit : end 0 end)  : ");
		scanf("%s", name);
		scanf("%d", age);
		scanf("%s", address);
		// ����ü�� name, age, address�� �־����.
		if (strncmp(name, "end", 3) == 0)
		{
			print_person(p1, count);
			break;
			//�̸�  ����  �ּ�
			//==== ===== =====
		}
		else
		{
			copy_person(p1 + count, name, &age, address, &count);
		}
	}
	return 0;
}

copy_person(t_person* p, char* pn, int* page, char* paddr, int* pcount)
{
	strcpy((*p).name, pn); // strcpy�� �ּҸ� �Ѱ��༭ *�� �� ����
	p->age = *page;
	strcpy(p->address, paddr);
	*pcount += 1;
}

print_person(t_person* p, int n)
{
	t_person* pt = p;

	printf("�̸�   ����   �ּ�\n");
	printf("===================\n");

	for (int i = 0; i < n; i++)
	{
		printf("%-6s %d      %s\n", pt->name, pt->age, pt->address);
		pt++;
	}

}
#endif

/*���ڿ� 1���� ��ġ��
ù��° ���ڿ� : abcdefg
�ι�° ���ڿ� : ABCDEFGH
��ģ ��� : abcdefgABCDEFG
*/
#if 0
merge_func(char* p1, char* p2, char* po);

int main(void)
{
	char input1[80];
	char input2[80];
	char output[200];

	printf("ù��° ���ڿ� : ");
	fgets(input1, 80, stdin); // ���� "\n\0"�� �ٴ´�.

	printf("�ι�° ���ڿ� : ");
	fgets(input2, 80, stdin);

	merge_func(input1, input2, output);
	printf("��ģ ��� : %s\n", output);

	return 0;
}
//call by value : ������ �Ѱ��ִ� ���
//call by reference : �ּҸ� �Ѱ��ִ� ���
merge_func(char* p1, char* p2, char* po)
{
	char* potmp = po;
	char* p2tmp = p2;

	strcpy(potmp, p1); //NULL�� ���� �� ���� ����.
	potmp[strlen(po) - 1] = '\0'; //\n ����

	while (*potmp != '\0') // potmp�� null�� ��� �ִ� ������ �̵��Ѵ�.
		potmp++;

	while (*p2tmp != '\0')
	{
		*potmp++ = *p2tmp++; // ���簡 �ʰ� ���ÿ� ��������	
	}
	*potmp = '\0';

	/*printf("%d %d %d", strlen(p1), strlen(p2), strlen(po));
	for (int j = 0; j < strlen(p1)-1; j++)
	{
		*(po + j) = *(p1 + j);
	}
	printf("%d", strlen(po));
	for (int i = strlen(po)-1; i < strlen(po) + strlen(p2) - 2; i++)
	{
		*(po + i) = *(p2 + i);
	}
	*po = '\0';*/
}
#endif


/*
����(0: +, 1: -, 2: *, 3: /, 9: exit) :
�� ���� �Է� (num1, num2)
���: num1 + num2 =
*/
#if 0
#define SUM(a, b) ( (a) + (b))

void add(int a, int b);
void sub(int a, int b);
void mul(int a, int b);
void div(int a, int b);
int space_check(char* pi);

int main(void)
{
	char input[100];
	int num1, num2;
	int sp = 0, sel = 0;

	while (1)
	{
		printf("����(0: +, 1: -, 2: *, 3: /, 9: exit) : ");
		fgets(input, 100, stdin);
		sel = atoi(input); // 1\n\0  atoi �Լ� Ư¡: \n or \0�� ������ �ڵ����� ����, 1+1�϶� +�� ������ �ڵ����� ����
		if (sel == 9) break;

		printf("�� ���� �Է�(num1 num2) : ");
		fgets(input, 100, stdin); // 111 11
		sp = space_check(input);

		num1 = atoi(input);
		num2 = atoi(input + sp + 1);

		switch (sel)
		{
		case 0:
			printf("��� : %d + %d = %d\n", a, b, SUM(a, b));
			//add(num1, num2);
			break;
		case 1:
			sub(num1, num2);
			break;
		case 2:
			mul(num1, num2);
			break;
		case 3:
			div(num1, num2);
			break;
		default:
			break;
		}
	}
	return 0;
}
// call by reference
int space_check(char* pi)
{
	for (int i = 0; i < 100; i++)
	{
		if (*(pi + i) == ' ')
			return i;
	}
}
// call by value
void add(int a, int b)
{
	printf("��� : %d + %d = %d\n", a, b, a + b);
}

void sub(int a, int b)
{
	printf("��� : %d - %d = %d\n", a, b, a - b);
}

void mul(int a, int b)
{
	printf("��� : %d * %d = %d\n", a, b, a * b);
}

void div(int a, int b)
{
	printf("��� : %d / %d = %d\n", a, b, a / b);
}
#endif

// �Լ� ������ 
// ����õ��(state transition)�� �� switch ~ case �� ���� �Լ� ������ ����� ����.
#if 0
void add(int, int);
void sub(int, int);
void mul(int, int);
void div1(int, int);

//�Լ� ������ ����
void (*fp[]) (int, int) = // �Լ� �ּҸ� �����ϰ� �ִ� �迭
{
	add,	// add �Լ��� ���� ������ fp[0]�� �濡 ����.
	sub,
	mul,
	div1
};

int space_check(char* pi);

int main(void)
{
#if 1 // ���� �޸� �Ҵ�
	char* input;
#else
	char input[100]; // ���� �޸� �Ҵ�
#endif
	int num1, num2;
	int sp = 0, sel = 0;

	input = (char*)malloc(100); // 100byte�� �Ҵ� �޾Ƽ� char ������ ��ȯ�Ͽ� ���� ������ input�̶�� ������(�ּҸ� �����ϴ� ����)�� �־��.

	while (1)
	{
		printf("����(0: +, 1: -, 2: *, 3: /, 9: exit) : ");
		fgets(input, 100, stdin);
		sel = atoi(input); // 1\n\0  atoi �Լ� Ư¡: \n or \0�� ������ �ڵ����� ����, 1+1�϶� +�� ������ �ڵ����� ����
		if (sel == 9) break;

		printf("�� ���� �Է�(num1 num2) : ");
		fgets(input, 100, stdin); // 111 11
		sp = space_check(input);

		num1 = atoi(input);
		num2 = atoi(input + sp + 1);

		fp[sel](num1, num2);
	}
	free(input); // ���� �޸� �Ҵ� ���� �޸𸮸� �ݳ�

	return 0;
}

// call by reference
int space_check(char* pi)
{
	for (int i = 0; i < 100; i++)
	{
		if (*(pi + i) == ' ')
			return i;
	}
}
// call by value
void add(int a, int b)
{
	printf("��� : %d + %d = %d\n", a, b, a + b);
}
void sub(int a, int b)
{
	printf("��� : %d - %d = %d\n", a, b, a - b);
}

void mul(int a, int b)
{
	printf("��� : %d * %d = %d\n", a, b, a * b);
}

void div1(int a, int b)
{
	printf("��� : %d / %d = %d\n", a, b, a / b);
}
#endif

//abc shift ������
#if 0
void shift_alpha();
int main(void)
{
	char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	shift_alpha(alpha);

	return 0;
}

void shift_alpha(char* beta)
{
	char temp;
	for (int i = 0; i < 27; i++)
	{
		printf("%s\n", beta);
		temp = beta[0];
		for (int j = 0; j < 25; j++)
		{
			beta[j] = beta[j + 1];
		}
		beta[25] = temp;
	}
}
#endif

//������
#if 0
/*
1. �����Ͱ� ������?
	�ּҸ� ���� �ϴ� �޸� ����(����)�̴�.
	�Ϲ� �����͸� �����ϴ� ������ "����" ����Ѵ�.

2. �����͸� �� ������?
	(1) ���δٸ� �Լ��� ���ǵ� ������ access(�а�/����)�ϱ� �����̴�.
	�̷��� �����ν� ���������� ����� �ּ�ȭ �Ͽ� �޸��� ���� �����Ͽ� �޸��� ȿ������ ���̰��� ���̴�.
	# ���������� ���α׷��� �����ϰ� �ִ� ���ȿ��� �׻� �޸𸮸� �����ϰ� �ִ�.
	# ���������� ���� ��� ������ �ٸ� ���α׷��� ���µ� ���ظ� �ش�.
	# ������ �������� ����� �ּ�ȭ �� �� �ֵ��� ���α׷��� �ۼ��Ѵ�.
*/
//---- �빮�� <--> �ҹ��� ��ȯ ���α׷�
void upper2lower();

int main(void)
{
	char input[100];	// stack�� �޸𸮰� ������.
	// ���������� ���α׷� ����� �����ִ� ���ȿ��� Ȱ��ȭ �ȴ�.
	// �Լ� ������ ������ �޸𸮰� ���� �ȴ�.
	while (1)
	{
		printf("������ ���ڿ��� �Է�(exit): ");
		fgets(input, 100, stdin);
		if (strncmp(input, "exit", strlen(input) - 1) == NULL)
			break;
		printf("org: %s\n", input);
		printf("input�� �ּ�: %p\n", input);
		upper2lower(input);	// input ������ ���� ������ �Ѱ��ش�. upper2lower(&input[0]);�� ����.
		printf("conv: %s\n", input);
	}
	return 0;
}
// ���� �̸� �տ� "*"�� ���� �ּҸ� �����ϴ� �����̴�.
// char *p: p��� ������ char type�� �ּҸ� �����ϴ� ����
//			�ּҸ� �Ѱ� �شٰ� �ؼ� call by reference��� �Ѵ�.
void upper2lower(char* p)
{
	printf("p�� �ּ� : %p\n", p);

	for (int i = 0; i < 100; i++)
	{
		if (*(p + i) >= 'A' && *(p + i) <= 'Z') // p+i : ���۹��� + i
			*(p + i) += 0x20;	// ������� ���� ������ ����� ������
		// *p : p�� ������ ������ �ؼ� ã�� ���� ���̴�.
	}
}

#endif

#if 0
void test_func();

int main(void)
{
	int a = 10;
	printf("original a : %d\n", a);
	test_func(&a);
	printf("updated a : %d\n", a);
}

void test_func(int* p)
{
	*p = 20;
}
#endif

#if 0
void cal(int* pa, int* pb, int* ptotal, double* pavg);

int main(void)
{
	int a = 10, b = 15, total;
	double avg;

	cal(&a, &b, &total, &avg);

	printf("�� : %d, %d\n", a, b);
	printf("�� : %d\n", total);
	printf("��� : %.1lf\n", avg);

	return 0;
}

void cal(int* pa, int* pb, int* ptotal, double* pavg)
{
	*ptotal = *pa + *pb;
	*pavg = *ptotal / 2.0;
}
#endif

#if 0
int main(void)
{
	char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char temp;
	int j;

	for (int i = 0; i < 27; i++)
	{
		printf("%s\n", alpha);
		temp = alpha[0];
		for (j = 0; j < 25; j++)
		{
			alpha[j] = alpha[j + 1];
		}
		alpha[j] = temp;
	}
	return 0;
}
#endif


/*************		// �������� �ּ� (���α׷� �̸�, ����, �ۼ���, �ۼ���, ��� ��� �ۼ�)
*
*
*
**************/

#if 0 // 0�̸� ���� �� ��,  1�̸� ����
int main(void) { // void�� ����������. ��� ��.
	// ���� (variable) : �ڷ�(data)�� �����ϴ� �޸� ����
	char c; // 1byte(8bit) �������, ���� �ƴ�
	// ���� ���� : -127 ~ 127

	unsigned char uc = 0xff; // 0x00 ~ 0xff, 0 ~ 255
	// unsigned char uc = 0b11111111;
	// unsigned char uc = 255;

	short s; // s��� �̸����� �ؼ� 2byte¥�� ���� ������ Ȯ�� �϶�.
	unsigned short us; // 0 ~ 0xffff	ffff:65535

	int i; // i��� �̸����� �ؼ� 4byte¥�� ���� ������ Ȯ�� �϶�.
	long l; // l��� �̸����� �ؼ� 4byte¥�� ���� ������ Ȯ�� �϶�.

	// �Ʒ� 4���� statement�� ���� ����� �����ϴ�.
	uc = 0xff;  // 0x, 0X : hex
	uc = 0b11111111; // 0b, 0B : binary
	uc = 255;
	uc = 0377; // 0�� ���δ�. : octal

	printf("uc dec : %d\n", uc); // dec������ ���� �� d�� ����
	printf("uc hex : %0x\n", uc); // ff hex������ ���� �� 0x�� ����
	printf("uc oct : %o\n", uc); // oct������ ���� �� o�� ����
	//2������ ���α׷��� ���� ������,

	uc++; // uc = uc + 1;
	// overflow �߻�

	printf("uc dec : %d\n", uc); // 0
	printf("uc hex : %0x\n", uc); // 0
	printf("uc oct : %o\n", uc); // 0

	// sizeof() �Լ� : ������ ũ�Ⱑ �� byte������ Ȯ���ϴ� �Լ��̴�.
	// MCU�� ó�� ������ �� ������ �Լ��̴�.
	char arry[10];
	int iarry[2];
	printf("char�� size : % d\n", sizeof(char)); // ���� type
	printf("c char�� size : % d\n", sizeof(c)); // ���� �̸�
	printf("arry�� size : % d\n", sizeof(arry)); // 10byte
	printf("iarry�� size : % d\n", sizeof(iarry)); // 8byte

	printf("short : %d\n", sizeof(short));
	printf("s short : %d\n", sizeof(s));

	printf("int : %d\n", sizeof(int));
	printf("long : %d\n", sizeof(long));
	printf("float : %d\n", sizeof(float));

	printf("12 dec : %d\n", 12); // 12
	printf("12 hex : %d\n", 0x0c); // 0x0c -> 12
	printf("12 oct : %d\n", 014); // 014 -> 12

	// Ascii Code
	// Space ( ) : 0x20
	// 0 (0) : 0x30
	// A (A) : 0x41
	// a (a) : 0x61
	// �� �ܿ��

	printf("A : %c, size : %d\n", 'A', sizeof((char)'A')); // 1byte�� �������� (char)�߰�
	printf("A : %s, size : %d\n", "A", sizeof("A")); // A\0 ���� null(\0)�� ����.
	// compiler�� ���� null�� �־��ش�.

	char a[10] = "abcdefg"; // ������abcdefg\0
	printf("a : %s\n", a); // %s�� null�� ���� ������ ��� �ϴ� ��
	printf("a sizeof : %d\n", sizeof(a)); // �� memory size
	printf("a : %d\n", strlen(a)); // �޸𸮿� ����ִ� ���� ����

	// a �迭�� �ִ� 0 2 4���� ������ ��� �Ͻÿ�.
	printf("0�� : %c, 2�� : %c, 4�� : %c\n", a[0], a[2], a[4]);
	// a�� 2���濡 �ִ� ������� ������ ��� �Ͻÿ�.
	printf("a�� 2����� ������ ��� : %s\n", a + 2); // a�� �ּҿ� �ִ� ������ 2�� ���� ���
	// a �迭�� �ִ� ������ ���� �ڱ� �̸����� �ٲ� �� �� ������ ����Ͻÿ�
	strcpy(a, "SEONGJIN");
	printf("a : %s\n", a);

	char ch1 = 'A';
	char ch2 = 0x41;
	char ch3 = 0b01000001;

	printf("���� %c�� �ƽ�Ű �ڵ� �� : %d\n", ch1, ch3);
	printf("�ƽ�Ű �ڵ� ���� %d�� ���� : %c\n", ch3, ch3);

	return 0; // 0 : error���� ������ �����ߴ�. -1 : �ɰ��� error. �� �� ������� ���Ǵ�� error code ����.
}
#endif

#if 0
int main(void) {
	// ���ڸ� Ű����� ���� �Է��� �޾� ����Ѵ�.
	// �� q�� �ԷµǸ� ������ �����Ѵ�.
	// q�� �ƴ� ���ڸ� ������ ������ ����Ѵ�.
	char buff[10];
	while (1)
	{
		printf("1���� ���ڸ� �Է��ϼ��� : ");
		fgets(buff, 10, stdin); // fgets : stdin(keyboard ��)���� ���ڸ� �Է� �޾� buff�� �����Ѵ�.
		if (buff[0] == 'q') {
			break;
		}
		printf("���� %c�� �ƽ�Ű �ڵ� �� : %d\n", buff[0], buff[0]);
	}
	return 0;
}
#endif

#if 0
int main(void) {

	char buff[10]; //���� ����
	int num1, num2, result;

	while (1) {
		printf("��Ģ����(1+1=) (���� : q)");
		fgets(buff, 10, stdin);
		//stdin���� ���ڸ� �Է� �޾� buff�� �����Ѵ�.
		//�ִ� 10 char �Ǵ� enter Ű�� ���� �� ���� Ű����� ���� �޾� ���δ�.
		if (buff[0] == 'q')
			break;
		// ascii���� ������ ��ȯ
		num1 = buff[0] - '0'; // buff[0] - 0x30, atoi		num1 : 00000010
		num2 = buff[2] - '0'; // buff[2] - 0x30, atoi		num2 : 00000001
		//������
		if (buff[1] == '+')
			result = num1 + num2; // result : 00000011
		printf("%c + %c = %c\n", num1 + '0', num2 + '0', result + '0');
		// printf("%d + %d = %d\n", num1, num2, result);
		// --> printf�� int�� ascii�� ��ȯ�ؼ� ����ϵ��� �����Ѵ�.
	}
	return 0;
}
#endif

#if 0
int main(void) {

	char buff[10]; //���� ����
	int num1, num2, result;

	while (1) {
		printf("��Ģ���� (���� : q) : ");
		fgets(buff, 10, stdin);
		//stdin���� ���ڸ� �Է� �޾� buff�� �����Ѵ�.
		//�ִ� 10 char �Ǵ� enter Ű�� ���� �� ���� Ű����� ���� �޾� ���δ�.
		if (buff[0] == 'q')
			break;
		// ascii���� ������ ��ȯ
		num1 = buff[0] - '0'; // buff[0] - 0x30, atoi		num1 : 00000010
		num2 = buff[2] - '0'; // buff[2] - 0x30, atoi		num2 : 00000001
		//������
		if (buff[1] == '+')
			result = num1 + num2; // result : 00000011
		if (buff[1] == '-')
			result = num1 - num2;
		if (buff[1] == '*')
			result = num1 * num2;
		if (buff[1] == '/')
			result = num1 / num2;
		printf("%c %c %c = %c\n", num1 + '0', buff[1], num2 + '0', result + '0');
		// printf("%d + %d = %d\n", num1, num2, result);
		// --> printf�� int�� ascii�� ��ȯ�ؼ� ����ϵ��� �����Ѵ�.
	}
	return 0;
}
#endif

#if 0
int main(void)
{
	// floating ó��
	// �Ҽ��� ���� 6�ڸ����� ����ϴ� ���
	printf("%lf\n", 3.4);
	// �Ҽ��� ���� 1�ڸ����� ���
	printf("%.1lf\n", 3.344);
	// �Ҽ��� ���� 10�ڸ����� ���
	printf("%.10lf\n", 3.1234);

	char ch[10]; // abc

	ch[0] = 'a';
	ch[1] = 'b';
	ch[2] = 'c'; // printf("%s\n", ch); --> ch�� �ִ� ������ ����ϴµ� null�� ������ ���� 
	ch[3] = '\0'; // �׻� null�� �־����.

	printf("ch --> %s\n", ch);
	strcpy(ch, "ABC");
	printf("ch --> %s\n", ch);

	return 0;
}
#endif

#if 0
/*
	������ ���ڿ��� �Է� (����:quit) : abcDEFG
	��ȯ ��� : ABCdefg
	������ ���ڿ��� �Է� (����:quit) : DFGa
	��ȯ ��� : dfgA
*/

int main(void)
{
	char alpha[10];

	while (1)
	{
		printf("������ ���ڿ��� �Է� (����:quit) : ");
		fgets(alpha, 100, stdin);
		if (strncmp(alpha, "quit", 4) == NULL) // strcmp(buff, "quit") == 0
		{
			break;
		}
		int len = strlen(alpha);

		for (int i = 0; i < len - 1; i++)
		{
			// if (alpha[i] >= 'A' && alpha[i] <='Z')
			if (alpha[i] < 0x5B) // ���� : A~Z
			{
				alpha[i] = alpha[i] + 0x20;
			}
			// else if (alpha[i] >= 'a' && alpha[i] <= 'z')
			else
			{
				alpha[i] = alpha[i] - 0x20;
			}
		}
		printf("%s\n", alpha);
	}
	return 0;
}
#endif

#if 0
/*
*              ASCII CODE TABLE
*              ================
*
*       DEC       HEX       OCT      CHAR
*       ===       ===       ===      ====
*/
int main(void)
{
	printf("%30s\n", "ASCII CODE TABLE"); // 30ĭ�� �����ʺ��� ����ϰ� �������� ����
	// %-30s 30ĭ�� ���ʺ��� ����ϰ� �������� ����
	printf("%30s\n\n", "================");
	printf("%10s%10s%10s%10s\n", "DEC", "HEX", "OCT", "CHAR");
	printf("%10s%10s%10s%10s\n\n", "===", "===", "===", "====");
	for (int i = 0; i < 128; i++) // i <= 127 ���ٴ� i < 128 �� �ӵ��� �� ������
	{
		printf("%10d%10.2x%10o%10c\n", i, i, i, i);
	}
	return 0;
}
#endif

#if 0
int main(void)
{
	int a;
	double b;

	while (1)
	{
		printf("���̿� Ű�� �Է��ϼ��� : ");
		scanf("%d %lf", &a, &b);

		if (a == 0 && b == 0)
		{
			break;
		}

		printf("���̴� %d��, Ű�� %.1lfcm�Դϴ�.", a, b);
	}
	return 0;
}
#endif

#if 0
/*
*              ASCII CODE TABLE
*              ================
*
*       DEC       HEX       OCT      CHAR
*       ===       ===       ===      ====
*/
int main(void)
{
	printf("%30s\n", "ASCII CODE TABLE"); // 30ĭ�� �����ʺ��� ����ϰ� �������� ����
	// %-30s 30ĭ�� ���ʺ��� ����ϰ� �������� ����
	printf("%30s\n\n", "================");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s%10s\n", "DEC", "HEX", "OCT", "BIN", "CHAR");
		printf("%10s%10s%10s%10s%10s\n\n", "===", "===", "===", "===", "====");
	}
	for (int i = 0; i < 128; i++) // i <= 127 ���ٴ� i < 128 �� �ӵ��� �� ������
	{

		printf("%10d%10.2x%10o  ", i, i, i);
		bin_print(i);
		printf("%10c\n", i);
	}
	return 0;
}
int bin_print(unsigned char x)
{
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", x >> i & 1);
	}
}
#endif

#if 0
int main(void)
{
	char text[32][10] = { "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US" };

	printf("%115s\n", "ASCII CODE TABLE"); // 30ĭ�� �����ʺ��� ����ϰ� �������� ����
	// %-30s 30ĭ�� ���ʺ��� ����ϰ� �������� ����
	printf("%115s\n\n", "================");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s%10s", "DEC", "HEX", "OCT", "BIN", "CHAR");
	}
	printf("\n");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s%10s", "===", "===", "===", "===", "====");
	}
	printf("\n");
	for (int i = 0; i < 32; i++) // i <= 127 ���ٴ� i < 128 �� �ӵ��� �� ������
	{
		printf("%10d%10.2x%10o  ", i, i, i);
		bin_print(i);
		printf("%10s", text[i]);

		printf("%10d%10.2x%10o  ", i + 32, i + 32, i + 32);
		bin_print(i + 32);
		printf("%10c", i + 32);

		printf("%10d%10.2x%10o  ", i + 64, i + 64, i + 64);
		bin_print(i + 64);
		printf("%10c", i + 64);

		printf("%10d%10.2x%10o  ", i + 96, i + 96, i + 96);
		bin_print(i + 96);
		printf("%10c", i + 96);

		printf("\n");
	}

	return 0;
}
int bin_print(unsigned char x)
{
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", x >> i & 1);
	}
}
#endif

#if 0
void bin_div(unsigned char x);

int main(void)
{
	char text[32][10] = { "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US" };

	printf("%115s\n", "ASCII CODE TABLE");
	printf("%115s\n\n", "================");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s%10s", "DEC", "HEX", "OCT", "BIN", "CHAR");
	}
	printf("\n");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s%10s", "===", "===", "===", "===", "====");
	}
	printf("\n");
	for (int i = 0; i < 32; i++) // i <= 127 ���ٴ� i < 128 �� �ӵ��� �� ������
	{
		printf("%10d%10.2x%10o  ", i, i, i);
		//bin_print(i);
		bin_div(i);
		printf("%10s", text[i]);

		printf("%10d%10.2x%10o  ", i + 32, i + 32, i + 32);
		//bin_print(i + 32);
		bin_div(i + 32);
		printf("%10c", i + 32);

		printf("%10d%10.2x%10o  ", i + 64, i + 64, i + 64);
		//bin_print(i + 64);
		bin_div(i + 64);
		printf("%10c", i + 64);

		printf("%10d%10.2x%10o  ", i + 96, i + 96, i + 96);
		//bin_print(i + 96);
		bin_div(i + 96);
		printf("%10c", i + 96);

		printf("\n");
	}

	return 0;
}
//shift ������
#if 0
int bin_print(unsigned char x)
{
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", x >> i & 1);
	}
}
#endif
//div ������
#if 1
void bin_div(unsigned char x)
{
	int b; //��, ������
	char buff[10];
	for (int i = 0; i < 8; i++) {
		b = x % 2;
		x = x / 2;
		buff[i] = b;
		if (x == 1) {
			buff[i + 1] = x;
		}
	}
	for (int j = 7; j >= 0; j--) {
		printf("%d", (int)buff[j]);
	}
}
#endif
#endif

//16������ 2������ ���
#if 0
int main(void) {
	unsigned char uc = 0x73; // 0111 0011
	unsigned short us = 0x7337; //0111 0011 0011 0111

	for (int i = 7; i >= 0; i--) //�ڷ����� ũ�⿡ �°� i ����
	{
		printf("%d", uc >> i & 1);
	}
	printf("\n");

	for (int i = 15; i >= 0; i--)
	{
		printf("%d", us >> i & 1);
	}
	printf("\n");
	return 0;
}
#endif
