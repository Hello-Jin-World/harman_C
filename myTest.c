#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> // string 계산 함수가 들어있음
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
	printf("%95s\n", "ASCII CODE TABLE"); // 30칸을 오른쪽부터 출력하고 나머지는 공백
	// %-30s 30칸을 왼쪽부터 출력하고 나머지는 공백
	printf("%95s\n\n", "================");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s", "DEC", "HEX", "OCT", "CHAR");
	}
	printf("\n");
	for (int i = 0; i < 4; i++) {
		printf("%10s%10s%10s%10s", "===", "===", "===", "====");
	}
	printf("\n");
	for (int i = 0; i < 32; i++) // i <= 127 보다는 i < 128 이 속도가 더 빠르다
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

//6-1장 1번
#if 0
int main(void) {

	int a;
	while (1) {
		scanf("%d", &a);
		if (a >= 0)
		{
			break;
		}
	}
	return 0;
}
#endif
//6-1장 2번
#if 0
int main(void) {
	for (int i = 0;i < 5; i++)
	{
		printf("Be happy\n");
	}
	return 0;
}
#endif
//6-1장 3번
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
//6-2장 3번
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
//6-2장 실전
#if 0
int main(void) {
	int num, count = 0;
	printf("2 이상의 정수를 입력하세요 : ");
	scanf("%d", &num);
	
	for (int i = 2; i <= num; i++)
	{
		if (num % i == 0) printf("%d", num);
	}
	return 0;
}
#endif

#if 0
int main(void) {
	int num1, num2, result;
	char cal;
	printf("사칙연산 입력(정수) : ");
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

