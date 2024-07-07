#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#endif

#if 0

#define MAX_SIZE 20

void bubble_sort(int* list, int n, int order) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if ((order == 1 && list[j] > list[j + 1]) || (order == 2 && list[j] < list[j + 1])) {
				int temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

int main(void) {
	char input[256];
	int list[MAX_SIZE];
	int n;
	int order;

	while (1) {
		printf("�����͸� �Է� �ִ� 20�� (�����Ϸ��� 'exit' �Է�): ");
		fgets(input, sizeof(input), stdin);

		if (strncmp(input, "exit", 4) == 0) {
			break;
		}

		// �Է¹��� �����͸� ���� �迭�� ��ȯ
		char* token = strtok(input, " ");
		n = 0;
		while (token != NULL && n < MAX_SIZE) {
			list[n++] = atoi(token);
			token = strtok(NULL, " ");
		}

		printf("���� ���� (1: ��������, 2: ��������): ");
		fgets(input, sizeof(input), stdin);
		order = atoi(input);

		printf("���� ������: ");
		for (int i = 0; i < n; i++) {
			printf("%d ", list[i]);
		}
		printf("\n");

		// ���� ���� ����
		bubble_sort(list, n, order);

		// ���� ��� ���
		if (order == 1) {
			printf("�������� ����: ");
		}
		else {
			printf("�������� ����: ");
		}
		for (int i = 0; i < n; i++) {
			printf("%d ", list[i]);
		}
		printf("\n");
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
	char text[32][10] = { "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US" };
	int a = 32;
	int b = 64;
	int c = 96;
	printf("%95s\n", "ASCII CODE TABLE"); // 30ĭ�� �����ʺ��� ����ϰ� �������� ����
	// %-30s 30ĭ�� ���ʺ��� ����ϰ� �������� ����
	printf("%95s\n\n", "================");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s", "DEC", "HEX", "OCT", "CHAR");
	}
	printf("\n");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s", "===", "===", "===", "====");
	}
	printf("\n");
	for (int i = 0; i < 32; i++) // i <= 127 ���ٴ� i < 128 �� �ӵ��� �� ������
	{
		printf("%10d%10.2x%10o%10s", i, i, i, text[i]);
		printf("%10d%10.2x%10o%10c", a, a, a, a);
		printf("%10d%10.2x%10o%10c", b, b, b, b);
		printf("%10d%10.2x%10o%10c", c, c, c, c);
		printf("\n");
		a++; b++; c++;
	}

	return 0;
}
#endif

// ����
#if 0

void cal(char* p);

int main(void)
{
	char input[100];

	while (1)
	{
		fgets(input, 100, stdin);

		if (strncmp(input, "exit", 4) == 0)
		{
			break;
		}

		cal(input);
	}
	return 0;
}

void cal(char* p)
{
	int i = 0, num1 = 0, num2 = 0;
	char oper;
	while (1)
	{
		if (p[i] >= '0' && p[i] <= '9')
		{
			num1 = num1 * 10 + (p[i] - '0');
			i++;
		}
		else if (p[i] == '+' || p[i] == '-' || p[i] == '*' || p[i] == '/')
		{
			oper = p[i];
			break;
		}
	}

	for (int j = i + 1; j < strlen(p) - 2; j++)
	{
		num2 = num2 * 10 + (p[j] - '0');
	}

	switch (oper)
	{
	case '+':
		printf("%d\n", num1 + num2);
		break;
	case '-':
		printf("%d\n", num1 - num2);
		break;
	case '*':
		printf("%d\n", num1 * num2);
		break;
	case '/':
		printf("%d\n", num1 / num2);
		break;
	default:
		break;
	}
}
#endif

//sort ���α׷�
#if 1
#define MAXSIZE 100

void bubble_sort();

int main(void)
{
	int i, num;
	int n = MAXSIZE;
	int list[MAXSIZE];
	char arry[MAXSIZE];

	while (1)
	{
		n = 0; i = 0; num = 0;
		printf("data�� �Է�, �ִ� 20(10 1 5) ����(exit) : ");
		fgets(arry, MAXSIZE, stdin);

		if (strncmp(arry, "exit", 4) == 0)
		{
			break;
		}
		for (int j = 0; j < strlen(arry); j++)
		{
			if (arry[j] >= '0' && arry[j] <= '9')
			{
				num = num * 10 + (arry[j] - '0');

				list[i] = num;
				n = i + 1;
			}
			else if (arry[j] == ' ')
			{
				num = 0;
				i++;
			}
		}

		bubble_sort(list, &n);

		for (i = 0; i < n; i++)
		{
			printf("%d ", list[i]);
		}
		printf("\n");
	}
	return 0;
}

void bubble_sort(int* ary, int* n)
{
	int mod = 0;
	printf("sort ����( 1: ascending, 2: descending) : ");
	scanf("%d", &mod);
	getchar();

	int temp;

	printf("orgianl data : ");
	for (int i = 0; i < *n; i++)
	{
		printf("%d ", ary[i]);
	}
	printf("\n");

	if (mod == 1)
	{

		for (int i = 0; i < *n - 1; i++)
		{
			for (int j = i + 1; j < *n; j++)
			{
				if ( ary[i] > ary[j])
				{
					temp = ary[i];
					ary[i] = ary[j];
					ary[j] = temp;
				}
			}
		}
		printf("ascending order : ");
	}
	else if (mod == 2)
	{
		for (int i = 0; i < *n - 1; i++)
		{
			for (int j = i + 1; j < *n; j++)
			{
				if (ary[i] < ary[j])
				{
					temp = ary[i];
					ary[i] = ary[j];
					ary[j] = temp;
				}
			}
		}
		printf("descending order : ");
	}
	else
	{
		return;
	}
}

#endif

#if 0
void cal();

int main(void)
{
	char input[100];

	while (1)
	{
		fgets(input, 100, stdin);
		if (strncmp(input, "exit", 4) == 0)
		{
			break;
		}
		cal(input);
	}
	return 0;
}

void cal(char* p)
{
	char oper;
	int num1, num2;
	//�����ȣ�� ��ȣ ����
	sscanf(p, "%d %c %d", &num1, &oper, &num2);

	switch (oper)
	{
	case '+':
		printf("%d+%d=%n\n", num1, num2, num1 + num2);
		break;
	case '-':
		printf("%d-%d=%d\n", num1, num2, num1 - num2);
		break;
	case '*':
		printf("%d*%d=%d\n", num1, num2, num1 * num2);
		break;
	case '/':
		printf("%d/%d=%d\n", num1, num2, num1 / num2);
		break;
	default:
		break;
	}
}
#endif

//6-1�� 1��
#if 0
int main(void) {
	int a;
	do
	{
		scanf("%d", &a);
	} while (a < 0);
	return 0;
}
#endif
//6-1�� 2��
#if 0
int main(void) {
	for (int i = 0;i < 5; i++)
	{
		printf("Be happy\n");
	}
	return 0;
}
#endif
//6-1�� 3��
#if 0
int main(void) {
	int i;
	for (i = 0;i < 10; i++)
	{
		printf("$");
	}
	return 0;
}
#endif
//6-2�� 3��
#if 0
int main(void) {
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == j || i + j == 4)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	
	return 0;
}
#endif
//6-2�� ����
#if 0
int main(void) {
	int in_num, num, i;
	int line = 0;

	printf("2 �̻��� ������ �Է��ϼ��� : ");
	scanf("%d", &in_num);
	
	for (num = 2; num <= in_num; num++)
	{
		for (i = 2; i < num; i++)
		{
			if (num % i == 0) break;
		}

		if (num == i)
		{
			printf("%4d", num);

			line ++;
			if (line == 5)
			{
				printf("\n");
				line = 0;
			}
		}
	}
	return 0;
}
#endif
//7-1�� 1��
#if 0
double average();
int main(void)
{
	double res;
	res = average(1.5, 3.4);
	printf("%lf", res);
}
double average(double a, double b)
{
	double temp;
	temp = a + b;
	return (temp / 2.0);
}

#endif
//7-1�� 2��
/*
�Լ� ���� - �Լ� ������ �����Ϸ��� �˸���.
�Լ� ���� - �Լ� ������ �����ϰ� ������ �����Ѵ�.
�Լ� ȣ�� - �Լ��� �ʿ��� ���� �ְ� �Լ��� ����Ѵ�.
*/
//7-1�� 3��
#if 0
double centi_to_meter();

int main(void)
{
	double res;

	res = centi_to_meter(187);
	printf("%.2lfm\n", res);

	return 0;
}

double centi_to_meter(int centi)
{
	double meter;
	
	meter = (double)centi / 100;

	return (meter);
}
#endif
//7-2�� 1��
//	4��
//7-2�� 2��
#if 0
int sum();

int main(void)
{
	sum(10);
	sum(100);
	return 0;
}

int sum(int num)
{
	int count, result = 0;
	for (count = 1; count < num + 1; count++)
	{
		result += count;
	}
	printf("1���� %d������ ���� %d�Դϴ�.\n", num, result);
}
#endif
//7-2�� 3��
//	9
#if 0
int func(int n);
int poly(int n);

int main(void)
{
	printf("%d", func(-3));
	return 0;
}
int func(int n)
{
	int res;
	res = poly(n);
	if (res >= 0) return res;
	else return -res;
}
int poly(int n)
{
	return ((2 * n * n) + (3 * n));
}
#endif
//7-2�� ����
#if 0
int rec_func();

int main(void)
{
	printf("%d", rec_func(10));
}
int rec_func(int n)
{
	int sum;
	if (n == 1)
	{
		return 1;
	}
	else
	{
		sum = n + rec_func(n - 1);
	}
	return sum;
}
#endif
//8-1�� 1��
/*
int arry[5];
float arry[10];
int arry[3];
char arry[5];
*/
//8-1�� 2��
/*int arry[6] = {1, 2, 3, 0, 0, 0};*/
//8-1�� 3��
#if 0
int main(void)
{
	int A[3] = { 1, 2, 3 };
	int B[10];
	int i;
	for (i = 0; i < 10; i++)
	{
		B[i] = A[i % 3];
	}
	for (i = 0; i < 10; i++)
	{
		printf("%3d", B[i]);
	}

}
#endif
//8-2�� 1��
/*
	O
	O
	X
	X
*/
//8-2�� 2��
//	4��
//8-2�� 3��
#if 0
int main(void)
{
	char str1[80], str2[80];
	char temp[80];

	printf("�� ���ڿ� �Է� : ")
	scanf("%s %s", str1, str2);
	printf("�ٲٱ� �� : %s %s\n", str1, str2);
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
	printf("�ٲ� �� : %s %s\n", str1, str2);
}
#endif
//8-2�� ����
#if 0
int main(void)
{
	char str[80];
	int count = 0;
	printf("���� �Է� : ");
	gets(str);
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 0x20;
			count++;
		}
	}
	printf("�ٲ� ���� : %s\n", str);
	printf("�ٲ� ���� �� : %d\n", count);
}
#endif
//9-1�� 1��
/*
	char *p = &ch;
	int *p = &in;
	double *p = &db;
*/
//9-1�� 2��
#if 0
int main(void)
{
	char ch = 'A';
	int in = 10;
	double db = 3.4;

	int* a = &ch;
	int* b = &in;
	double* c = &db;

	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);

	printf("%c\n", *a);
	printf("%d\n", *b);
	printf("%.1lf\n", *c);
}
/*
100, 101, 105, A, 10, 3.4
*/
#endif
//9-1�� 3��
#if 0
int main(void)
{
	int a = 10;
	int* p = &a;
	*p = 20;
	printf("%d", a);
}
//	20
#endif
//9-2�� 1��
/*
	1. ���� 2. ��� 3. ���� 4. ���� 5. ���
*/
//9-2�� 2��
//	4��
//9-2�� 3��
//	20 10
//9-2�� ����
#if 0
void swap(double* pa, double* pb);
void line_up(double* maxp, double* midp, double* minp);

int main(void)
{
	double max, mid, min;

	printf("�Ǽ��� 3�� �Է� : ");
	scanf("%lf %lf %lf", &max, &mid, &min);
	line_up(&max, &mid, &min);
	printf("���ĵ� �� ��� : %.1lf, %.1lf, %.1lf\n", max, mid, min);

	return 0;
}

void swap(double* pa, double* pb)
{
	double temp;

	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

void line_up(double* maxp, double* midp, double* minp)
{
		if (*midp > *maxp)
			swap(maxp, midp);
		if (*minp > *maxp)
			swap(maxp, minp);
		if (*minp > *midp)
			swap(midp, minp);
}
#endif
//10-1�� 1, 2, 3��
#if 0
int main(void)
{
	double ary[5] = { 1.2, 3.5, 7.4, 0.5, 10.0 };
	double* pa = ary;
	double* pb = ary + 2;
	printf("%.1ld", ary);
}
//	1��		100, 3.5, 116, 0.5, 7.4, 2
//	2��		x, x, o, o, x, o
//	3��		pb++;
#endif

#if 0
int main(void) {
	int num1, num2, result;
	char cal;
	printf("��Ģ���� �Է�(����) : ");
	scanf("%d%c%d", &num1, &cal, &num2);
	if (cal == '+') {
		result = num1 + num2;
		printf("%d%c%d=%d", num1, cal, num2, result);
	}
	else if (cal == '-') {
		result = num1 - num2;
		printf("%d%c%d=%d", num1, cal, num2, result);
	}
	else if (cal == '*') {
		result = num1 * num2;
		printf("%d%c%d=%d", num1, cal, num2, result);
	}
	else {
		result = num1 / num2;
		printf("%d%c%d=%d", num1, cal, num2, result);
	}
	return 0;
}
#endif

