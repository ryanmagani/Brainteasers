#include <stdio.h>
void test(char * stA, char * stB, char a, char b, int isPerm)
{
	if (isPermutation(stA, stB) == isPerm)
	{
		printf("correct %c, %c\n", a, b);
	}

	else
	{
		printf("ERROR: %c, %c\n", a, b);
	}
}

int main (void)
{
	char a[] = "hello";
	char b[] = "world";

	char c[] = "hello";
	char d[] = "llohe";

	char e[] = "ds";
	char f[] = "hello";

	char g[] = "a";
	char h[] = "b";

	char i[] = "a";
	char j[] = "a";

	char k[] = "chars";
	char l[] = "srahc";

	char m[] = "";
	char n[] = "";

	char o[] = "";
	char p[] = "a";

	test(a, b, 'a', 'b', 0);
	test(c, d, 'c', 'd', 1);
	test(e, f, 'e', 'f', 0);
	test(g, h, 'g', 'h', 0);
	test(i, j, 'i', 'j', 1);
	test(k, l, 'k', 'l', 1);
	test(m, n, 'm', 'n', 1);
	test(o, p, 'o', 'p', 0);
}
