​#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

enum { RESERVATION = 1, CHECKOUT, MODIFICATION, ONE_INQUIRE, ALL_INQUIRE, EXIT = 9 };

typedef struct _node {
    int roomno;   // 방 번호
    char name[20];       // 이름
    char phone[40];     // 전화번호
    int  price;                  // 요금
    char address[40];  // 주소
    char enter_date[20];   // 입실 시각
    char exit_date[20];     //  퇴실 시각
    struct _node* prev;  // 이전 노드
    struct _node* next;  // 다음 노드
} t_NODE;

void show_menu(void);       // 메뉴출력
void reservation(t_NODE** head, int* pn); // 예약
void checkout(t_NODE** head, int* pn); // 퇴실
void modification(t_NODE** head, int* pn); // 수정
void one_inquire(t_NODE** head, int* pn); // 개별조회
void all_inquire(t_NODE** head, int* pn); // 예약자 전체 조회
void load_reservatiom(t_NODE** head, int* pn);

 FILE *fp;

int main()
{
    int choice;

    void (*r_fp[]) (t_NODE**, int*) =
    {
        NULL, // 0
        reservation,
        checkout,
        modification,
        one_inquire,
        all_inquire
    };

    t_NODE* head = NULL;  // 리스트의 헤드
    int rev_num = 0;        // 저장된 Account 수

    // 파일 열기
    if ((fp = fopen("reservation_list", "rb+")) == NULL)
    {
        // 파일 없으면 새로 만들기 
        if ((fp = fopen("reservation_list", "wb+")) == NULL)
        {
            fprintf(stderr, "Can't open reservation_list\n");
            exit(1);
        }
    }
    else // 파일 있으면 정보 로딩
    {
        load_accounts(&head, &rev_num); 
    }

    while (1)
    {
        show_menu();
        printf("원하는 메뉴를 선택하세요 : ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == EXIT)
        {
            // 리스트 메모리 해제
            t_NODE* current = head;
            while (current != NULL) {
                t_NODE* next = current->next;
                free(current);
                current = next;
            }
            fclose(fp);
            break;
        }
        if (choice >= RESERVATION && choice <= ALL_INQUIRE)
            r_fp[choice](&head, &rev_num);
    }
    return 0;
}

void show_menu(void)
{
    char* menu[] =
    {
    "------------------ < 객실 관리 > ---------------------\n",
    "1. 입력(예약)\n",
    "2. 삭제(퇴실)\n",
    "3. 수정(예약내역수정)\n",
    "4. 조회(개별조회)\n",
    "5. 전체조회(예약자 전쳬조회)\n",
    "9. 종료\n"
    };

    for (int i = 0; i < 7; i++)
        printf("%s", menu[i]);
}

void reservation(t_NODE** head, int* pn)
{
    int want_roomno;   // 방 번호
    char name[20];       // 이름
    char phone[40];     // 전화번호
    char address[40];  // 주소

    int  room_price;         // 요금
    char enter_date[20];   // 입실 시각
    char exit_date[20];     //  퇴실 시각

    printf("호텔 객실 예약\n");
    printf("예약할 방 번호 (1001 ~ 3010 각 층엔 방이 10개 있습니다.) : ");
    scanf("%d", &want_roomno);
    printf("예약자 성함 : ");
    scanf("%s", name);
    printf("예약자 전화번호 : ");
    scanf("%s", phone);
    printf("예약자 주소 : ");
    scanf("%s", address);
    printf("\n");

    t_NODE* current = *head;
    while (current != NULL) {
        if (current->roomno == want_roomno) {
            printf("예약된 객실입니다. 다른 객실을 선택해주세요. %d\n", want_roomno);
            return;
        }
        current = current->next;
    }

    t_NODE* new_reservation = (t_NODE*)malloc(sizeof(t_NODE));
    new_reservation->roomno = want_roomno;
    strcpy(new_reservation->name, name);
    strcpy(new_reservation->phone, phone);
    strcpy(new_reservation->address, address);
    if (want_roomno >= 1001 && want_roomno <= 1910)
    {
        room_price = 300000;
        strcpy(new_reservation->enter_date, "오후 4시");
        strcpy(new_reservation->exit_date, "오전 11시");
    }
    else if (want_roomno >= 2001 && want_roomno < 2910)
    {
        room_price = 500000;
        strcpy(new_reservation->enter_date, "오후 3시");
        strcpy(new_reservation->exit_date, "오전 11시");
    }
    else if (want_roomno >= 3001 && want_roomno < 3010)
    {
        room_price = 1000000;
        strcpy(new_reservation->enter_date, "오후 3시");
        strcpy(new_reservation->exit_date, "오후 1시");
    }
    new_reservation->price = room_price;
    new_reservation->prev = NULL;
    new_reservation->next = *head;

    if (*head != NULL)
        (*head)->prev = new_reservation;
    *head = new_reservation;

    (*pn)++;
    printf("계좌가 개설되었습니다.\n\n");

    // 파일에 저장
    fseek(fp, 0, SEEK_END);
    fwrite(new_reservation, sizeof(t_NODE), 1, fp);
}

void checkout(t_NODE** head, int* pn)
{
    int want_checkout;
    printf("체크아웃을 원하는 객실 번호를 입력하세요.\n");
    printf("객실 번호 : ");
    scanf("%d", &want_checkout);

    t_NODE* current = *head;
    while (current != NULL) {
        if (current->roomno == want_checkout) {
            if (current->prev != NULL)
                current->prev->next = current->next;
            else
                *head = current->next;

            if (current->next != NULL)
                current->next->prev = current->prev;

            free(current);
            (*pn)--;
            printf("체크아웃이 완료되었습니다. 감사합니다.\n\n");
            
            rewind(fp);
            current = *head;
            while (current != NULL) {
                fwrite(current, sizeof(t_NODE), 1, fp);
                current = current->next;
            }
            return;
        }
        current = current->next;
    }
    printf("유효하지 않는 객실 번호입니다.\n\n");
}

void modification(t_NODE** head, int* pn)
{
    int want_mod_num;
    char now_name[20];
    char now_phone[40];
    char new_name[20];
    char new_phone[40];
    char new_address[40];
    int new_price;
    int new_roomno;

    int exit_toggle = 1;

    printf("예약 변경\n");
    printf("예약자 성함 : ");
    scanf("%s", now_name);
    printf("예약자 전화번호 : ");
    scanf("%s", now_phone);

    t_NODE* current = *head;
    while (current != NULL) {
        if (current->name == now_name && current->phone == now_phone) {
            printf("^^^^^^ 예약 변경 ^^^^^^\n");
            printf("1. 예약자 성함 수정\n");
            printf("2. 예약자 전화번호 수정\n");
            printf("3. 예약자 주소 수정\n");
            printf("4. 객실 변경\n");
            printf("9. 수정 내용 저장 후 나가기\n");
            printf("^^^^^^^^^^^^^^^^^^^^\n");

            while (exit_toggle)
            {
                printf("예약 변경을 위해 해당되는 번호를 입력하세요. ");
                scanf("%d", want_mod_num);
                    switch (want_mod_num)
                    {
                        case 1:
                        printf("새로운 성함 입력 : ");
                        scanf("%s", new_name);
                        *current->name = new_name;

                        case 2:
                        printf("새로운 전화번호 입력 : ");
                        scanf("%s", new_phone);
                        *current->phone = new_phone;

                        case 3:
                        printf("새로운 주소 입력 : ");
                        scanf("%s", new_address);
                        *current->address = new_address;

                        case 4:
                        printf("새로운 객실 번호 입력 : ");
                        scanf("%d", new_roomno);
                        current->roomno = new_roomno;
                        if (new_roomno >= 1001 && new_roomno <= 1910)
                        {
                            new_price = 300000;
                            strcpy(current->enter_date, "오후 4시");
                            strcpy(current->exit_date, "오전 11시");
                        }
                        else if (new_roomno >= 2001 && new_roomno < 2910)
                        {
                            new_price = 500000;
                            strcpy(current->enter_date, "오후 3시");
                            strcpy(current->exit_date, "오전 11시");
                        }
                        else if (new_roomno >= 3001 && new_roomno < 3010)
                        {
                            new_price = 1000000;
                            strcpy(current->enter_date, "오후 3시");
                            strcpy(current->exit_date, "오후 1시");
                        }
                        current->price = new_price;
                        
                        case 9:
                        exit_toggle = 0;
                        break;
                    }
            }
            
            // 파일 업데이트
            long pos = ftell(fp);  // 현재 위치 저장
            fseek(fp, pos - (long)sizeof(t_NODE), SEEK_SET);
            fwrite(current, sizeof(t_NODE), 1, fp);
            return;
        }
        current = current->next;
    }
    printf("유효하지 않은 예약 입니다.\n\n");
}

void one_inquire(t_NODE** head, int* pn)
{
    char inq_name[20];
    char inq_phone[40];

    printf("예약 조회\n");
    printf("예약자 성함 : ");
    scanf("%s", inq_name);
    printf("예약자 전화번호 : ");
    scanf("%s", inq_phone);

    t_NODE* current = *head;
    while (current != NULL) {
        if (current->name == inq_name && current->phone == inq_phone) {
            printf("객실 번호 : %d\n", current->roomno);
            printf("이름 : %s\n", current->name);
            printf("전화번호 : %d\n", current->phone);
            printf("요금 : %d원\n", current->price);
            printf("주소 : %s\n", current->address);
            printf("입실 시각 : %s\n", current->enter_date);
            printf("퇴실 시각 : %s\n\n", current->exit_date);
        }
        current = current->next;
    }
    printf("유효하지 않은 예약입니다.\n\n");
}

void all_inquire(t_NODE** head, int* pn)
{
    t_NODE* current = *head;
    while (current != NULL)
    {
        printf("객실 번호 : %d\n", current->roomno);
        printf("이름 : %s\n", current->name);
        printf("전화번호 : %d\n", current->phone);
        printf("요금 : %d원\n", current->price);
        printf("주소 : %s\n", current->address);
        printf("입실 시각 : %s\n", current->enter_date);
        printf("퇴실 시각 : %s\n\n", current->exit_date);
        current = current->next;
    }
}

void load_reservatiom(t_NODE** head, int* pn)
{
    t_NODE* temp = NULL; // 저장할 임시 노드
    while (1) {
        t_NODE* new_reservation = (t_NODE*)malloc(sizeof(t_NODE)); // 메모리 동적 할당

        if (fread(new_reservation, sizeof(t_NODE), 1, fp) != 1) {
            free(new_reservation);
            break;
        }
        new_reservation->next = temp;
        if (temp != NULL)
            temp->prev = new_reservation;
        temp = new_reservation;
        (*pn)++;
    }
    if (temp != NULL) {
        *head = temp;
        (*head)->prev = NULL;
    }
}