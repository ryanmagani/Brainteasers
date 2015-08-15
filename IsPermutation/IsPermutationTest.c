#include <stdio.h>
int test(char * stA, char * stB, char a, char b, int isPerm)
{
	if (isPermutation(stA, stB) == isPerm)
	{
		printf("correct %c, %c\n", a, b);
		return 0;
	}

	printf("ERROR: %c, %c\n", a, b);
	return 1;
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

	int res = 0;

	res += test(a, b, 'a', 'b', 0);
	res += test(c, d, 'c', 'd', 1);
	res += test(e, f, 'e', 'f', 0);
	res += test(g, h, 'g', 'h', 0);
	res += test(i, j, 'i', 'j', 1);
	res += test(k, l, 'k', 'l', 1);
	res += test(m, n, 'm', 'n', 1);
	res += test(o, p, 'o', 'p', 0);

	if (res == 0)
	{
		printf("All tests passed \n");
	}

	return 0;
}
