#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> // string ��� �Լ��� �������
#endif

#if 1
void shift_alpha();
int main(void)
{
	char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	shift_alpha(alpha);

	return 0;
}

void shift_alpha(char* alpha)
{
	int j;
	for (j = 0; j < 25; j++)
	{
		for (int i = 0; i < 27; i++)
		{
			printf("%c", *(alpha + i + j));
		}
		printf("%c", *(alpha + j));
		printf("\n");
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
void upper2lower(char *p)
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

void cal(int *pa, int *pb, int *ptotal, double *pavg)
{
	*ptotal =  *pa + *pb;
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


/*************		// ������ �ּ� (���α׷� �̸�, ����, �ۼ���, �ۼ���, ��� ��� �ۼ�)
* 
* 
* 
**************/  

#if 0 // 0�̸� ���� �� ��,  1�̸� ����
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

	while(1){
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

		for (int i = 0; i < len-1; i++)
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

		printf("%10d%10.2x%10o  ", i+32, i+32, i+32);
		bin_print(i + 32);
		printf("%10c", i + 32);

		printf("%10d%10.2x%10o  ", i+64, i+64, i+64);
		bin_print(i+64);
		printf("%10c", i + 64);

		printf("%10d%10.2x%10o  ", i+96, i+96, i+96);
		bin_print(i+96);
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
			buff[i+1] = x;
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
