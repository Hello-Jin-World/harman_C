#include <stdio.h>

/*************		// 블럭단위 주석 (프로그램 이름, 버전, 작성자, 작성일, 기능 등등 작성)
* 
* 
* 
**************/  

#if 1 // 0이면 실행 안 됨,  1이면 실행
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

	return 0; // 0 : error없이 실행을 종료했다. -1 : 심각한 error. 그 외 사용자의 편의대로 error code 정의.
}
#endif