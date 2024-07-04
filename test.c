#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> // string 계산 함수가 들어있음

/*************		// 블럭단위 주석 (프로그램 이름, 버전, 작성자, 작성일, 기능 등등 작성)
* 
* 
* 
**************/  

#if 0 // 0이면 실행 안 됨,  1이면 실행
int main(void){ // void는 가독성때문. 없어도 됨.
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
	printf("char의 size : % d\n",sizeof(char)); // 변수 type
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

	while(1){
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

		for (int i = 0; i < len-1; i++)
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
		printf("%s\n",alpha);
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

#if 1
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
		printf("%10s%10s%10s%10s\n", "DEC", "HEX", "OCT", "CHAR");
		printf("%10s%10s%10s%10s\n\n", "===", "===", "===", "====");
	}
	for (int i = 0; i < 128; i++) // i <= 127 보다는 i < 128 이 속도가 더 빠르다
	{
		printf("%10d%10.2x%10o%10c\n", i, i, i, i);
	}
	return 0;
}
#endif
