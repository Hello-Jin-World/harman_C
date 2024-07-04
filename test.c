#include <stdio.h>

/*************		// ������ �ּ� (���α׷� �̸�, ����, �ۼ���, �ۼ���, ��� ��� �ۼ�)
* 
* 
* 
**************/  

#if 1 // 0�̸� ���� �� ��,  1�̸� ����
int main(void){ // void�� ����������. ��� ��.
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
	printf("char�� size : % d\n",sizeof(char)); // ���� type
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

	return 0; // 0 : error���� ������ �����ߴ�. -1 : �ɰ��� error. �� �� ������� ���Ǵ�� error code ����.
}
#endif