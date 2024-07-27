#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc 함수 여기있음.
#endif

/*
1. 구조체 배열
2. 구조체 포인터 (전역 -> 지역)
3. 정적 메모리 -> 동적 메모리 (switch~case -> 함수 포인터 배열)
4. reset -> 파일 처리
5. union
*/

// union (공용체) 학습
// union을 이해하고 union을 쓰는 목적 및 용도를 이해한다.
//--- Big Endian(모토롤라계열)과 Little Endion(인텔)의 차이점
// - 데이터를 처리하는 어드레싱의 최소 단위 : byte
//   데이터를 처리하는데 큰단위 부터 처리할 것인가 작은 단위부터 처리할 것인가
//	 큰단위 처리:Big Endian, 작은단위 처리:Little Endion
// - 0x12345678의 byte data가 있다고 가정하자
//   3130................0
// 
//   MSB(Most Significant Byte) : 0x12
//   LSB(Least Significant Byte) : 0x78
// - Big Endian(모토롤라계열) type으로 데이터를 저장(읽음)
//   0x12 0x34 0x56 0x78
// - Little Endion(인텔계열) type으로 데이터를 저장(읽음)
//   0x78 0x56 0x23 0x12
#if 0
int main(void)
{
	union
	{
		// BYTE 변수의 내용이 변경되면 struct { } s;내의 값도 같이 바뀐다. (공용체)
		unsigned char BYTE;		// 0x1000번지에 메모리가 1byte가 할당 되었다고 가정하자.
		struct   // little endian 0x1000번지 부터 시작
		{
			unsigned b0 : 1;  // 1bit 할당
			unsigned b1 : 1;
			unsigned b2 : 1;
			unsigned b3 : 1;	// 서로 b0~b3는 연동됨.
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

//구조체를 파일 처리(파일 포인터. fseek, rewind)로 구조 변경
// --> 프로그램을 종료 하더라도 이전 정보가 그대로 남아 있도록 하기 위함
// --> 마치 DB와 비슷함.
#if 1
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>    // atoi itoa malloc등이 들어 있다. 
#define NAME_LEN   20

void show_menu(void);       // 메뉴출력

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
/*
struct
{
	int acc_id;     // 계좌번호
	int balance;    // 잔    액
	char cus_name[NAME_LEN];   // 고객이름
} account;

struct account acc_arr[100];
*/
void make_account(t_account* pt, int* pn);   // 계좌개설
void deposit_money(t_account* pt, int* pn);  // 입금
void with_draw_money(t_account* pt, int* pn);  // 출금 
void show_all_acc_info(t_account* pt, int* pn); // 잔액조회

FILE* filep;   // 이름은 money_file



int main()  // int main(argc, char *argv[])
{
	int choice;
#if 0
	t_account* acc_arr;   // acc_arr라는 변수는 t_account 타입의 구조체 타입의 
	// 포인터(주소를 저장하는 공간(변수) 이다. 
	void (*fp[]) (t_account*, int*) =
	{
		NULL, // 0
		make_account,
		deposit_money,
		with_draw_money,
		show_all_acc_info
	};


	acc_arr = (t_account*)malloc(sizeof(t_account) * 10);   // acc_arr[10];
	// malloc의 리턴 되는 default는 char *이나 이를 구조체 포인터로 변환
	// acc_arr에는 시작 번지가 리턴 된다. 
	if (acc_arr == NULL)
	{
		printf("메모리 할당 실패 @!!!!!\n");
		return -1;   // 0: 정상종, -1: 심각한 error
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
	t_account acc_arr[10];   // Account 저장을 위한 배열
#endif 

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

#if 0  // 함수 포인터 배열로 동작 되도록 완성 하시오 
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
			free(acc_arr);   // 동적 메모리를 해제 한다. 
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

//17-8 문제    구조체 포인터 배열
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
		{"홍길동", 23, "111-1111", "울릉도 독도"},
		{"이순신", 35, "222-2222", "서울 건천동"},
		{"장보고", 19, "333-3333", "완도 청해진"},
		{"유관순", 15, "444-4444", "충남 천안"},
		{"안중근", 45, "555-5555", "황해도 해주"},
	};

	while (1)
	{
		printf("1: 전체 보기, 2: 선택 보기, 9: 나가기   입력 : ");
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
			printf("이름 : ");
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

// 동적 메모리 할당
/*
1. 구조체 배열 정적 메모리를 동적 메모리로 할당하기
2. switch~case 문을 함수 포인터 배열로 동작하도록 하기
*/
#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //구조체
#include <string.h>
#include <stdlib.h>
#define NAME_LEN   20

//#define : 매크로 (MACRO)
#define MAKE     1
#define DEPOSIT  2
#define WITHDRAW 3
#define INQUIRE  4
#define EXIT     9


typedef struct // t_account 로 redefine 한다			28byte
{
	int acc_id;      // 계좌번호
	int balance;    // 잔    액
	char cus_name[NAME_LEN];   // 고객이름
} t_account;

void show_menu(void);
void make_account(t_account* pt, int* pn); // 계좌 개설
void deposit_money(t_account* pt, int* pn); // 입금
void with_draw_money(t_account* pt, int* pn); // 출금
void show_all_acc_info(t_account* pt, int* pn); // 잔액조회

int main()  // int main(argc, char *argv[])
{
	int choice;
	int acc_num = 0;        // 저장된 Account 수
#if 1
	t_account* acc_arr;	// acc_arr이라는 변수는 t_account 타입의 구조체 타입의
	//포인터(주소를 저장하는 공간(변수))이다.
	void (*fp[]) (t_account*, int*) =
	{
		NULL, // 0번 배열은 버림.
		make_account,
		deposit_money,
		with_draw_money,
		show_all_acc_info
	};


	acc_arr = (t_account*)malloc(sizeof(t_account) * 10); // 구조체 사이즈만큼 넘겨줌        acc_arr[10];이랑 같음.			malloc은 char타입이라 형변환 필요.
	// malloc의 리턴되는 default는 char *이나 이를 구조체 포인터로 변환. (t_account *) 붙임.
	// acc_arr에는 시작 번지가 리턴된다.
	if (acc_arr == NULL)
	{
		printf("메모리 할당 실패!\n");
		return -1; // 0은 정상 종료, -1은 심각한 error
	}


#else // original
	t_account acc_arr[10];   // Account 저장을 위한 배열, 100개가 연속으로 잡힌다.
#endif

	while (1)
	{
		show_menu();
		printf("선택:(1 : make, 2: deposit, 3: withdraw, 4 : inquire, 9 : exit)");
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

#if 1 // 함수 포인터 배열로 동작되도록

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
			free(acc_arr);	// 동적 메모리를 해제한다.
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

void make_account(t_account* pt, int* pn)
{
	int id;
	char name[NAME_LEN];
	int balance;
	t_account* p = pt + *pn; //뒤에서 주소의 시작점이 틀어질 수 있어서 대피시킴.

	printf("[계좌개설]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("이  름: ");
	scanf("%s", name);
	printf("입금액: ");
	scanf("%d", &balance);
	printf("\n");

	p->acc_id = id;
	p->balance = balance;
	strcpy(p->cus_name, name);
	*pn += 1;	// pn += 1 이렇게 주소가 증가됨.
}

void deposit_money(t_account* pt, int* pn)
{
	int money;
	int id, i;
	t_account* p = pt;

	printf("[입    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("입금액: ");
	scanf("%d", &money);

	for (i = 0; i < *pn; i++, p++)
	{
		if (p->acc_id == id)
		{
			p->balance += money;
			printf("입금완료\n\n");
			return;
		}
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void with_draw_money(t_account* pt, int* pn)
{
	t_account* p = pt;
	int money;
	int id, i;

	printf("[출    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("출금액: ");
	scanf("%d", &money);

	for (i = 0; i < *pn; i++, p++)
	{
		if (p->acc_id == id)
		{
			if (p->balance < money)
			{
				printf("잔액부족\n\n");
				return;
			}

			p->balance -= money;  // acc_arr[i].balance = acc_arr[i].balance - money;
			printf("출금완료\n\n");
			return;
		}
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void show_all_acc_info(t_account* pt, int* pn)
{
	t_account* p = pt;
	int i;

	for (i = 0; i < *pn; i++, p++)
	{
		printf("계좌ID: %d\n", p->acc_id);
		printf("이  름: %s\n", p->cus_name);
		printf("잔  액: %d\n\n", p->balance);
	}
}
#endif 
// 정적 메모리 할당
#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //구조체
#include <string.h>
#define NAME_LEN   20

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

void show_menu(void);
void make_account(t_account* pt, int* acc_num); // 계좌 개설
void deposit_money(t_account* pt, int* acc_num); // 입금
void with_draw_money(t_account* pt, int* acc_num); // 출금
void show_all_acc_info(t_account* pt, int* acc_num); // 잔액조회

int main()  // int main(argc, char *argv[])
{
	t_account acc_arr[100];   // Account 저장을 위한 배열, 100개가 연속으로 잡힌다.

	int acc_num = 0;        // 저장된 Account 수
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

void make_account(t_account* pt, int* acc_num)
{
	int id;
	char name[NAME_LEN];
	int balance;
	t_account* p = pt + *acc_num; //뒤에서 주소의 시작점이 틀어질 수 있어서 대피시킴.

	printf("[계좌개설]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("이  름: ");
	scanf("%s", name);
	printf("입금액: ");
	scanf("%d", &balance);
	printf("\n");

	p->acc_id = id;
	p->balance = balance;
	strcpy(p->cus_name, name);
	*acc_num += 1;	// pn += 1 이렇게 주소가 증가됨.
}

void deposit_money(t_account* pt, int* acc_num)
{
	int money;
	int id, i;
	t_account* p = pt;

	printf("[입    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("입금액: ");
	scanf("%d", &money);

	for (i = 0; i < *acc_num; i++, p++)
	{
		if (p->acc_id == id)
		{
			p->balance += money;
			printf("입금완료\n\n");
			return;
		}
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void with_draw_money(t_account* pt, int* acc_num)
{
	t_account* p = pt;
	int money;
	int id, i;

	printf("[출    금]\n");
	printf("계좌ID: ");
	scanf("%d", &id);
	printf("출금액: ");
	scanf("%d", &money);

	for (i = 0; i < *acc_num; i++, p++)
	{
		if (p->acc_id == id)
		{
			if (p->balance < money)
			{
				printf("잔액부족\n\n");
				return;
			}

			p->balance -= money;  // acc_arr[i].balance = acc_arr[i].balance - money;
			printf("출금완료\n\n");
			return;
		}
	}
	printf("유효하지 않은 ID 입니다.\n\n");
}

void show_all_acc_info(t_account* pt, int* acc_num)
{
	t_account* p = pt;
	int i;

	for (i = 0; i < *acc_num; i++, p++)
	{
		printf("계좌ID: %d\n", p->acc_id);
		printf("이  름: %s\n", p->cus_name);
		printf("잔  액: %d\n\n", p->balance);
	}
}
#endif 

/*
1. 구조체를 정적 메모리 할당 후 사용자로부터 데이터를 입력 받아 print하는 프로그램을 작성한다. (구조체 포인터를 활용)
	(1) 이름 나이 주소를 입력 받아서 구조체 배열에 저장하고
	(2) 사용자로 부터 end 입력을 받으면 입력을 종료하고
	(3) 현재까지 구조체 배열에 저장된 데이터를 프린트한다.
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
	t_person p1[NUMBER]; //사람을 저장하기 위한 배열
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
		// 구조체에 name, age, address를 넣어야함.
		if (strncmp(name, "end", 3) == 0)
		{
			print_person(p1, count);
			break;
			//이름  나이  주소
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
	strcpy((*p).name, pn); // strcpy는 주소를 넘겨줘서 *를 안 붙임
	p->age = *page;
	strcpy(p->address, paddr);
	*pcount += 1;
}

print_person(t_person* p, int n)
{
	t_person* pt = p;

	printf("이름   나이   주소\n");
	printf("===================\n");

	for (int i = 0; i < n; i++)
	{
		printf("%-6s %d      %s\n", pt->name, pt->age, pt->address);
		pt++;
	}

}
#endif

/*문자열 1개로 합치기
첫번째 문자열 : abcdefg
두번째 문자열 : ABCDEFGH
합친 결과 : abcdefgABCDEFG
*/
#if 0
merge_func(char* p1, char* p2, char* po);

int main(void)
{
	char input1[80];
	char input2[80];
	char output[200];

	printf("첫번째 문자열 : ");
	fgets(input1, 80, stdin); // 끝에 "\n\0"이 붙는다.

	printf("두번째 문자열 : ");
	fgets(input2, 80, stdin);

	merge_func(input1, input2, output);
	printf("합친 결과 : %s\n", output);

	return 0;
}
//call by value : 변수를 넘겨주는 방식
//call by reference : 주소를 넘겨주는 방식
merge_func(char* p1, char* p2, char* po)
{
	char* potmp = po;
	char* p2tmp = p2;

	strcpy(potmp, p1); //NULL을 만날 대 까지 복사.
	potmp[strlen(po) - 1] = '\0'; //\n 제거

	while (*potmp != '\0') // potmp를 null이 들어 있는 번지로 이동한다.
		potmp++;

	while (*p2tmp != '\0')
	{
		*potmp++ = *p2tmp++; // 복사가 됨과 동시에 증가가됨	
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
선택(0: +, 1: -, 2: *, 3: /, 9: exit) :
두 수를 입력 (num1, num2)
결과: num1 + num2 =
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
		printf("선택(0: +, 1: -, 2: *, 3: /, 9: exit) : ");
		fgets(input, 100, stdin);
		sel = atoi(input); // 1\n\0  atoi 함수 특징: \n or \0를 만나면 자동으로 멈춤, 1+1일때 +를 만나면 자동으로 멈춤
		if (sel == 9) break;

		printf("두 수를 입력(num1 num2) : ");
		fgets(input, 100, stdin); // 111 11
		sp = space_check(input);

		num1 = atoi(input);
		num2 = atoi(input + sp + 1);

		switch (sel)
		{
		case 0:
			printf("결과 : %d + %d = %d\n", a, b, SUM(a, b));
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
	printf("결과 : %d + %d = %d\n", a, b, a + b);
}

void sub(int a, int b)
{
	printf("결과 : %d - %d = %d\n", a, b, a - b);
}

void mul(int a, int b)
{
	printf("결과 : %d * %d = %d\n", a, b, a * b);
}

void div(int a, int b)
{
	printf("결과 : %d / %d = %d\n", a, b, a / b);
}
#endif

// 함수 포인터 
// 상태천이(state transition)할 때 switch ~ case 문 보다 함수 포인터 사용을 권장.
#if 0
void add(int, int);
void sub(int, int);
void mul(int, int);
void div1(int, int);

//함수 포인터 변수
void (*fp[]) (int, int) = // 함수 주소를 저장하고 있는 배열
{
	add,	// add 함수의 시작 번지가 fp[0]번 방에 들어간다.
	sub,
	mul,
	div1
};

int space_check(char* pi);

int main(void)
{
#if 1 // 동적 메모리 할당
	char* input;
#else
	char input[100]; // 정적 메모리 할당
#endif
	int num1, num2;
	int sp = 0, sel = 0;

	input = (char*)malloc(100); // 100byte를 할당 받아서 char 형으로 변환하여 시작 번지를 input이라는 포인터(주소를 저장하는 변수)에 넣어라.

	while (1)
	{
		printf("선택(0: +, 1: -, 2: *, 3: /, 9: exit) : ");
		fgets(input, 100, stdin);
		sel = atoi(input); // 1\n\0  atoi 함수 특징: \n or \0를 만나면 자동으로 멈춤, 1+1일때 +를 만나면 자동으로 멈춤
		if (sel == 9) break;

		printf("두 수를 입력(num1 num2) : ");
		fgets(input, 100, stdin); // 111 11
		sp = space_check(input);

		num1 = atoi(input);
		num2 = atoi(input + sp + 1);

		fp[sel](num1, num2);
	}
	free(input); // 동적 메모리 할당 받은 메모리를 반납

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
	printf("결과 : %d + %d = %d\n", a, b, a + b);
}
void sub(int a, int b)
{
	printf("결과 : %d - %d = %d\n", a, b, a - b);
}

void mul(int a, int b)
{
	printf("결과 : %d * %d = %d\n", a, b, a * b);
}

void div1(int a, int b)
{
	printf("결과 : %d / %d = %d\n", a, b, a / b);
}
#endif

//abc shift 포인터
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

//포인터
#if 0
/*
1. 포인터가 뭐에요?
	주소를 저장 하는 메모리 공간(변수)이다.
	일반 데이터를 저장하는 공간은 "변수" 라고한다.

2. 포인터를 왜 쓰지요?
	(1) 서로다른 함수에 정의된 변수를 access(읽고/쓰기)하기 위함이다.
	이렇게 함으로써 전역변수의 사용을 최소화 하여 메모리의 낭비를 제거하여 메모리의 효율성을 높이고자 함이다.
	# 전역변수는 프로그램이 실행하고 있는 동안에는 항상 메모리를 점유하고 있다.
	# 전역변수를 많이 잡고 있으면 다른 프로그램이 도는데 방해를 준다.
	# 가능한 전역변수 사용을 최소화 할 수 있도록 프로그램을 작성한다.
*/
//---- 대문자 <--> 소문자 변환 프로그램
void upper2lower();

int main(void)
{
	char input[100];	// stack에 메모리가 잡힌다.
	// 지역변수로 프로그램 모듈이 돌고있는 동안에만 활성화 된다.
	// 함수 실행이 끝나면 메모리가 삭제 된다.
	while (1)
	{
		printf("임의의 문자열을 입력(exit): ");
		fgets(input, 100, stdin);
		if (strncmp(input, "exit", strlen(input) - 1) == NULL)
			break;
		printf("org: %s\n", input);
		printf("input의 주소: %p\n", input);
		upper2lower(input);	// input 변수의 시작 번지를 넘겨준다. upper2lower(&input[0]);도 가능.
		printf("conv: %s\n", input);
	}
	return 0;
}
// 변수 이름 앞에 "*"가 들어가면 주소를 저장하는 변수이다.
// char *p: p라는 변수는 char type의 주소를 저장하는 변수
//			주소를 넘겨 준다고 해서 call by reference라고 한다.
void upper2lower(char* p)
{
	printf("p의 주소 : %p\n", p);

	for (int i = 0; i < 100; i++)
	{
		if (*(p + i) >= 'A' && *(p + i) <= 'Z') // p+i : 시작번지 + i
			*(p + i) += 0x20;	// 선언시의 모양과 실행의 모양이 같지만
		// *p : p의 내용을 번지로 해서 찾아 가는 것이다.
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

	printf("값 : %d, %d\n", a, b);
	printf("합 : %d\n", total);
	printf("평균 : %.1lf\n", avg);

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


/*************		// 블럭단위 주석 (프로그램 이름, 버전, 작성자, 작성일, 기능 등등 작성)
*
*
*
**************/

#if 0 // 0이면 실행 안 됨,  1이면 실행
int main(void) { // void는 가독성때문. 없어도 됨.
	// 변수 (variable) : 자료(data)를 저장하는 메모리 공간
	char c; // 1byte(8bit) 저장공간, 문자 아님
	// 저장 범위 : -127 ~ 127

	unsigned char uc = 0xff; // 0x00 ~ 0xff, 0 ~ 255
	// unsigned char uc = 0b11111111;
	// unsigned char uc = 255;

	short s; // s라는 이름으로 해서 2byte짜리 저장 공간을 확보 하라.
	unsigned short us; // 0 ~ 0xffff	ffff:65535

	int i; // i라는 이름으로 해서 4byte짜리 저장 공간을 확보 하라.
	long l; // l라는 이름으로 해서 4byte짜리 저장 공간을 확보 하라.

	// 아래 4개의 statement의 실행 결과가 동일하다.
	uc = 0xff;  // 0x, 0X : hex
	uc = 0b11111111; // 0b, 0B : binary
	uc = 255;
	uc = 0377; // 0을 붙인다. : octal

	printf("uc dec : %d\n", uc); // dec값으로 찍을 때 d를 붙임
	printf("uc hex : %0x\n", uc); // ff hex값으로 찍을 때 0x를 붙임
	printf("uc oct : %o\n", uc); // oct값으로 찍을 때 o를 붙임
	//2진수는 프로그램을 따로 찍어야함,

	uc++; // uc = uc + 1;
	// overflow 발생

	printf("uc dec : %d\n", uc); // 0
	printf("uc hex : %0x\n", uc); // 0
	printf("uc oct : %o\n", uc); // 0

	// sizeof() 함수 : 변수의 크기가 몇 byte인지를 확인하는 함수이다.
	// MCU를 처음 접했을 때 유용한 함수이다.
	char arry[10];
	int iarry[2];
	printf("char의 size : % d\n", sizeof(char)); // 변수 type
	printf("c char의 size : % d\n", sizeof(c)); // 변수 이름
	printf("arry의 size : % d\n", sizeof(arry)); // 10byte
	printf("iarry의 size : % d\n", sizeof(iarry)); // 8byte

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
	// 꼭 외우기

	printf("A : %c, size : %d\n", 'A', sizeof((char)'A')); // 1byte로 잡으러면 (char)추가
	printf("A : %s, size : %d\n", "A", sizeof("A")); // A\0 끝에 null(\0)이 들어간다.
	// compiler가 끝에 null을 넣어준다.

	char a[10] = "abcdefg"; // 실제론abcdefg\0
	printf("a : %s\n", a); // %s는 null을 만날 때까지 출력 하는 것
	printf("a sizeof : %d\n", sizeof(a)); // 총 memory size
	printf("a : %d\n", strlen(a)); // 메모리에 들어있는 변수 길이

	// a 배열에 있는 0 2 4방의 내용을 출력 하시오.
	printf("0번 : %c, 2번 : %c, 4번 : %c\n", a[0], a[2], a[4]);
	// a의 2번방에 있는 내용부터 끝까지 출력 하시오.
	printf("a의 2방부터 끝까지 출력 : %s\n", a + 2); // a의 주소에 있는 값을를 2번 부터 출력
	// a 배열에 있는 내용을 영문 자기 이름으로 바꾼 후 그 내용을 출력하시오
	strcpy(a, "SEONGJIN");
	printf("a : %s\n", a);

	char ch1 = 'A';
	char ch2 = 0x41;
	char ch3 = 0b01000001;

	printf("문자 %c의 아스키 코드 값 : %d\n", ch1, ch3);
	printf("아스키 코드 값이 %d인 문자 : %c\n", ch3, ch3);

	return 0; // 0 : error없이 실행을 종료했다. -1 : 심각한 error. 그 외 사용자의 편의대로 error code 정의.
}
#endif

#if 0
int main(void) {
	// 문자를 키보드로 부터 입력을 받아 출력한다.
	// 단 q가 입력되면 실행을 종료한다.
	// q가 아닌 문자를 받으면 실행을 계속한다.
	char buff[10];
	while (1)
	{
		printf("1개의 문자를 입력하세요 : ");
		fgets(buff, 10, stdin); // fgets : stdin(keyboard 등)부터 문자를 입력 받아 buff에 저장한다.
		if (buff[0] == 'q') {
			break;
		}
		printf("문자 %c의 아스키 코드 값 : %d\n", buff[0], buff[0]);
	}
	return 0;
}
#endif

#if 0
int main(void) {

	char buff[10]; //지역 변수
	int num1, num2, result;

	while (1) {
		printf("사칙연산(1+1=) (종료 : q)");
		fgets(buff, 10, stdin);
		//stdin부터 문자를 입력 받아 buff에 저장한다.
		//최대 10 char 또는 enter 키를 만날 때 까지 키보드로 부터 받아 들인다.
		if (buff[0] == 'q')
			break;
		// ascii값을 정수로 변환
		num1 = buff[0] - '0'; // buff[0] - 0x30, atoi		num1 : 00000010
		num2 = buff[2] - '0'; // buff[2] - 0x30, atoi		num2 : 00000001
		//연산자
		if (buff[1] == '+')
			result = num1 + num2; // result : 00000011
		printf("%c + %c = %c\n", num1 + '0', num2 + '0', result + '0');
		// printf("%d + %d = %d\n", num1, num2, result);
		// --> printf가 int를 ascii로 변환해서 출력하도록 지정한다.
	}
	return 0;
}
#endif

#if 0
int main(void) {

	char buff[10]; //지역 변수
	int num1, num2, result;

	while (1) {
		printf("사칙연산 (종료 : q) : ");
		fgets(buff, 10, stdin);
		//stdin부터 문자를 입력 받아 buff에 저장한다.
		//최대 10 char 또는 enter 키를 만날 때 까지 키보드로 부터 받아 들인다.
		if (buff[0] == 'q')
			break;
		// ascii값을 정수로 변환
		num1 = buff[0] - '0'; // buff[0] - 0x30, atoi		num1 : 00000010
		num2 = buff[2] - '0'; // buff[2] - 0x30, atoi		num2 : 00000001
		//연산자
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
		// --> printf가 int를 ascii로 변환해서 출력하도록 지정한다.
	}
	return 0;
}
#endif

#if 0
int main(void)
{
	// floating 처리
	// 소수점 이하 6자리까지 출력하는 기능
	printf("%lf\n", 3.4);
	// 소수점 이하 1자리까지 출력
	printf("%.1lf\n", 3.344);
	// 소수점 이하 10자리까지 출력
	printf("%.10lf\n", 3.1234);

	char ch[10]; // abc

	ch[0] = 'a';
	ch[1] = 'b';
	ch[2] = 'c'; // printf("%s\n", ch); --> ch에 있는 내용을 출력하는데 null을 만날때 까지 
	ch[3] = '\0'; // 항상 null이 있어야함.

	printf("ch --> %s\n", ch);
	strcpy(ch, "ABC");
	printf("ch --> %s\n", ch);

	return 0;
}
#endif

#if 0
/*
	임의의 문자열을 입력 (종료:quit) : abcDEFG
	변환 결과 : ABCdefg
	임의의 문자열을 입력 (종료:quit) : DFGa
	변환 결과 : dfgA
*/

int main(void)
{
	char alpha[10];

	while (1)
	{
		printf("임의의 문자열을 입력 (종료:quit) : ");
		fgets(alpha, 100, stdin);
		if (strncmp(alpha, "quit", 4) == NULL) // strcmp(buff, "quit") == 0
		{
			break;
		}
		int len = strlen(alpha);

		for (int i = 0; i < len - 1; i++)
		{
			// if (alpha[i] >= 'A' && alpha[i] <='Z')
			if (alpha[i] < 0x5B) // 범위 : A~Z
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
	printf("%30s\n", "ASCII CODE TABLE"); // 30칸을 오른쪽부터 출력하고 나머지는 공백
	// %-30s 30칸을 왼쪽부터 출력하고 나머지는 공백
	printf("%30s\n\n", "================");
	printf("%10s%10s%10s%10s\n", "DEC", "HEX", "OCT", "CHAR");
	printf("%10s%10s%10s%10s\n\n", "===", "===", "===", "====");
	for (int i = 0; i < 128; i++) // i <= 127 보다는 i < 128 이 속도가 더 빠르다
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
		printf("나이와 키를 입력하세요 : ");
		scanf("%d %lf", &a, &b);

		if (a == 0 && b == 0)
		{
			break;
		}

		printf("나이는 %d살, 키는 %.1lfcm입니다.", a, b);
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
	printf("%30s\n", "ASCII CODE TABLE"); // 30칸을 오른쪽부터 출력하고 나머지는 공백
	// %-30s 30칸을 왼쪽부터 출력하고 나머지는 공백
	printf("%30s\n\n", "================");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s%10s\n", "DEC", "HEX", "OCT", "BIN", "CHAR");
		printf("%10s%10s%10s%10s%10s\n\n", "===", "===", "===", "===", "====");
	}
	for (int i = 0; i < 128; i++) // i <= 127 보다는 i < 128 이 속도가 더 빠르다
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

	printf("%115s\n", "ASCII CODE TABLE"); // 30칸을 오른쪽부터 출력하고 나머지는 공백
	// %-30s 30칸을 왼쪽부터 출력하고 나머지는 공백
	printf("%115s\n\n", "================");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s%10s", "DEC", "HEX", "OCT", "BIN", "CHAR");
	}
	printf("\n");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s%10s", "===", "===", "===", "===", "====");
	}
	printf("\n");
	for (int i = 0; i < 32; i++) // i <= 127 보다는 i < 128 이 속도가 더 빠르다
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
	for (int i = 0; i < 32; i++) // i <= 127 보다는 i < 128 이 속도가 더 빠르다
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
//shift 연산자
#if 0
int bin_print(unsigned char x)
{
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", x >> i & 1);
	}
}
#endif
//div 연산자
#if 1
void bin_div(unsigned char x)
{
	int b; //몫, 나머지
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

//16진수를 2진수로 출력
#if 0
int main(void) {
	unsigned char uc = 0x73; // 0111 0011
	unsigned short us = 0x7337; //0111 0011 0011 0111

	for (int i = 7; i >= 0; i--) //자료형의 크기에 맞게 i 조절
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
