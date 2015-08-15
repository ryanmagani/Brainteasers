#define DEBUG 0
#include <stdio.h>

// this code should realistically never be used,
// it's a brainteaser example of how to check if
// string A is a permutation of string B with the
// following rules:
// 1. No variable creation
// 2. No function/macro calls (except printf for debugging)
// 2. No memory (stack, heap) usage/manipulation outside of the char*
// 3. Either (not both) of the strings may be modified, but its padding/null
//    terminator may not be modified
// 4. A[-1] = 0 (see assumptions)

// return 1 if true, 0 if false, 2 if rule three and/or assumptions violated

// Assumption 1: the caller's stack is laid out such that
// A exists on the stack adjacent to B,
// at a higher address than B,
// both padded to `wordsize` bytes
//
// Concrete example: A = "a" (0x61), B = "b" (0x62)
// B[16] = A = 'a'
// A[-16] = B = 'b'
// addr0:	62 00 ?? ?? ?? ?? ?? ?? ??
// addr8:	61 00 ?? ?? ?? ?? ?? ?? ??
//
// Generic example:
// addr0:	B0 B1 B2 B3 B4 B5 B6 B7 B8
//			...
// addrN:	BN 00 ?? ?? ?? ?? ?? ?? ??
// addrN+8:	A0 A1 ...   AN 00 ?? ?? ??

// Assumption 2: the uninitialized bytes ("??"s) are set to 00 so
// A[-1] = 0
int isPermutation(char * stA, char * stB)
{
	if (DEBUG)
	{
		printf("1: ptrA: %p, ptrB: %p\n", stA, stB);
		
		if (*(stA - 1) != 0)
		{
			printf("rule 3 and/or assumptions violated");
			return 2;
		}
	}

	// if we're given 2 empty strings, they are permutations
	if (!*stA && !*stB)
	{
		return 1;
	}

	// if we're given 1 empty string, no permutation
	if (!*stA || !*stB)
	{
		return 0;
	}

// REGION: compare length
	// travel to the end of one/both of the arrays
	while (*stA && *stB)
	{
		stA++;
		stB++;
	}

	// if we're at the end of only 1 array, the
	// strings are different lengths
	if (*stA != *stB)
	{
		return 0;
	}

	// go back one byte to make the following loop easier
	stA--;
	stB--;

	// continue to go back one byte until A's pointer
	// now points to the null terminator of A. This is
	// correct iff our assumptions are true
	while (*stA)
	{
		stA--;
		stB--;
	}

	// go forward one byte, we should be poining at the
	// beginning of both strings which we now know
	// are the same length
	stA++;
	stB++;

	if (DEBUG)
	{
		printf("2: ptrA: %p, ptrB: %p\n", stA, stB);
	}
// ENDREGION

// REGION: loop through B, removing equal chars from A until either a char is
// not found, or A is entirely 00 and stB points one left of the terminator
	// for all the characters in string B
	while (*stB)
	{
		// for all characters in string A
		while (*stA)
		{
			// if we match
			if (*stA == *stB)
			{
				// remove this char from the string and shift
				// the remaining characters to the right
				while (*stA)
				{
					*stA = *(stA - 1);
					stA--;
				}

				// we're pointing to 0x00 and we just
				// moved that value to our right, move
				// right two chars to get to the new
				// beginning of A
				stA++;
				stA++;

				// if the beginning of A is now 0x00, and the
				// next byte of B is B's null terminator, then
				// it is a permutation
				if (!*stA && !*(stB + 1))
				{
					return 1;
				}

				break;
			}
			stA++;
		}

		// if we didn't find the char, return false
		if (!*stA)
		{
			return 0;
		}

		// move our A pointer back to the beginning of A
		while (*stA)
		{
			stA--;
		}
		stA++;
		stB++;
	}
// ENDREGION

	printf("Some assumption/rule was violated, or a bug exists \n");
	return 2;
}
